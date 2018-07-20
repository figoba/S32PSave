using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml.Linq;
using System.Windows.Forms.DataVisualization.Charting;
using System.Drawing;
using S32PSave.MESLabel;
using Core.DBUtility;
using System.Data.OleDb;
using System.Data;
using _32p_analyze;
using System.Net.NetworkInformation;
using DevComponents.DotNetBar;
using System.Threading;


namespace S32PSave
{
    public struct FileSaveConfig
    {
        public string savePath;
       
    }

    public struct testParams {
        public string channelName;
        public string testName;
        public int trace;
    }

    public struct plotData
    {
        public float[] xData;
        public float[] yData;
    }
    public struct MOPNCheckResult {
        public bool result;
        public string msg;
        public int MONumber;
    }
    public struct SNData {
        public string FSN;
        public string label;
        public string showDate;
        public string sn;
        public string customerData;
        public string snDec;
        public string MO;
        public string PN;
    }

    public class Util
    {
        //public static string DB_MesDataCenterConnectionString = "Provider=SQLNCLI11;Data Source=172.20.23.107;Persist Security Info=True;User ID=sa;Initial Catalog=MesDataCenter;Password=data'songyy";
        //public static string DB_HTPSDBConnectionString = "Provider=SQLNCLI11;Data Source=172.20.23.107;Persist Security Info=True;User ID=sa;Initial Catalog=HTPSDB;Password=data'songyy";

        public static string DB_MesDataCenterConnectionString = "Provider=SQLOLEDB;server=172.20.23.107,1433;Initial Catalog=MesDataCenter;uid=sa;pwd=data'songyy";
        public static string DB_HTPSDBConnectionString = "Provider=SQLOLEDB;server=172.20.23.107,1433;Initial Catalog=HTPSDB;uid=sa;pwd=data'songyy";
       
        public static string computerName = Environment.MachineName;
        public static string formatMsg(string msgIn) {
            return DateTime.Now.ToString() + "    " + msgIn;
        }
        //public static FileSaveConfig getFileSaveConfig(string xmlFilePath)
        //{
        //    XElement xe = XElement.Load(@xmlFilePath);
        //    XElement xle = (from ele in xe.Elements("FileSave") select ele).FirstOrDefault();
        //    FileSaveConfig fsc = new FileSaveConfig();
        //    fsc.savePath = xle.Element("savePath").Value;
        //    return fsc;
        //}

        //public static bool saveFileConfig(string xmlFilePath,string saveFolderPath)
        //{
        //    XElement xe = XElement.Load(@xmlFilePath);
        //    XElement xle = (from ele in xe.Elements("FileSave") select ele).FirstOrDefault();
        //    xle.Element("savePath").Value = saveFolderPath;
        //    xe.Save(xmlFilePath);
        //    return true;
        //}

        //public static bool saveSNClearConfig(string xmlFilePath, string SNClear)
        //{
        //    XElement xe = XElement.Load(@xmlFilePath);
        //    //XElement a = xe.Element("MaxTestNum");
        //    XElement xle = (from ele in xe.Elements("ClearSN") select ele).FirstOrDefault();
        //    xle.Value = SNClear;
        //    xe.Save(xmlFilePath);
        //    return true;
        //}

        //public static bool getSNClearConfig(string xmlFilePath)
        //{
        //    XElement xe = XElement.Load(@xmlFilePath);
        //    //XElement a = xe.Element("MaxTestNum");
        //    XElement xle = (from ele in xe.Elements("ClearSN") select ele).FirstOrDefault();
        //    if (xle.Value == "True")
        //    {
        //        return true;
        //    }
        //    else {
        //        return false;
        //    }
        //}

        //public static int getMaxTestNum(string xmlFilePath)
        //{
        //    XElement xe = XElement.Load(@xmlFilePath);
        //    //XElement a = xe.Element("MaxTestNum");
        //    XElement xle = (from ele in xe.Elements("MaxTestNum") select ele).FirstOrDefault();
        //    return int.Parse(xle.Value);
        //}

     
       

