using S32PSave;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

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
    }
}
