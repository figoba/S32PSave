using S32PSave;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;

namespace test
{
    
    
    /// <summary>
    ///这是 UtilTest 的测试类，旨在
    ///包含所有 UtilTest 单元测试
    ///</summary>
    [TestClass()]
    public class UtilTest
    {


        private TestContext testContextInstance;

        /// <summary>
        ///获取或设置测试上下文，上下文提供
        ///有关当前测试运行及其功能的信息。
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                Util.DB_MesDataCenterConnectionString = "Provider=SQLNCLI11;Data Source=172.20.23.107;Persist Security Info=True;User ID=sa;Initial Catalog=MesDataCenter;Password=data'songyy";
                testContextInstance = value;
            }
        }

        #region 附加测试特性
        // 
        //编写测试时，还可使用以下特性:
        //
        //使用 ClassInitialize 在运行类中的第一个测试前先运行代码
        //[ClassInitialize()]
        //public static void MyClassInitialize(TestContext testContext)
        //{
        //}
        //
        //使用 ClassCleanup 在运行完类中的所有测试后再运行代码
        //[ClassCleanup()]
        //public static void MyClassCleanup()
        //{
        //}
        //
        //使用 TestInitialize 在运行每个测试前先运行代码
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        //使用 TestCleanup 在运行完每个测试后运行代码
        //[TestCleanup()]
        //public void MyTestCleanup()
        //{
        //}
        //
        #endregion


        /// <summary>
        ///getSavedNumber 的测试
        ///</summary>
        [TestMethod()]
        public void getSavedNumberTest()
        {
            string PN = "L01HE014-SD-R";
            string MO = "E511D-180800235";
            int testNo = 1; // TODO: 初始化为适当的值
            int expected = 40; // TODO: 初始化为适当的值
            int actual;
            actual = Util.getSavedNumber(MO, PN, testNo);
            Assert.AreEqual(expected, actual);
         
        }

        /// <summary>
        ///getConfig 的测试
        ///</summary>
        [TestMethod()]
        public void getConfigTest()
        {
            string configPath = @"D:\gitProjects\S32PSave\S32PSave\bin\x86\Debug\config.xml" ; // TODO: 初始化为适当的值
            config expected = null; // TODO: 初始化为适当的值
            config actual;
            actual = Util.getConfig(configPath);
            Assert.AreEqual(0, actual.MoTolerance);
           
        }

        /// <summary>
        /// getITSN 的测试
        /// </summary>
        [TestMethod()]
        public void getITSNTest()
        {
            string PN = "L01HE014-SD-R";
            string MO = "E511D-180800235";
            SNData actual;
            actual= Util.getITSN(MO, PN);
            Assert.IsNotNull(actual);
        }
        [TestMethod()]
        public void sqlLiteTest()
        {
            string PN = "LZ6AAAAAA";
            string strSql = "select frequency,TDR,general from vna32port where LuxsharePN='" + PN + "'";
            //DataTable dt= DbHelperOleDb.Query(strSql,DB_HTPSDBConnectionString).Tables[0];
            DataTable dt = SqlLite.ExecuteDataTable(strSql);
            if (dt.Rows.Count != 1) {
                
            }
           
        }

        [TestMethod()]
        public void readTxt()
        {
            string filePath = @"C:\Users\Administrator\Desktop\777.txt";

            //float[] f1 = {0.1f, 0.2f,0.3f,0.4f};
            //byte[]b1=new byte[f1.Length*sizeof(float)];
            //Buffer.BlockCopy(f1, 0, b1, 0, b1.Length);

            //float[]f2=new float[2];
            //Buffer.BlockCopy(b1, 0, f2, 0, f2.Length*sizeof(float));
            byte[] retb = File.ReadAllBytes(filePath);
            int dbLength = BitConverter.ToInt32(retb.Take(4).ToArray(),0);
            int freLength = BitConverter.ToInt32(retb.Skip(4).Take(4).ToArray(), 0);
            byte[] db = retb.Skip(8).Take(dbLength).ToArray();
            byte[] fre = retb.Skip(8 + dbLength).Take(freLength).ToArray();

            float[]dbFloats=new float[db.Length/sizeof(float)];
            Buffer.BlockCopy(db, 0, dbFloats, 0, db.Length);

            double[] freDoubles = new Double[fre.Length / sizeof(double)];
            Buffer.BlockCopy(fre, 0, freDoubles, 0, fre.Length);

            float[]ret=new float[retb.Length/sizeof(float)];
            Buffer.BlockCopy(retb, 0, ret, 0, ret.Length);
            
            //List<float> ret = new List<float>();
            //using (FileStream reader = new FileStream(filePath, FileMode.Open, FileAccess.ReadWrite))
            //{
            //    using (BinaryReader binRdr = new BinaryReader(reader))
            //    {
                    
            //        byte[] chunk;
            //        chunk = binRdr.ReadBytes(sizeof(float));
            //        while (chunk.Length > 0)
            //        {
            //            ret.Add(BitConverter.ToSingle(chunk, 0));
            //            chunk = binRdr.ReadBytes(sizeof(float));
            //        }

                   
            //    }

            //}
            var new1 = ret.Where((c, i) => i % 2 == 0).ToArray();
            var new2 = ret.Where((c, i) => i % 2 != 0).ToArray();
            float[,]real=new float[2650,1024];
            float[,] image = new float[2650, 1024];
            Buffer.BlockCopy(new1, 0, real, 0, new1.Length * sizeof(float));
            Buffer.BlockCopy(new2, 0, image, 0, new2.Length * sizeof(float));
        }
        [TestMethod()]
        public void CycleTest()
        {
            string[] tempRow = new string[1];
            Dictionary<int,string[]>ret=new Dictionary<int, string[]>();
            for (int i = 0; i < 10; i++)
            {
                tempRow[0] = i.ToString();
                ret.Add(i,tempRow);
            }

        }
    }
}
