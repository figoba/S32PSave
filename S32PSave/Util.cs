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
using System.Reflection;
using System.Text.RegularExpressions;
using DevComponents.DotNetBar;
using System.Threading;
using System.Windows.Forms.VisualStyles;
using System.Xml;
using ICSharpCode.SharpZipLib.Zip;


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

    public struct TDD
    {
        public string startTime;
        public string stopTime;
        public int points;
        public string riseTime;
        public string offset;
        public string impedance;

    }

    public struct ReportInformation
    {
        public string application;
        public string partDescription;
        public string partNo;
        public string fixtureSerialNo;
        public string reportNo;
        public string sampleNo;
        public string preparedBy;
        public string approvedBy;
        public string temprature;
        public string rHumidity;
        public string date;
        public string tdrModel;
        public string vnaModel;
    }

    public class Util
    {
#if DEBUG
        public static string DB_MesDataCenterConnectionString = "Provider=SQLNCLI11;Data Source=172.20.23.107;Persist Security Info=True;User ID=sa;Initial Catalog=MesDataCenter;Password=data'songyy";
        public static string DB_HTPSDBConnectionString = "Provider=SQLNCLI11;Data Source=172.20.23.107;Persist Security Info=True;User ID=sa;Initial Catalog=HTPSDB;Password=data'songyy";
#else
        public static string DB_MesDataCenterConnectionString = "Provider=SQLOLEDB;server=172.20.23.107,1433;Initial Catalog=MesDataCenter;uid=sa;pwd=data'songyy";
        public static string DB_HTPSDBConnectionString = "Provider=SQLOLEDB;server=172.20.23.107,1433;Initial Catalog=HTPSDB;uid=sa;pwd=data'songyy";

#endif


       
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

        //public static bool saveFileConfig(string xmlFilePath,string pnSaveFolderPath)
        //{
        //    XElement xe = XElement.Load(@xmlFilePath);
        //    XElement xle = (from ele in xe.Elements("FileSave") select ele).FirstOrDefault();
        //    xle.Element("savePath").Value = pnSaveFolderPath;
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
            ret.label = aret[0];
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

        public static string slashRepalce(string source) {
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

        public static TDD[] getTdd(string tdr)
        {
            TDD[]ret=new TDD[2];
            
            string[] temp = tdr.Split('\t');
            ret[0].startTime = temp[0];
            ret[0].stopTime = temp[1];
            ret[0].points = (int)double.Parse(temp[2]);
            ret[0].riseTime = temp[3];
            ret[0].offset = temp[4];
            ret[0].impedance = temp[7];
            if ((int)double.Parse(temp[10]) == 1)
            {
                ret[1].startTime = temp[8];
                ret[1].stopTime = temp[9];
                ret[1].points = (int)double.Parse(temp[10]);
                ret[1].riseTime = temp[11];
                ret[1].offset = temp[12];
                ret[1].impedance = temp[15];
            }
            else
            {
                ret[1] = ret[0];
            }

            return ret;
        }

        public  static plotData[]  GetTddSpec(TDD tdd)
        {
            plotData[] ret=new plotData[2];
            double step = (float.Parse(tdd.stopTime) - float.Parse(tdd.startTime))/(tdd.points-1);
            float[] timeArray=new float[tdd.points];
            //for (int i = 0; i < timeArray.Length; i++)
            //{
            //    timeArray[i] = i * step;
            //}
            var cc = tdd.impedance.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries).Select(t => t.Split('#').ToArray()).ToArray();
            double upperPoint1 = double.Parse((cc[0][1]));
            double upperPoint2 = double.Parse((cc[1][1]));
            double upperPoint3 = (double.Parse(tdd.stopTime) - upperPoint2) / 2 + upperPoint2;
            double upperValue1 = double.Parse((cc[0][2]));
            double upperValue2 = double.Parse((cc[1][2]));

            double lowerPoint1 = double.Parse((cc[0][3]));
            double lowerPoint2 = double.Parse((cc[1][3]));
            double lowerPoint3 = (double.Parse(tdd.stopTime) - lowerPoint2) / 2 + lowerPoint2;
            double lowerValue1 = double.Parse((cc[0][4]));
            double lowerValue2 = double.Parse((cc[1][4]));


            List<float> x = new List<float>();
            List<float> y = new List<float>();
            double pointX = upperPoint1;
            while (pointX<=upperPoint2)
            {
                x.Add(float.Parse(pointX.ToString()));
                y.Add(float.Parse(upperValue1.ToString()));
                pointX = pointX + step;
            }
            while (pointX <= upperPoint3)
            {
                x.Add(float.Parse(pointX.ToString()));
                y.Add(float.Parse(upperValue2.ToString()));
                pointX = pointX + step;
            }

            ret[0].xData = x.ToArray();
            ret[0].yData = y.ToArray();

            x.Clear();
            y.Clear();
            pointX = lowerPoint1;
            while (pointX <= lowerPoint2)
            {
                x.Add(float.Parse(pointX.ToString()));
                y.Add(float.Parse(lowerValue1.ToString()));
                pointX = pointX + step;
            }
            while (pointX <= lowerPoint3)
            {
                x.Add(float.Parse(pointX.ToString()));
                y.Add(float.Parse(lowerValue2.ToString()));
                pointX = pointX + step;
            }
            ret[1].xData = x.ToArray();
            ret[1].yData = y.ToArray();
            return ret;
        }

        public static Dictionary<string, plotData> getPNSpec(string PN,ref TDD[] tdds,ref string description)
        {
            if (!PingIpOrDomainName("172.20.23.107"))
            {
                MessageBoxEx.Show("无法连接到IP地址172.20.23.107,请检查网络");
                return null;
            }
            string strSql = "select frequency,TDR,general from vna32port where LuxsharePN='" + PN + "'";
            DataTable dt= DbHelperOleDb.Query(strSql,DB_HTPSDBConnectionString).Tables[0];
            if (dt.Rows.Count != 1) {
                return null;
            }
            string frequency = dt.Rows[0]["frequency"].ToString();
            string tdr = dt.Rows[0]["TDR"].ToString();
            string general = dt.Rows[0]["general"].ToString();
            description = general.Split('\t')[5];
            tdds = getTdd(tdr);
            plotData[] tdd1 = GetTddSpec(tdds[0]);
            plotData[] tdd2 = GetTddSpec(tdds[1]);
            string bb = frequency.Split('\t')[0];
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
            ret.Add("TDD11_UPPER",tdd1[0]);
            ret.Add("TDD11_LOWER", tdd1[1]);
            ret.Add("TDD22_UPPER", tdd2[0]);
            ret.Add("TDD22_LOWER", tdd2[1]);
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

        public static float[,] GetSavedTxtFromPlotDataArray(plotData[] plotDatas)
        {
            int row = plotDatas[0].yData.Length;
            int col = plotDatas.Length + 1;
            float[,]ret=new float[row,col];
            for (int i = 0; i < row; i++)
            {
                for (int j = 1; j < col; j++)
                {
                    ret[i, j] = plotDatas[j - 1].yData[i];
                }
            }

            for (int i = 0; i < row; i++)
            {
                ret[i, 0] = plotDatas[0].xData[i];
            }
             return ret;
        }

        public static bool Save2DArrayToTxt<T>(T[,] data, string savePath)
        {
            bool ret = true;
            try
            {
                int col = data.GetLength(1);
                var enumerator = data.Cast<T>()
                    .Select((s, i) => (i + 1) % col == 0 ? string.Concat(s, Environment.NewLine) : string.Concat(s, "\t"));

                var item = String.Join("", enumerator.ToArray<string>());
                File.AppendAllText(savePath, item);

            }
            catch (Exception e)
            {
                ret = false;
             }

            return ret;
        }

        public static Dictionary<string, bool> dataSave(string saveFolder, Dictionary<string, plotData[]> data)
        {
            Dictionary<string, bool> ret = new Dictionary<string, bool>();
            if (!Directory.Exists(saveFolder))
            {
                Directory.CreateDirectory(saveFolder);//创建该文件夹
            }
            foreach (var VARIABLE in data)
            {
                string testItem = VARIABLE.Key;
                string savePath = @saveFolder+"\\" + testItem + ".txt";
                ret.Add(testItem, Save2DArrayToTxt(GetSavedTxtFromPlotDataArray(data[testItem]), savePath)); ;
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
            getAnalyzedData(string[] testItems, string snpFilepath, SNPPort snpPort, Dictionary<string, plotData> spec, 
                TDD[] tdds ,
                ref bool action, ref string msg,ref Dictionary<string,string[]> pairNameDictionary)
        {
            int pairNum = 8;
            pairNameDictionary.Clear();
            string[] pairNames = new string[pairNum];
            Dictionary<string, plotData[]> ret = new Dictionary<string, plotData[]>();
            try
            {
                SNP snpClass = new SNP(snpFilepath, snpPort);
                foreach (string item in testItems)
                {
                    if (item.StartsWith("T"))
                    {
                        TDD tdd = item.ToUpper().Equals("TDD11") ? tdds[0] : tdds[1];
                        timeDomainData tData = snpClass.EasyGetTimeData(item, out pairNames, double.Parse(tdd.riseTime), (double.Parse(tdd.stopTime) - double.Parse(tdd.startTime)) / (tdd.points - 1), tdd.points, double.Parse(tdd.offset));
                        int tColumns = tData.resistance.GetLength(1);
                        int tRows = tData.resistance.GetLength(0);
                        float[] offset = new float[tRows];
                        if (spec.ContainsKey(item + "_OFFSET"))
                        {
                            for (int row = 0; row < tRows; row++)
                            {
                                offset[row] = spec[item + "_OFFSET"].yData[row];
                            }
                        }

                        plotData[] tItem = new plotData[tColumns];
                        for (int curveNo = 0; curveNo < tColumns; curveNo++)
                        {
                            float[] y = new float[tRows];
                            for (int row = 0; row < tRows; row++)
                            {
                                y[row] = tData.resistance[row, curveNo] + offset[row];
                            }
                            tItem[curveNo].yData = y;
                            tItem[curveNo].xData = tData.time;
                            y = null;
                           
                        }

                        ret.Add(item, tItem);
                        pairNameDictionary.Add(item, pairNames);

                    }
                    else if (item.Equals("SINGLE"))
                    {
                        string[] pairNameSingles = new[]
                        {
                            "S1_17","S2_18","S3_19","S4_20",
                            "S5_21","S6_22","S7_23","S8_24",
                            "S9_25","S10_26","S11_27","S12_28",
                            "S13_29","S14_30","S15_31","S16_32"
                        };
                        formatedData sfData = snpClass.getSingle(pairNameSingles);
                        int sColumns = sfData.dB.GetLength(1);
                        int sRows = sfData.dB.GetLength(0);
                        plotData[] singleItem = new plotData[sColumns];
                        for (int curveNo = 0; curveNo < sColumns; curveNo++)
                        {
                            float[] y = new float[sRows];
                            for (int row = 0; row < sRows; row++)
                            {
                                y[row] = sfData.dB[row, curveNo];
                            }
                            singleItem[curveNo].yData = y;
                            singleItem[curveNo].xData = sfData.fre;
                            y = null;
                        }
                        ret.Add(item, singleItem);
                        pairNameDictionary.Add(item, pairNameSingles);
                      }
                    else
                    {
                        
                        formatedData fData = snpClass.EasyGetfreData(item, out pairNames);
                        int columns = fData.dB.GetLength(1);
                        int rows = fData.dB.GetLength(0);
                        float[] offset = new float[rows];
                        if (spec.ContainsKey(item + "_OFFSET"))
                        {
                            for (int row = 0; row < rows; row++)
                            {
                                offset[row] = spec[item + "_OFFSET"].yData[row];
                            }
                        }

                        plotData[] diffItem = new plotData[columns];
                        for (int curveNo = 0; curveNo < columns; curveNo++)
                        {
                            float[] y = new float[rows];
                            for (int row = 0; row < rows; row++)
                            {
                                y[row] = fData.dB[row, curveNo] + offset[row];
                            }
                            diffItem[curveNo].yData = y;
                            diffItem[curveNo].xData = fData.fre;
                            y = null;
                        }
                        ret.Add(item, diffItem);
                        diffItem = null;
                        fData = new formatedData();
                        pairNameDictionary.Add(item, pairNames);
                    }


                }
                snpClass = null;
                //System.GC.Collect();
                action = true;
                return ret;
            }
            catch (SnpException ex)
            {
                action = false;
                msg = ex.Message;
                //MessageBoxEx.Show(ex.Message);
                return null;
            }

        }

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
            catch (SnpException ex)
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

        public static bool SaveTestResult(Dictionary<string, bool> results, ReportInformation reportInformation, string saveFolder)
        {
            bool ret = true;
            try
            {
                StringBuilder xmlHead = new StringBuilder("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n<general>\r\n<testResult>\r\n");
                string singleItem = "<testItem name=\"@item\" result=\"@result\"/> ";
                string singleTail = "</testResult>\r\n";

                string inforHead = "<information>";
                string singleInforItem = "<inforItem name=\"@item\" value=\"@value\"/>";
                string xmlTail = "</information>\r\n</general>";

                StringBuilder temp = new StringBuilder();
                foreach (var result in results)
                {
                    xmlHead.Append(singleItem.Replace("@item", result.Key).Replace("@result", result.Value ? "OK" : "NG"));

                }

                xmlHead.Append(singleTail);
                xmlHead.Append(inforHead);
                foreach (FieldInfo fieldInfo in reportInformation.GetType().GetFields())
                {
                    xmlHead.Append(singleInforItem.Replace("@item", fieldInfo.Name)
                    .Replace("@value", fieldInfo.GetValue(reportInformation).ToString()));
                 }

                xmlHead.Append(xmlTail);
                File.WriteAllText(saveFolder + "\\Result & Sample info.xml", FormatXml(xmlHead.ToString()));
            }
            catch (Exception e)
            {
                ret = false;
                Console.WriteLine(e);
                //throw;
            }

            return ret;
        }

        private static string FormatXml(string sUnformattedXml)
        {
            XmlDocument xd = new XmlDocument();
            xd.LoadXml(sUnformattedXml);
            StringBuilder sb = new StringBuilder();
            StringWriter sw = new StringWriter(sb);
            XmlTextWriter xtw = null;
            try
            {
                xtw = new XmlTextWriter(sw);
                xtw.Formatting = Formatting.Indented;
                xtw.Indentation = 1;
                xtw.IndentChar = '\t';
                xd.WriteTo(xtw);
            }
            finally
            {
                if (xtw != null)
                    xtw.Close();
            }

            return sb.ToString();
        }

        public enum DataType
        {
            Next,
            TxtSource,
            Fext,
            Txt,
            Summary,
            EEPROM

        }
        public static bool zipTxt(string txtDataSourceFolder, string zipFileName, DataType dataType)
        {
            bool ret = true;
          
            try
            {
                List<string>txtList=new List<string>();
                string[] txtFiles = Directory.GetFiles(txtDataSourceFolder).Select(fullPath => Path.GetFileName(fullPath)).ToArray();
                switch (dataType)
                {
                    case    DataType.Next:
                        txtList.Add(txtDataSourceFolder+"\\"+"next.txt");
                       
                        break;
                    case DataType.Fext:
                        txtList.Add(txtDataSourceFolder+"\\"+"fext.txt");
                        
                        break;
                    case DataType.TxtSource:
                        txtList = txtFiles.Select(filename => txtDataSourceFolder + "\\" + filename).ToList();
                        
                        break;
                    case DataType.Txt:
                        string pattern = @"^S|^T|^I";
                        foreach (string fileName in txtFiles)
                        {
                            Match m = Regex.Match(fileName.ToUpper(), pattern);
                            if (m.Success)
                            {
                                txtList.Add(txtDataSourceFolder+"\\"+fileName);
                            }
                        }
                       
                        break;
                    case DataType.EEPROM:
                        foreach (string fileName in txtFiles)
                        {
                            if (fileName.StartsWith("EEPROM"))
                            {
                                txtList.Add(txtDataSourceFolder+"\\"+fileName);
                            }
                        }
                        
                        break;
                    case  DataType.Summary:
                        txtList.Add("summary.txt");
                        
                        break;
                   
                         }

                ret=SharpZip.CompressFile(txtList, zipFileName);

            }
            catch (Exception e)
            {
                ret = false;
            }

            return ret;
        }

      
        public static void ziptest()
        {
            string[] lists = new[]
            {
                @"D:\gitProjects\S32PSave\S32PSave\bin\x86\Debug\report\figo11\SN-2222\txt\1\Result & Sample info.xml"
            };
            SharpZip.CompressFile(lists, "B:\\myzip.zip");

          
         
        }


    }
}
