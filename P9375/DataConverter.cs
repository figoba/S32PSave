using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;


namespace P9375
{
   public struct HecSnp
    {
        /// <summary>
        /// 仪器型号信息
        /// </summary>
        public string Idn { get; set; }
        /// <summary>
        /// 测试日期
        /// </summary>
        public string Date { get; set; }
        /// <summary>
        /// 实部虚部
        /// </summary>
        public byte[] Value { get; set; }
        /// <summary>
        /// 频率
        /// </summary>
        public byte[] Fre { get; set; }
    }

    public class DataConverter
    {
        private static readonly string _headers = "figoba";
        private static readonly byte[] headBytes = System.Text.Encoding.Default.GetBytes(_headers);

        /// <summary>
        /// HEC二进制格式保存
        /// 0-3 文件头长度，字符串
        /// 4-7 仪器信息长度，字符串
        /// 8-11 测试日期字符串长度，字符串
        /// 12-15 频率长度，double[]数组
        /// 16-19 实部虚部长度，float[]数组
        /// 20-结尾 按上面五部分长度划分
        /// </summary>
        /// <param name="saveFilePath"></param>
        /// <param name="hecSnp"></param>
        public static void SavePure(string saveFilePath,HecSnp hecSnp)
        {
            byte[] idn = System.Text.Encoding.Default.GetBytes(hecSnp.Idn);
            byte[] date = System.Text.Encoding.Default.GetBytes(hecSnp.Date);
            byte[] allBytes = JoinBytes(new[] { headBytes,idn,date,hecSnp.Fre,hecSnp.Value});
            using (FileStream writer = new FileStream(saveFilePath, FileMode.Create, FileAccess.ReadWrite))
            {
                using (BinaryWriter binWtr = new BinaryWriter(writer))
                {
                    binWtr.Write(allBytes);
                }

            }
        }

        public static void SaveSnp(string saveFilePath, HecSnp hecSnp, int portCount)
        {
            using (StreamWriter writer = File.CreateText(saveFilePath))
            {
                writer.WriteLine("!" + hecSnp.Idn);
                writer.WriteLine("!" + hecSnp.Date);
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

                double[] freDoubles = new Double[hecSnp.Fre.Length / sizeof(double)];
                Buffer.BlockCopy(hecSnp.Fre, 0, freDoubles, 0, hecSnp.Fre.Length);

                float[] dbFloats = new float[hecSnp.Value.Length / sizeof(float)];
                Buffer.BlockCopy(hecSnp.Value, 0, dbFloats, 0, hecSnp.Value.Length);

                DataWrapper wrapper = new DataWrapper
                {
                    allData = dbFloats,
                    pointCount = freDoubles.Length,
                    portCount = portCount
                };
                for (int k = 0; k < freDoubles.Length; k++)
                {
                    writer.Write(freDoubles[k].ToString("G17") + " ");
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

        private static string ToSParameter(int receivePort, int sourcePort)
        {
            if ((receivePort <= 9) && (sourcePort <= 9))
            {
                return ("S" + receivePort.ToString() + sourcePort.ToString());
            }
            return ("S" + receivePort.ToString() + "_" + sourcePort.ToString());
        }


        public static HecSnp GetSnp(string hecFilePath)
        {
            string extensionName=(new FileInfo(hecFilePath)).Extension.ToUpper();
            if (extensionName != ".HEC")
            {
                throw new Exception("only support HEC file!");
            }
            byte[] allBytes = File.ReadAllBytes(hecFilePath);
            int headLength = BitConverter.ToInt32(allBytes, 0);
            int idnLength = BitConverter.ToInt32(allBytes, 4);
            int dateLength = BitConverter.ToInt32(allBytes, 8);
            int freLength = BitConverter.ToInt32(allBytes, 12);
            int valueLength = BitConverter.ToInt32(allBytes, 16);
            string _head = System.Text.Encoding.Default.GetString(allBytes.Skip(20).Take(headLength).ToArray());
            if (_head != _headers)
            {
                throw new Exception("invalid HEC file!");
            }

            HecSnp ret=new HecSnp();
            ret.Idn = Encoding.Default.GetString(allBytes.Skip(20+headLength).Take(idnLength).ToArray());
            ret.Date = Encoding.Default.GetString(allBytes.Skip(20 + headLength+idnLength).Take(dateLength).ToArray());
            ret.Fre = allBytes.Skip(20 + headLength + idnLength+dateLength).Take(freLength).ToArray();
            ret.Value = allBytes.Skip(20 + headLength + idnLength + dateLength+freLength).Take(valueLength).ToArray();
            return ret;
        }

        public static byte[] JoinBytes(byte[][]section)
        {
            List<byte>tempBytes=new List<byte>();
            foreach (var variable in section)
            {
                int sectionLength = variable.Length;
                tempBytes.AddRange(BitConverter.GetBytes(sectionLength));
             }
            foreach (var variable in section)
            {
               tempBytes.AddRange(variable);
            }

            return tempBytes.ToArray();
        }
    }

     class DataWrapper
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