        public static plotData read(string FilePath)
        {
            int start = -1;
            int end = -1;
            int length = 0;
            plotData pPlotData = new plotData();
            string[] temp = File.ReadAllLines(FilePath);

            for (int i = 0; i < temp.Length; i++) {
                if (temp[i].StartsWith("%"))
                {
                    start = i;
                }
                if (temp[i].StartsWith("END"))
                {
                    end = i;
                }
            }
            if ((start == -1) || (end == -1)) {
                throw new Exception("can not find start or end from the mdf file!");
            }
            length = end - start - 1;
            float[][] arrayData = temp.Skip(start+1).Take(length).
                Select(x => x.Split(' ').Select(a => (float)Convert.ToDouble(a)).ToArray()).ToArray();
            pPlotData.xData = arrayData.Select(a => a[0]).ToArray();
            pPlotData.yData = arrayData.Select(a => a[1]).ToArray();
            return pPlotData;
        }

        public static string testChannelTrim(string source){
            string rRet = source;
            if (source.StartsWith("")) {
                rRet = source.Remove(0, 1);
            }
            if (source.EndsWith("")) {
                rRet = rRet.Remove(rRet.Length-1);
            }
            return rRet;
        }

        public static string setTestJson(string testSN,string testCount,string EEPROM) {
            string rReturn = "{\"sn\":\"" + testSN + "\",\"testCount\":\"" + testCount  + "\",\"write\":\"" + EEPROM + "\"}";
            Console.WriteLine(rReturn);
            return rReturn;
        }

        public static MOPNCheckResult MOPNCheck(string MO, string PN)
        {
            MOPNCheckResult ret = new MOPNCheckResult();
            string factoryID="LXXT";
            string profitCenter="SEE-D";
            string outPartID="";

            if (MO == "") {
                ret.result = false;
                ret.msg = "工单不能为空";
                return ret;
            }

            if (PN == "")
            {
                ret.result = false;
                ret.msg = "料号不能为空";
                return ret;
            }

            MESDataServices a = new MESDataServices();
            string retMsg=a.CheckSfcMoPN(MO, PN, factoryID, profitCenter, ref outPartID);

            if (retMsg == "OK")
            {
                if (outPartID.Contains("#"))
                {
                    ret.result = false;
                    ret.msg = "工单存在，料号不正确，正确的料号应为:" + outPartID.Split('#')[0];
                }
                else {
                    ret.result = true;
                    ret.msg = "工单料号匹配!";
                    ret.MONumber = int.Parse(outPartID);
                }
            }
            else {
                ret.result = false;
                ret.msg = retMsg;
            }
            return ret;
        }

        public static SNData getITSN(string MO, string PN)
        {
            SNData ret = new SNData();
            string stationID="HT001";
            string userID="TestID";
            string factoryID="LXXT";
            string profitCenter="SEE-D";
            string strFSN="";
            MESDataServices a = new MESDataServices();
            string b=a.GetSFCNewFSN(MO, "", stationID, true, true, userID, factoryID, profitCenter, ref strFSN);
            string[] aret = strFSN.Split('#');
            ret.FSN = strFSN;
            ret.label = slashRepalce(aret[0]);
            ret.showDate = aret[1];
            ret.sn = aret[2];
            ret.customerData = aret[3];
            ret.snDec = aret[4];
            ret.MO = MO;
            ret.PN = PN;
            return ret;
        }

        /// <summary>
        /// 获取已经保存的对应料号和工单的数量
        /// </summary>
        /// <param name="MO">工单</param>
        /// <param name="PN">料号</param>
        /// <param name="testNo">测试次数</param>
        /// <returns>已经保存的数量</returns>
        public static int getSavedNumber(string MO, string PN,int testNo)
        {
            string querySql = "SELECT count(ID) FROM S32PSave WHERE MO=? AND PN=? AND testNo=?";
            OleDbParameter[] b = new OleDbParameter[3];
            b[0] = new OleDbParameter("0", MO);
            b[1] = new OleDbParameter("1", PN);
            b[2] = new OleDbParameter("2", testNo);
           return (int)DbHelperOleDb.GetSingle(querySql, DB_MesDataCenterConnectionString, b);
        }

        private static string slashRepalce(string source) {
            StringBuilder rBuilder = new StringBuilder(source); 
            foreach (char rInvalidChar in Path.GetInvalidFileNameChars())
                rBuilder.Replace(rInvalidChar.ToString(), "-");
            return rBuilder.ToString();
        }

