using System;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using Ivi.Visa.Interop;

namespace P9375
{
    /// <summary>
    /// 9375 32port网分仪器控制dll,采用内存共享方式，只能在网分电脑上部署使用
    /// </summary>
    public class P9375A
    {
        private static FormattedIO488 gPNA;
        private static string IDNinfo;
        private bool connect;

       /// <summary>
       /// 内存数据获取时发生
       /// </summary>
        public event Action<float[]> OnMemoryDataGet;
        /// <summary>
        /// 频率数据获取前发生
        /// </summary>
        public event Action BeforeGetfre;
        /// <summary>
        /// 频率数据获取时发生
        /// </summary>
        public event Action<double[]> OnFreGet;

        /// <summary>
        /// 仪器连接
        /// </summary>
        /// <param name="Address">仪器visa地址</param>
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

        /// <summary>
        /// 获取仪器连接状态
        /// </summary>
        /// <returns>bool</returns>
        public bool IsConnect()
        {
            return connect;
        }

        /// <summary>
        /// 通用visa命令执行
        /// </summary>
        /// <param name="scpi"></param>
        /// <returns>字符串</returns>
        public string Query(string scpi)
        {
            gPNA.WriteString(scpi);
            return gPNA.ReadString();
        }

        /// <summary>
        /// 保存SNP文件
        /// </summary>
        /// <param name="filename">snp文件路径</param>
        /// <param name="portCount">端口数</param>
        public void StoreS2P(string filename, int portCount)
        {

            int pointCount = 0;
            HecSnp hecsnp = GetData(ref pointCount, portCount);
            DataConverter.SaveSnp(filename, hecsnp, portCount);

        }
        /// <summary>
        /// 保存二进制形式s32p文件
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="portCount"></param>
        public void StorePure(string filename, int portCount = 32)
        {
            int pointCount = 0;
            HecSnp hecsnp = GetData(ref pointCount, portCount);
            DataConverter.SavePure(filename, hecsnp);
        }

        private  float[] SweepStore(ref int pointCount, int portCount)
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
            int offset = Convert.ToInt32(gPNA.ReadString());
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
            var tempGetMemoryData = OnMemoryDataGet;
            if (tempGetMemoryData != null)
            {
                tempGetMemoryData(arr);
            }
            return arr;
        }


        private static unsafe void ReadBytes(MemoryMappedViewAccessor mappedFileView, int offset, int num, float[] arr)
        {
            byte* numPtr = null;
            mappedFileView.SafeMemoryMappedViewHandle.AcquirePointer(ref numPtr);
            Marshal.Copy(IntPtr.Add(new IntPtr(numPtr), offset), arr, 0, num);
            mappedFileView.SafeMemoryMappedViewHandle.ReleasePointer();
        }




      

        private HecSnp GetData(ref int pointCount,  int portCount)
        {
            //int pointCount = 0;
            HecSnp ret=new HecSnp();
            float[]value = SweepStore(ref pointCount, portCount);

            var tempBefore_Getfre = BeforeGetfre;
            if (tempBefore_Getfre != null)
            {
                tempBefore_Getfre();
            }
            gPNA.WriteString("FORM REAL,64", true);
            gPNA.WriteString("CALC:MEAS:X?", true);
            double[]fre = (double[])gPNA.ReadIEEEBlock(IEEEBinaryType.BinaryType_R8, false, true);
            gPNA.WriteString("FORM ASCii,0", true);
            var tempOn_Getfre = OnFreGet;
            if (tempOn_Getfre != null)
            {
                tempOn_Getfre(fre);
            }

            
            byte[]valueBytes=new byte[value.Length*sizeof(float)];
            Buffer.BlockCopy(value, 0, valueBytes, 0, valueBytes.Length);

            byte[] freBytes = new byte[fre.Length * sizeof(double)];
            Buffer.BlockCopy(fre, 0, freBytes, 0, freBytes.Length);

            ret.Idn = IDNinfo;
            ret.Date = DateTime.Now.ToString("F");
            ret.Fre = freBytes;
            ret.Value = valueBytes;
            return ret;
        }

    

       
      

    }
}
