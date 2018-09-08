using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace S32PSave
{
    public class config
    {
        private string fileSavePath;

        public string FileSavePath
        {
            get { return fileSavePath; }
            set { fileSavePath = value; }
        }
        private int maxTestNum;

        public int MaxTestNum
        {
            get { return maxTestNum; }
            set { maxTestNum = value; }
        }
        private bool clearSN;

        public bool ClearSN
        {
            get { return clearSN; }
            set { clearSN = value; }
        }
        private int adapterIndex;

        public int AdapterIndex
        {
            get { return adapterIndex; }
            set { adapterIndex = value; }
        }
        private int comIndex;

        public int ComIndex
        {
            get { return comIndex; }
            set { comIndex = value; }
        }
        private int connectMap;

        public int ConnectMap
        {
            get { return connectMap; }
            set { connectMap = value; }
        }
        private bool writeSN;

        public bool WriteSN
        {
            get { return writeSN; }
            set { writeSN = value; }
        }
        private bool writeEEPROM;

        public bool WriteEEPROM
        {
            get { return writeEEPROM; }
            set { writeEEPROM = value; }
        }
        private string port;

        public string Port
        {
            get { return port; }
            set { port = value; }
        }
        private string calPath;

        public string CalPath
        {
            get { return calPath; }
            set { calPath = value; }
        }

      
        private bool calFileEnable;

        public bool CalFileEnable
        {
            get { return calFileEnable; }
            set { calFileEnable = value; }
        }

        private int skin;

        public int Skin
        {
            get { return skin; }
            set { skin = value; }
        }
        private string visaAddress;

        public string VisaAddress
        {
            get { return visaAddress; }
            set { visaAddress = value; }
        }
        private int resolutionIndex;

        public int ResolutionIndex
        {
            get { return resolutionIndex; }
            set { resolutionIndex = value; }
        }
        private int moTolerance;

        public int MoTolerance
        {
            get { return moTolerance; }
            set { moTolerance = value; }
        }

        public string TxtSaveFolder
        {
            get { return txtSaveFolder; }
            set { txtSaveFolder = value; }
        }

        private string txtSaveFolder;


    }

    #region 数据库测试记录
    public enum SNType { 
        ITAutoGet,
        ReadFromEEPROM,
        ManualInput
     }
    public enum itemTestResult{
        PASS,
        Fail,
        None
    }
    
    public struct testRecord {
        public string PN;
        public string MO;
        public int testNo;
        public string sn;
        public SNType snType;
        public itemTestResult SDD21;
        public itemTestResult dataCheck;
        public itemTestResult result;
        public string snpFilePath;
        public string testUser;
        public DateTime testTime;
     
    }
    #endregion
}
    