        public static bool saveSNRecord(SNData snData)
        {
            bool ret = false;
            string updateSql = "insert into Label_Print " +
                "([CurrentTestingLabel],[BurnedDateCode],[BurnedTimeSN],[CustomerDate],[Shijinzhisn]," +
                "[Sample],[SN],[midVar_time_date],[ReportNo],[strFSN]," +
                "[CustomerSN],[PrintCount],[PrintDate],[MO],[PN]," +
                "[Station],[Computer],[Operater],[Remark1],[Remark2],[Remark3]) " +
            "values (?,?,?,?,?" +
            ",?,?,?,?,?" +
            ",?,?,?,?,?" +
            ",?,?,?,?,?,?" +
            ")";
            OleDbParameter[] b = new OleDbParameter[21];
            b[0] = new OleDbParameter("0", snData.label);
            b[1] = new OleDbParameter("1", "");
            b[2] = new OleDbParameter("2", "");
            b[3] = new OleDbParameter("3", snData.customerData);
            b[4] = new OleDbParameter("4", snData.snDec);
            b[5] = new OleDbParameter("5", getSample(snData.sn));
            b[6] = new OleDbParameter("6", getSample(snData.sn));
            b[7] = new OleDbParameter("7", DateTime.Now.ToString());
            b[8] = new OleDbParameter("8", getReportNo(snData.sn));
            b[9] = new OleDbParameter("9", snData.FSN);
            b[10] = new OleDbParameter("10", snData.sn);
            b[11] = new OleDbParameter("11", 1);
            b[12] = new OleDbParameter("12", DateTime.Now);
            b[13] = new OleDbParameter("13", snData.MO);
            b[14] = new OleDbParameter("14", snData.PN);
            b[15] = new OleDbParameter("15", "S32P");
            b[16] = new OleDbParameter("16", Environment.MachineName);
            b[17] = new OleDbParameter("17", "Operater");
            b[18] = new OleDbParameter("18", "Remark1");
            b[19] = new OleDbParameter("19", "Remark2");
            b[20] = new OleDbParameter("20", "Remark3");

            int insertCount = DbHelperOleDb.ExecuteSql(updateSql, DB_MesDataCenterConnectionString,b);
            if (insertCount == 1) {
                ret = true;
            }
            return ret;
        }

        public static string getSample(string sn) {
            return DateTime.Now.ToString("yyyyMMdd") + sn;
        }
        public static string getReportNo(string sn)
        {
            return "HF-"+DateTime.Now.ToString("yyyyMMdd") + sn;
        }
        public static Dictionary<string, plotData> getPNSpec(string PN)
        {
            if (!PingIpOrDomainName("172.20.23.107"))
            {
                MessageBoxEx.Show("无法连接到IP地址172.20.23.107,请检查网络");
                return null;
            }
            string strSql = "select frequency from vna32port where LuxsharePN='" + PN + "'";
            DataTable dt= DbHelperOleDb.Query(strSql,DB_HTPSDBConnectionString).Tables[0];
            if (dt.Rows.Count != 1) {
                return null;
            }
            string aa = dt.Rows[0]["frequency"].ToString();
            string bb = aa.Split('\t')[0];
            var cc = bb.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries).Select(t=>t.Split('#').ToArray()).ToArray();
            Dictionary<string, plotData> ret = new Dictionary<string, plotData>();

            for (int i = 1; i < cc[0].Length; i++) {
                plotData temp = new plotData();
                List<float> x = new List<float>();
                List<float> y = new List<float>();
                for (int j = 1; j < cc.Length; j++) {
                    if (cc[j][i] != "NaN") {
                        x.Add((float)(double.Parse(cc[j][0])));
                        y.Add((float)(double.Parse(cc[j][i])));
                    }
                }
                temp.xData = x.ToArray();
                temp.yData = y.ToArray();
                ret.Add(cc[0][i].ToUpper(), temp);
            }
            return ret;
        
        }

