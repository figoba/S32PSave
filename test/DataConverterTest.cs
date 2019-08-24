using P9375;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace test
{
    
    
    /// <summary>
    ///这是 DataConverterTest 的测试类，旨在
    ///包含所有 DataConverterTest 单元测试
    ///</summary>
    [TestClass()]
    public class DataConverterTest
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
        ///GetSnp 的测试
        ///</summary>
        [TestMethod()]
        public void GetSnpTest()
        {
            string hecFilePath = @"C:\Users\Administrator\Desktop\333.hec"; // TODO: 初始化为适当的值
            string snpFilePath = @"C:\Users\Administrator\Desktop\777.s32p"; // TODO: 初始化为适当的值
            HecSnp expected = new HecSnp(); // TODO: 初始化为适当的值
            HecSnp actual;
            actual = DataConverter.GetSnp(hecFilePath);
            DataConverter.SaveSnp(snpFilePath,actual,32);
            Assert.AreEqual(expected, actual);
            Assert.Inconclusive("验证此测试方法的正确性。");
        }

        /// <summary>
        ///GetSnp 的测试
        ///</summary>
        [TestMethod()]
        public void GetSnpTest1()
        {
            string hecFilePath = @"C:\Users\Administrator\Desktop\333.hec"; // TODO: 初始化为适当的值
            string snpFilePath = @"C:\Users\Administrator\Desktop\777.hec"; // TODO: 初始化为适当的值
            HecSnp expected = new HecSnp(); // TODO: 初始化为适当的值
            HecSnp actual;
            actual = DataConverter.GetSnp(hecFilePath);
            DataConverter.SavePure(snpFilePath, actual);
            Assert.AreEqual(expected, actual);
            Assert.Inconclusive("验证此测试方法的正确性。");
        }
    }
}
