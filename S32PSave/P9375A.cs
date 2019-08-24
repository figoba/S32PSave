using System;
using System.Collections.Generic;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using Ivi.Visa.Interop;

namespace S32PSave
{
    class P9375A
    {
        private static  FormattedIO488 gPNA;
        private static string IDNinfo;
        private bool connect;



        public void Connect(string Address)
        {
            if (!connect)
            {
                ResourceManager resourceManagerIv = new ResourceManager();
                gPNA = new FormattedIO488();
                gPNA.IO = (IMessage)resourceManagerIv.Open(Address, AccessMode.NO_LOCK, 0x7d0, "");
                gPNA.IO.Timeout = 0xea60;
                connect = true;
            }
          
            gPNA.WriteString("*IDN?", true);
            IDNinfo = gPNA.ReadString();

        }

        public bool IsConnect()
        {
            return connect;
        }


        public string Query(string scpi)
        {
            gPNA.WriteString(scpi);
            return gPNA.ReadString();
        }

        public static float[] SweepStore(ref int pointCount, int portCount)
        {
            string str = "S1_1";
            int num = 0;
            gPNA.WriteString("CALC:PAR:EXT '" + str + "', '" + str + "'", true);
            gPNA.WriteString("CALC:PAR:SEL '" + str + "',fast", true);
            gPNA.WriteString("CALC:PAR:MNUM?", true);
            num = Convert.ToInt32(gPNA.ReadString());
            gPNA.WriteString("SENS1:SWE:POIN?", true);
            pointCount = Convert.ToInt32(gPNA.ReadString());
            gPNA.WriteString("SYST:DATA:MEM:INIT", true);
            int num2 = ((pointCount * portCount) * portCount) * 2;
            string data = string.Concat(new object[] { "SYST:DATA:MEM:ADD '1:", num, ":CAL:", num2.ToString(), "'" });
            //string data = string.Concat(new object[] { "SYST:DATA:MEM:ADD '1:", num, ":SDATA:", num2.ToString(), "'" });
            gPNA.WriteString(data, true);
            gPNA.WriteString("SYST:DATA:MEM:OFFSet?", true);
            int offset=Convert.ToInt32(gPNA.ReadString());
            gPNA.WriteString("SYST:DATA:MEM:NAME?", true);
            string str3 = gPNA.ReadString();
            gPNA.WriteString("SYST:DATA:MEM:COMM '" + str3 + "'", true);
            gPNA.WriteString("SYST:DATA:MEM:SIZE?", true);
            int num3 = int.Parse(gPNA.ReadString());
            gPNA.WriteString("SENS:SWE:MODE SING", true);
            gPNA.WriteString("*OPC?", true);
            gPNA.ReadString();
            float[] arr = null;
            using (MemoryMappedFile file = MemoryMappedFile.CreateOrOpen(str3, (long)num3))
            {
                using (MemoryMappedViewAccessor accessor = file.CreateViewAccessor())
                {
                    arr = new float[num2];
                    ReadBytes(accessor, offset, num2, arr);
                }
            }
            gPNA.WriteString("SYST:DATA:MEM:RESET", true);
            gPNA.WriteString("*OPC?", true);
            gPNA.ReadString();
            gPNA.WriteString("CALC:PAR:SEL '" + str + "',fast", true);
            gPNA.WriteString("CALC:PAR:DEL '" + str + "'", true);
            return arr;
        }


        public static unsafe void ReadBytes(MemoryMappedViewAccessor mappedFileView, int offset, int num, float[] arr)
        {
            byte* numPtr = null;
            mappedFileView.SafeMemoryMappedViewHandle.AcquirePointer(ref numPtr);
            Marshal.Copy(IntPtr.Add(new IntPtr(numPtr), offset), arr, 0, num);
            mappedFileView.SafeMemoryMappedViewHandle.ReleasePointer();
        }




        private static string ToSParameter(int receivePort, int sourcePort)
        {
            if ((receivePort <= 9) && (sourcePort <= 9))
            {
                return ("S" + receivePort.ToString() + sourcePort.ToString());
            }
            return ("S" + receivePort.ToString() + "_" + sourcePort.ToString());
        }




        public void StoreS2P(string filename, int portCount)
        {
            double[] numArray = null;
            int pointCount = 0;
            float[] numArray2 = SweepStore(ref pointCount, portCount);
            gPNA.WriteString("FORM REAL,64", true);
            gPNA.WriteString("CALC:MEAS:X?", true);
            numArray = (double[])gPNA.ReadIEEEBlock(IEEEBinaryType.BinaryType_R8, false, true);
            gPNA.WriteString("FORM ASCii,0", true);
            using (StreamWriter writer = File.CreateText(filename))
            {
                writer.WriteLine("!" + IDNinfo);
                writer.WriteLine("!" + DateTime.Now.ToString("F"));
                writer.Write("!S" + portCount.ToString() + "P File: Measurements: <");
                for (int i = 1; i <= portCount; i++)
                {
                    writer.Write(ToSParameter(1, i));
                    if (i != portCount)
                    {
                        writer.Write(",");
                    }
                }
                writer.WriteLine(">,");
                for (int j = 2; j <= portCount; j++)
                {
                    writer.Write("!<");
                    for (int m = 1; m <= portCount; m++)
                    {
                        writer.Write(ToSParameter(j, m));
                        if (m != portCount)
                        {
                            writer.Write(",");
                        }
                    }
                    writer.Write(">");
                    if (j != portCount)
                    {
                        writer.WriteLine(",");
                    }
                    else
                    {
                        writer.WriteLine(":");
                    }
                }
                writer.WriteLine("# Hz S  RI   R 50");
                DataWrapper wrapper = new DataWrapper
                {
                    allData = numArray2,
                    pointCount = pointCount,
                    portCount = portCount
                };
                for (int k = 0; k < numArray.Length; k++)
                {
                    writer.Write(numArray[k].ToString("G17") + " ");
                    for (int n = 1; n <= portCount; n++)
                    {
                        for (int num8 = 1; num8 <= portCount; num8++)
                        {
                            writer.Write(wrapper.Real(n, num8, k));
                            writer.Write(" ");
                            writer.Write(wrapper.Imag(n, num8, k));
                            writer.Write(" ");
                            if (((num8 % 4) == 0) && (num8 != portCount))
                            {
                                writer.WriteLine();
                            }
                        }
                        if (n != portCount)
                        {
                            writer.WriteLine();
                        }
                    }
                    writer.WriteLine();
                }
            }
        }

        private class DataWrapper
        {
            // Fields
            public float[] allData;
            public int pointCount;
            public int portCount;

            // Methods
            public float Imag(int receive, int source, int index)
            {
                int num = ((source - 1) * this.portCount) + (receive - 1);
                num *= this.pointCount * 2;
                num += index * 2;
                return this.allData[num + 1];
            }
            public float Real(int receive, int source, int index)
            {
                int num = ((source - 1) * this.portCount) + (receive - 1);
                num *= this.pointCount * 2;
                num += index * 2;
                return this.allData[num];
            }




        }



    }

   


}