        public static Dictionary<string, bool> judge(Dictionary<string, plotData> spec, Dictionary<string, plotData[]> data)
        {
            Dictionary<string, bool> ret = new Dictionary<string, bool>();
            foreach (var item in data) {
                bool blUpper = true;
                bool blLower = true;
                if (spec.ContainsKey(item.Key + "_UPPER")) {
                    plotData specSingle = spec[item.Key + "_UPPER"];
                    blUpper=edgeTest(item.Value, specSingle, true);
                }
                if (spec.ContainsKey(item.Key + "_LOWER"))
                {
                    plotData specSingle = spec[item.Key + "_LOWER"];
                   blLower= edgeTest(item.Value, specSingle, false);
                }
                ret.Add(item.Key, blUpper && blLower);
            }
            return ret;
        }
        #region 等同labview边界测试函数
        public static bool edgeTest(plotData[] data,plotData spec,bool isUpper) {
            for (int i = 0; i < data.Length; i++) { 
                if(!edgeTestLine(data[i],spec,isUpper)){
                    return false;
                }
            
            }

        return true;
        }
        private static bool edgeTestLine(plotData data, plotData spec, bool isUpper) {
            for (int i = 0; i < data.xData.Length; i++)
            {
                if (!edgeTestPoint(data.xData[i], data.yData[i], spec, isUpper)) {
                    return false;
                }
            }
            return true;
        }
        private static bool edgeTestPoint(double x, double y, plotData spec, bool isUpper)
        {
            for (int i = 0; i < spec.xData.Length; i++) {
                if (x == spec.xData[i]) {
                    if (isUpper) {
                        if (y >= spec.yData[i])
                        {
                            return false;
                        }
                    }else{
                         if (y <= spec.yData[i])
                        {
                            return false;
                        }
                        }
                   
                   }
               
            }
            return true;
        }
        #endregion

        public static Dictionary<string, plotData[]> 
            getDiff(Dictionary<string,string[]>testItems, string snpFilepath, SNPPort snpPort,Dictionary<string, plotData> spec,ref bool action,ref string msg)
        {
            //System.GC.Collect();
            Dictionary<string, plotData[]> ret = new Dictionary<string, plotData[]>();
            try
            {
                SNP snpClass = new SNP(snpFilepath, snpPort);
                foreach (var item in testItems)
                {
                   

                    formatedData fData = snpClass.getDiff(item.Value);
                    int columns = fData.dB.GetLength(1);
                    int rows = fData.dB.GetLength(0);
                    float[] offset = new float[rows];
                    if (spec.ContainsKey(item.Key + "_OFFSET"))
                    {
                        for (int row = 0; row < rows; row++)
                        {
                            offset[row] = spec[item.Key + "_OFFSET"].yData[row];
                        }
                    }
                    
                    plotData[] singleItem = new plotData[columns];
                    for (int curveNo = 0; curveNo < columns; curveNo++)
                    {
                        float[] y = new float[rows];
                        for (int row = 0; row < rows; row++)
                        {
                            y[row] = fData.dB[row, curveNo] + offset[row];
                        }
                        singleItem[curveNo].yData = y;
                        singleItem[curveNo].xData = fData.fre;
                        y = null;
                    }
                    ret.Add(item.Key, singleItem);
                    singleItem = null;
                    fData = new formatedData();
                }
                snpClass = null;
                //System.GC.Collect();
                action = true;
                return ret;
            }
            catch (snpException ex)
            {
                action = false;
                msg = ex.Message;
                //MessageBoxEx.Show(ex.Message);
                return null;
            }
               
           
         
           
        }

        public static string boolToString(bool bl) {
            if (bl)
            {
                return "PASS";
            }
            else {
                return "Fail";
            }
        }

        public static byte[] getBytes(string sn) {
            return System.Text.Encoding.ASCII.GetBytes(sn);

        }

        public static bool PingIpOrDomainName(string strIpOrDName)
        {
            try
            {
                Ping objPingSender = new Ping();
                PingOptions objPinOptions = new PingOptions();
                objPinOptions.DontFragment = true;
                string data = "";
                byte[] buffer = Encoding.UTF8.GetBytes(data);
                int intTimeout = 120;
                PingReply objPinReply = objPingSender.Send(strIpOrDName, intTimeout, buffer, objPinOptions);
                string strInfo = objPinReply.Status.ToString();
                if (strInfo == "Success")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception)
            {
                return false;
            }
        }

        public static bool saveConfig(config config,string savePath) {
            return Serializer.CreateXML(config, savePath);
        }
        public static config getConfig(string configPath) {
            return (config)Serializer.FromXmlString(configPath, typeof(config));
        }

        public static bool saveTestRecord(testRecord test_Record){
            bool ret = false;
           
            string updateSql =@"INSERT INTO dbo.S32PSave (
                PN, MO, testNo, sn, snType, 
                SDD21, dataCheck, result, filePath, testUser, 
                testDate, Computer, Remark1, Remark2, Remark3) 
                VALUES (
                ?, ?, ?, ?, ?, 
                ?, ?, ?, ?, ?, 
                ?, ?, ?, ?, ?)";
            OleDbParameter[] b = new OleDbParameter[15];
            b[0] = new OleDbParameter("0", test_Record.PN);
            b[1] = new OleDbParameter("1", test_Record.MO);
            b[2] = new OleDbParameter("2", test_Record.testNo);
            b[3] = new OleDbParameter("3", test_Record.sn);
            b[4] = new OleDbParameter("4", test_Record.snType.ToString());
            b[5] = new OleDbParameter("5", test_Record.SDD21.ToString());
            b[6] = new OleDbParameter("6", test_Record.dataCheck.ToString());
            b[7] = new OleDbParameter("7", test_Record.result.ToString());
            b[8] = new OleDbParameter("8", test_Record.snpFilePath);
            b[9] = new OleDbParameter("9", test_Record.testUser);
            b[10] = new OleDbParameter("10", DateTime.Now.ToString());
            b[11] = new OleDbParameter("11", computerName);
            b[12] = new OleDbParameter("12", "");
            b[13] = new OleDbParameter("13", "");
            b[14] = new OleDbParameter("14", "");
           
           

            int insertCount = DbHelperOleDb.ExecuteSql(updateSql, DB_MesDataCenterConnectionString, b);
            if (insertCount == 1)
            {
                ret = true;
            }
            return ret;
        }

        public static string GetExtension(string filePath)
        {
            //获取文件的名称
            FileInfo fi = new FileInfo(filePath);
            return fi.Extension;
        }

        public static long GetHardDiskSpace(string str_HardDiskName)
        {
            long totalSize = 0;
            str_HardDiskName = str_HardDiskName + ":\\";
            System.IO.DriveInfo[] drives = System.IO.DriveInfo.GetDrives();
            foreach (System.IO.DriveInfo drive in drives)
            {
                if (drive.Name == str_HardDiskName.ToUpper())
                {
                    totalSize = drive.TotalFreeSpace / (1024 * 1024);
                }
            }
            return totalSize;
        }

        public static bool FileIsUsing(string FilePath,int timeOutCreate,int timeOutUse,ref string msg,ref int checkTime)
        {
            DateTime start = DateTime.Now;
            bool ret = false;
            bool fileExist = false;
            int createCycleTime = 50;
            int createCycleCount = timeOutCreate / createCycleTime;

            for (int i = 0; i < createCycleCount; i++) {
                if (File.Exists(FilePath)) {
                    fileExist = true;
                    break;
                }
                Thread.Sleep(createCycleTime);
            }

            if (!fileExist) {
                ret = false;
                msg = "File: " + FilePath+" is not exist after "+timeOutCreate.ToString()+"ms";
                return ret;
            }

            int useCycleTime = 50;
            int useCycleCount = timeOutUse / useCycleTime;

            msg = "File: " + FilePath + " is still be using after " + timeOutUse.ToString() + "ms";
            for (int i = 0; i < useCycleCount; i++) {
                if (FileIsUsing(FilePath)) {
                    ret = true;
                    DateTime stop = DateTime.Now;
                    TimeSpan span = stop - start;
                    checkTime = span.Milliseconds;
                    msg = "";
                    break;
                }
                Thread.Sleep(useCycleTime);
            }

           
            return ret;

        }

        private static bool FileIsUsing(string FilePath)
        {
            bool ret = false;
            try
            {

                FileStream objFileStream = new FileStream(FilePath, FileMode.Open, FileAccess.Read, FileShare.None);
                objFileStream.Close();
                ret = true;
            }
            catch (IOException)
            {
                ret = false;
            }

            return ret;
        }
    }
}
