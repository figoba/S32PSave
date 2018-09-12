using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AgilentPNA835x;
using DevComponents.DotNetBar;
using DevComponents.DotNetBar.Metro;
using System.Diagnostics;
using System.Threading;
using System.IO;
using System.Net;
using System.Net.Sockets;
using virtualIIC;
using System.IO.Ports;
using _32p_analyze;
using System.Windows.Forms.DataVisualization.Charting;
using DevComponents.DotNetBar.Controls;
using Ivi.Visa.Interop;
using Application = System.Windows.Forms.Application;


namespace S32PSave
{
    public partial class frmMain : MetroForm
    {
        #region server
        private System.Net.Sockets.Socket sock, accSock;
        private IPAddress myIP = IPAddress.Parse("127.0.0.1");
        private IPEndPoint MyServer;
        Thread threadServer;
        Thread threadCheck;
        private bool check = true;
        Size _beforeDialogSize;
        #endregion 

        #region EEPROM
       
        public static int DeviceInd = 0;//串口顺序号
        const int writeBufferSize = 8;
        const GYI2CType GYIDeviceType = GYI2CType.DEV_GY7604;
        public int LuxshareIICTimeOut = 50;     //立讯盒子写数据延时参数，单位ms
        const int CP2102DeviceNum = 1;          
        const int CP2102TImeOut = 1000;         //CP2102超时时间
        private i_I2C I2CDevice = new VCI_GYI2C(GYIDeviceType, DeviceInd, writeBufferSize);
        private SerialPort comm = new SerialPort();
        const int SlaveAddr = 0xA0;//设备物理地址， bit7-1 有效
        #endregion

        readonly Stopwatch swTimeUse = new Stopwatch();
        

        #region SI
        Dictionary<string, plotData> spec = new Dictionary<string, plotData>();
        public static string[][] freSpec ;
        public static string TDDSpec;
        TDD[]tdds=new TDD[2];
        private string PNDescription = "";
        public bool calibrated = false;
        public SNPPort snpPort = SNPPort.X1234;
        #endregion

        public static bool clearSN;
        public static string s32pSaveFolder;//全部32p保存文件夹
        public string pnSaveFolderPath = "";//对应料号创建的文件夹
        public static string txtSaveFolder = "";//分析的数据保存路径

        
        public string volume = "";      //保存S32P文件所在的磁盘
        public string saveS32pPath = "";//生成的S32P文件保存路径
        public static int maxTestNum;
        public static  bool blUpload;   //是否上传数据到数据库
        public static bool blSaveTxt;   //是否保存分析数据

        public bool PN_change = false;

        AgilentPNA835x.Application PNA835;
        
        public string visaAddress = "";
        
        IScpiStringParser2 scpiParser;
        public string channelSelStr = "";
        public string channelSel = "";
       
        public int testNo = -1;
        public string testPN = "";
        public string testMO = "";
        public string Resolution = "";
        public const string configFilePath = "config.xml";
        public int MONumber = -1;//工单数量
        public int MOTolerance=20;//工单数量误差百分比
        public Dictionary<string, testParams> testparamList;

        public Dictionary<string, Chart> chartDic = new Dictionary<string, Chart>();
        /// <summary>
        /// dbRecord:数据库记录字段
        /// 
        /// Summary
        /// 0:PN
        /// 1:preLabel
        /// 2:ProductSN
        /// 3:ResultString
        /// 4:Result
        /// 5:Applicant
        /// 6:Tester
        /// 7:Approver
        /// 8:Date
        /// 9:Time
        /// 10:Machine
        ///
        /// detailResult
        /// 11:EEPROMRes
        /// 12:ReportTF
        /// 13:ThruTF
        /// 14:NextTF
        /// 15:FextTF
        /// 16:TxtTF
        /// 17:ExcelTF
        /// 18:PdfTF
        ///
        /// detailFile
        /// 19:ThruData
        /// 20:ThruTXTData
        /// 21:NextData
        /// 22:NextTXTData
        /// 23:FextData
        /// 24:FextTXTData
        /// 25:TxtData
        /// 26:PDFData
        /// 27:EEPROMData
        /// 28:SummaryData
        ///
        /// detailSN
        /// 29:Itsn
        /// 30:Eprm_datacode
        /// 31:Eprm_dataandsn
        /// 32:Itsn_really
        /// 33:Label_Date
        /// 34:Label_sn
        /// 35:Decimal_sn
        /// 36:MO
        ///
        /// Other
        /// 37:RetestReason
        /// 38:TestType
        /// 39:LineID
        /// 40:QAMark
        ///
        /// 涉及函数
        /// setDetailSN
        /// DBRecord_ini
        /// DBRecord_get
        /// LabelPrint
        /// </summary>
        public string[] dbRecord=new string[41];

        
        public frmMain()
        {
            InitializeComponent();
        }

        private enum TestStatus
        {
            Fail,
            Pass,
            Working
        }

        private void StatusSet(TestStatus testStatus)
        {
            switch (testStatus)
            {
                case TestStatus.Fail:
                    swTimeUse.Stop();
                    setResult("Fail",Color.Red);
                    setStart(true);
                    break;
                case TestStatus.Pass:
                    setResult("PASS",Color.Green);
                    break;
                case TestStatus.Working:
                    setResult("Working",Color.Blue);
                    break;

            }
           
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
#if !DEBUG
            if (!diskFreeSpaceCheck()) {
                MessageBoxEx.Show("磁盘剩余空间不足1G，请清理后再测试！");
                return;
            }

#endif           
            addStatus("start test");
            swTimeUse.Start();
            setCableStatus("");
            setProgress(0, false);
            setStart(false);
            
            setProgress(3, false);
            if (!snCheck())
                return;

            if (!writeSN())
                return;
           
            StatusSet(TestStatus.Working);
            setProgress(45, false);
            timer1.Enabled = true;
            addStatus("start get S32P");

            Thread threadGetS32p = new Thread(new ThreadStart(getS32P_EventStyle));
            threadGetS32p.Start();

        }

        private void frmMain_Load(object sender, EventArgs e)
        {
         
            testItemCheckBoxIni();
            setCableStatus("");
            btn_Calibrate.Enabled = false;
            skinStyle_ini();
            getSerialPorts();
            cmbAdapter.SelectedIndex = 0;
            if (!readConfig()) {
                MessageBoxEx.Show("read config file error!");
            }
            cmbTestNo_ini();
            
            setStart(false);
            rbtPort1.Checked = true;
            labelX2.ForeColor = Color.DarkOliveGreen;//标题颜色
            labelResult.Text = "";

            S32PSaveFolderCheck();
            PNASettingCheck();
            AutoScale(this);
          
        }

        /// <summary>
        /// 写入SN到EEPROM
        /// </summary>
        /// <returns></returns>
        private bool writeSN()
        {
            if (chkWriteSN.Checked)
            {
                if (!writeSN(textSN.Text.Trim()))
                {
                    MessageBoxEx.Show("写入SN失败，请确认烧录盒子或线缆连接是否OK后再重试");
                    labelResult.Text = "Fail";
                    labelResult.BackColor = Color.Red;
                    setStart(true);
                  
                    return false;
                }
                setProgress(15, false);
            }

            return true;
        }

        /// <summary>
        /// 获取SN及SN检查，并且给saveS32pPath赋值
        /// </summary>
        /// <returns></returns>
        private bool snCheck()
        {
            if (chkAutoSN.Checked)
            {
                if (!getSN(txtMO.Text.Trim(), textPN.Text.Trim()))
                {
                    return false;
                }
                setProgress(5, false);
                
            }
            else
            {
                if (textSN.Text.Trim().Equals(""))
                {
                    labelResult.Text = "Fail";
                    labelResult.BackColor = Color.Red;
                    setStart(true);
                   
                    MessageBoxEx.Show("SN不能为空");
                    return false;
                }

                
            }
            saveS32pPath = pnSaveFolderPath + "\\" + Util.slashRepalce(textSN.Text) + "_" + cmbTestNo.Text + ".s32p";
            return true;
        }

        private void S32PSaveFolderCheck()
        {
            if (!Directory.Exists(@s32pSaveFolder))
            {
                MessageBoxEx.Show("path:" + s32pSaveFolder + " not exist");
                MessageBoxEx.Show("This application will auto create this path");
                Directory.CreateDirectory(s32pSaveFolder);//创建该文件夹
            }

            if (!Directory.Exists(txtSaveFolder))
            {
                if (string.IsNullOrWhiteSpace(txtSaveFolder))
                {
                    MessageBoxEx.Show("txt save path is emputy,will use default folder: report");
                    txtSaveFolder =Application.StartupPath+"\\"+ "report";
                }

                
                //MessageBoxEx.Show("txt save path:" + txtSaveFolder + " not exist");
                Directory.CreateDirectory(txtSaveFolder);//创建该文件夹
            }
            volume = s32pSaveFolder.Substring(0, s32pSaveFolder.IndexOf(':'));
        }

       

        /// <summary>
        /// PNA档案检查
        /// </summary>
        private void PNASettingCheck()
        {
#if !DEBUG
            PNA835 = new AgilentPNA835x.Application();
            scpiParser = (IScpiStringParser2)PNA835.ScpiStringParser;
            testparamList = getTestParas();

            if (!testparamList.ContainsKey("Sdd21"))
            {
                MessageBoxEx.Show("the csa file did not contain Sdd21!");
            }

            testParams Sdd21 = testparamList["Sdd21"];

            string firstChannel = "";
            foreach (string key in testparamList.Keys)
            {
                if (testparamList[key].trace == 0)
                {
                    firstChannel = key;
                    break;
                }
            }

            channelSelStr = "CALC:PAR:SEL '" + testparamList[firstChannel].channelName + "'";
            channelSel = (Sdd21.trace + 1).ToString();
#endif
        }

        #region event style getS32P and analyze

        private void getS32P_EventStyle()
        {
            PNASaver a = new PNASaver();
            a.saveBefore += On_SaveBefore;
            a.pnaConnectChecked += On_PNAConnectChecked;
            a.saveFinished += On_SaveFinished;
            a.saveS32p(saveS32pPath, saveS32pPath, Resolution);
        }
        private void On_SaveBefore(string S32pFile)
        {
            sendWriting();
        }

        private void On_PNAConnectChecked(bool connected)
        {
            if (!connected)
            {
                MessageBoxEx.Show("请先连接PNA设备");
                StatusSet(TestStatus.Fail);
                setStart(true);
            }
            
            addStatus("start PLTS");
        }
        private void On_SaveFinished(string S32pFile)
        {
            addStatus("finished get S32P");
            setCableStatus("请拔出线缆");
          
           
            setProgress(170, false);
            Dictionary<string, bool> results = new Dictionary<string, bool>();
            bool checkResult = false;
            bool nextTF = false;
            bool fextTF = false;
            string testSN = null;
            if (!calibrated)
            {
                addStatus("start calibrate");
                calibrated = s32pAnalyze(saveS32pPath, snpPort, spec, textPN.Text.Trim(), ref results);
                setDisplayCaliresult();
            }
            else
            {
                string testResult = "";
                if (chartDic.Count>0)
                {
                    addStatus("data check set true,start data check");
                    checkResult = s32pAnalyze(S32pFile, snpPort, spec, textPN.Text.Trim(), ref results);
                    textSN.Invoke(new MethodInvoker(() =>
                    {
                        testSN = textSN.Text;
                    }));
                   // DBRecord_get(testSN,testNo,checkResult,)
                    testResult = setDisPlayResult(checkResult);
                    nextTF = results.ContainsKey("NEXT");
                    fextTF = results.ContainsKey("FEXT");
                }
                else
                {
                    addStatus("data check set false, data check cancel");
                    StatusSet(TestStatus.Pass);
                  }

                saveTestRecord(testResult);
                setStart(true);
            }

            timer1.Enabled = false;
            addStatus("timer set false");
            setProgress(200, false);

            swTimeUse.Stop();
            TimeSpan ts2 = swTimeUse.Elapsed;
            addStatus("used time is:" + ts2.TotalMilliseconds + " ms");
            swTimeUse.Reset();


            if (calibrated)
            {
                DBRecord_get(testSN, testNo, checkResult, (int)ts2.TotalSeconds, "EEPROM:None", nextTF, fextTF);
                string txtDataFolder = txtSaveFolder + "\\" + testPN + "\\SN-" + Util.slashRepalce(testSN) + "\\txt\\" + testNo;
                if (blSaveTxt)
                {

                    Util.SaveTestResult(results, GetReportInformation(), txtDataFolder);
                    saveTDDSpecData(txtDataFolder + "\\" + "Impedance Spec.txt");
                    saveFreData(txtDataFolder + "\\" + "Freq Spec.txt");
                }

                if (blUpload)
                {
                    getUpload1(testSN, txtDataFolder);
                    //zipData(txtDataFolder);
                    //getSummary(txtDataFolder+"\\Upload1",Util.slashRepalce(testSN));
                    getUpload2(testSN,txtDataFolder + "\\Upload2");
                }
            }
           
            sendTCPAnalyzeCMD();


            if (clearSN)
            {
                clearSNtext();
             
            }

            setSNFocus();

      
        }

        
        private void saveChart(Chart chart)
        {
            chart.Invoke(new MethodInvoker(() => { chart.SaveImage(@"B:\22.emf", ChartImageFormat.Emf); }));
        }

        #endregion
        

        private  bool saveTDDSpecData(string savePath)
        {
            bool ret = true;
            try
            {
               File.WriteAllText(savePath, TDDSpec);
            }
            catch (Exception e)
            {
                ret = false;
            }

            return ret;
        }
        private  bool saveFreData(string savePath)
        {
            bool ret = true;
            try
            {
                var enumerator = freSpec.Select(s => string.Join("\t", s.Skip(1))).ToArray();
                var allText = string.Join(Environment.NewLine, enumerator);

                File.WriteAllText(savePath, allText);
            }
            catch (Exception e)
            {
                ret = false;
            }

            return ret;
        }
        private bool getUpload1(string sn, string txtDataFolder)
        {
            if (zipData(txtDataFolder))
            {
                return getSummary(txtDataFolder + "\\Upload1", Util.slashRepalce(sn));
            }
            else
            {
                return false;
            }
            
        }

        private bool getUpload2(string sn,string upload2Folder)
        {
            bool ret = false;
            string[] temp = new string[6];
            temp[0] = testPN;
            temp[1] = sn;
            temp[2] = "L037047";
            temp[3] = DateTime.Now.ToString("hh:mm:ss yyyy/MM/dd");
            temp[4] = dbRecord[4];//test result PASS,FAIL
            temp[5] = "P#" + sn + "#s.zip";
            try
            {
                string txtPath = upload2Folder + "\\P#" + sn + "#s.txt";
                string zipPath = upload2Folder + "\\P#" + sn + "#s.zip";
                if (!Directory.Exists(upload2Folder))
                {
                    Directory.CreateDirectory(upload2Folder);
                }
                File.WriteAllText(txtPath,string.Join(";",temp));
                ret=SharpZip.CompressFile(txtPath, zipPath);
            }
            catch (Exception e)
            {
                ret = false;
            }

            return ret;
        }
        private bool getSummary(string summaryFolder,string sn)
        {
            bool ret = true;
            try
            {
                File.WriteAllText(summaryFolder + "\\P#" + sn+"v.txt", string.Join(";", dbRecord));
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                ret = false;
            }

            return ret;
        }
        private bool zipData(string txtDataSource)
        {
            bool ret = true;
            string[] zipFiles = new string[6];
            Util.DataType[] zipTypes=new Util.DataType[6];
            zipFiles[0] = dbRecord[19];//ThruData
            zipFiles[1] = dbRecord[22];//NextTXTData
            zipFiles[2] = dbRecord[24];//FextTXTData
            zipFiles[3] = dbRecord[25];//TxtData
            zipFiles[4] = dbRecord[27];//EEPROMData
            zipFiles[5] = dbRecord[28];//SummaryData

            zipTypes[0] = Util.DataType.TxtSource;
            zipTypes[1] = Util.DataType.Next;
            zipTypes[2] = Util.DataType.Fext;
            zipTypes[3] = Util.DataType.Txt;
            zipTypes[4] = Util.DataType.EEPROM;
            zipTypes[5] = Util.DataType.Summary;

            for (int i = 0; i < 6; i++)
            {
                if (zipFiles[i] != "NULL")
                {
                    ret = ret && Util.zipTxt(txtDataSource, txtDataSource + "\\Upload1\\" + zipFiles[i], zipTypes[i]);
                }
                
            }

            return ret;
        }

/// <summary>
        /// remote control command send to labview analyze software
        /// </summary>
        private void sendTCPAnalyzeCMD()
        {
            if (accSock != null)
            {
                if (accSock.Connected)
                {
                    string Msg = Util.setTestJson(textSN.Text, cmbTestNo.Text, "0");
                    addStatus("start send TCP/IP....");
                    sendMsg(Msg);
                    addStatus("TCP/IP send finish");

                }

            }
        }
        private void sendWriting()
        {
            if (accSock != null && chkEEPROM.Checked)
            {
                if (accSock.Connected)
                {
                    string Msg = Util.setTestJson(textSN.Text, cmbTestNo.Text, "1");
                    addStatus("start EEPROM Writing....");
                    sendMsg(Msg);
                }
            }
        }

        #region unUsed getS32P

        private void getS32p()
        {
          
#if !DEBUG
   
            PLTS plts = new PLTS();
            if (!plts.Connected)
            {
                plts.Connect(visaAddress);
            }
            if (!plts.Connected)
            {
                MessageBoxEx.Show("请先连接PNA设备");
                StatusSet(TestStatus.Fail);
                setStart(true);
            }


            addStatus("start PLTS");
            plts.CloseAllFiles();
            plts.MeasureS32pFile();

            int fileNumber = plts.GetActiveFileIndex();
            
            if (File.Exists(saveS32pPath))
            {
                File.Delete(saveS32pPath);
            }
            plts.ExportFile(fileNumber, 32, saveS32pPath, cmbResolution.SelectedItem.ToString());
            plts.Disconnect();
           
#endif


            addStatus("finished get S32P");
            setCableStatus("请拔出线缆");
          
            timer1.Enabled = false;
            addStatus("timer set false");
            setProgress(170, false);
            Dictionary<string, bool> results = new Dictionary<string, bool>();
            if (!calibrated)
            {
                addStatus("start calibrate");
                calibrated = s32pAnalyze(saveS32pPath, snpPort, spec, textPN.Text.Trim(), ref results);
                setDisplayCaliresult();
            }
            else
            {
                string testResult = "";
                if (chartDic.Count>0)
                {
                    addStatus("data check set true,start data check");
                    bool checkResult = s32pAnalyze(saveS32pPath, snpPort, spec, textPN.Text.Trim(), ref results);
                    string testSN = null;
                    textSN.Invoke(new MethodInvoker(() =>
                    {
                        testSN = textSN.Text;
                    }));
                   // DBRecord_get(testSN,testNo,checkResult,)
                    testResult = setDisPlayResult(checkResult);
                }
                else
                {
                    addStatus("data check set false, data check cancel");
                    StatusSet(TestStatus.Pass);
                  }

                saveTestRecord(testResult);
               

                setStart(true);
            }


            setProgress(200, false);

            swTimeUse.Stop();
            TimeSpan ts2 = swTimeUse.Elapsed;
            addStatus("used time is:" + ts2.TotalMilliseconds + " ms");
            swTimeUse.Reset();


            if (accSock != null)
            {
                if (accSock.Connected)
                {
                    string Msg = Util.setTestJson(textSN.Text, cmbTestNo.Text, "0");
                    addStatus("start send TCP/IP....");
                    sendMsg(Msg);
                    addStatus("TCP/IP send finish");
                }
            }


            if (clearSN)
            {
                clearSNtext();
                // this.textSN.Text = "";
            }

            setSNFocus();
            // this.textSN.Focus();
        }

        #endregion
        /// <summary>
        /// Display testResult
        /// </summary>
        /// <param name="checkResult"></param>
        /// <returns></returns>
        private string setDisPlayResult(bool checkResult)
        {
            string testResult = null;
            if (checkResult)
            {
                StatusSet(TestStatus.Pass);
                testResult = "PASS";
                addStatus("data check PASS");
            }
            else
            {
                StatusSet(TestStatus.Fail);
                testResult = "Fail";
                addStatus("data check Fail");
            }

            return testResult;
        }

        /// <summary>
        /// set calibrate result
        /// </summary>
        private void setDisplayCaliresult()
        {
            if (calibrated)
            {
                StatusSet(TestStatus.Pass);
                setStart(true);
                setCali(false);
                addStatus("calibrate PASS,now you can start test");
            }
            else
            {
                StatusSet(TestStatus.Fail);
                setStart(false);
                setCali(true);
               
                addStatus("calibrate Fail,please try again");
            }
        }

        /// <summary>
        /// save S32p save record
        /// </summary>
        /// <param name="result"></param>
        /// <returns></returns>
        private bool saveTestRecord(string result){
             testRecord tRecord = new testRecord();
            tRecord.PN = this.textPN.Text.Trim();
            tRecord.MO = this.txtMO.Text.Trim();
            tRecord.testNo = testNo;
            tRecord.sn = this.textSN.Text.Trim();
            if (this.chkAutoSN.Checked)
            {
                tRecord.snType = SNType.ITAutoGet;
            }
            else {
                tRecord.snType = SNType.ManualInput;
            }
            
            tRecord.SDD21 = itemTestResult.PASS;
            if (result=="PASS")
            {
                tRecord.dataCheck = itemTestResult.PASS;
                tRecord.result= itemTestResult.PASS;
            }
            else if (result == "Fail")
            {
                tRecord.dataCheck = itemTestResult.Fail;
                tRecord.result = itemTestResult.Fail;
            }
            else {
                tRecord.dataCheck = itemTestResult.None;
                tRecord.result = itemTestResult.None;
            }
           
           // tRecord.result = itemTestResult.None;
            tRecord.snpFilePath = saveS32pPath;
            tRecord.testUser = "Figo";
            tRecord.testTime = DateTime.Now;

            if (Util.saveTestRecord(tRecord))
            {
                addStatus("insert test record success");
                return true;
            }
            else {
                addStatus("insert test record fail");
                return false;
            }
        }

        private void textPN_TextChanged(object sender, EventArgs e)
        {
            PN_change = true;
            autoSNStatusSet();
           
        }

      

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void rTextStatus_TextChanged(object sender, EventArgs e)
        {
            rTextStatus.SelectionStart = rTextStatus.Text.Length;
            rTextStatus.ScrollToCaret();
        }

       

       

        private bool setTrigger() {
            bool result = false;
            const string setSingle = "SENS:SWE:MODE SINGle";
            const string queryStatue="SENSe:SWEep:MODE?";
            rTextStatus.AppendText(Util.formatMsg("start set single Mode") + "\n");
            scpiParser.Execute(setSingle);

            for (int i = 0; i < 50; i++) {
                Thread.Sleep(500);
                string status = scpiParser.Execute(queryStatue);
                
                if (status.Trim().ToUpper() == "HOLD") {
                    rTextStatus.AppendText(Util.formatMsg("set single Mode succesed,now Hold") + "\n");
                    result = true;
                    return result;
                }

            }
            rTextStatus.AppendText(Util.formatMsg("wait Hold Mode fail") + "\n");
            return result;

        }

        private Dictionary<string, testParams> getTestParas()
        {
            Dictionary<string, testParams> dTestParams = new Dictionary<string, testParams>();
            const string queryString="CALC:PAR:CAT?";
            string sRet=scpiParser.Execute(queryString);
           
           //string sRet = "\"CH1_SDD21_1,S32_1,CH1_S22_2,S22,CH1_SDD21_3,Sdd21,CH1_SDD22_4,Sdd22\"";
           sRet = Util.testChannelTrim(sRet);
            string[] temp = sRet.Split(',');
            int length = temp.Length;
            if ((length == 0) || (length % 2 == 1)) {
                throw new Exception("get test params fail");
            }

            for (int i = 0; i < length/2; i++) {
                testParams newParams=new testParams();
                newParams.testName = temp[2 * i + 1];
                newParams.trace = i;
                newParams.channelName = temp[2 * i];
                dTestParams.Add(newParams.testName, newParams);
            }
            return dTestParams;

          
        }

        private bool PNChange(string PN) {
            if (PN.IndexOfAny(System.IO.Path.GetInvalidFileNameChars()) >= 0||PN=="")
            {
                MessageBoxEx.Show("invalid PN!");
                setStart(false);
              
                return false;
            }
            else
            {
                testPN = PN;
                testMO = txtMO.Text;
                Resolution = cmbResolution.Text.ToString();
                pnSaveFolderPath = s32pSaveFolder +"\\"+ PN;
                if (!Directory.Exists(pnSaveFolderPath)) {
                    Directory.CreateDirectory(pnSaveFolderPath);//创建该文件夹
                }
                return true;
            }
        }

        private void textPN_Leave(object sender, EventArgs e)
        {
           
        }

        private void textPN_Validated(object sender, EventArgs e)
        {
            if (PN_change) {
                PNChange(textPN.Text.Trim());
                spec = Util.getPNSpec(textPN.Text.Trim(), ref tdds, ref PNDescription, ref freSpec, ref TDDSpec,chkDBOffline.Checked);
                if (spec != null)
                {
                    DBRecord_ini();
                    addStatus("get PN spec from DB success!");
                    //saveFreData();
                }
                else {
                    setStart(false);
                    btn_Calibrate.Enabled = false;
                    MessageBoxEx.Show("get PN spec from DB fail!");
                    addStatus("get PN spec from DB fail!");
                    return;
                }
                calibrated = getCalibratedStatus(textPN.Text.Trim());
                if (calibrated)
                {
                    addStatus("PN:" + textPN.Text.Trim() + " calibrated");
                    setStart(true);
                    btn_Calibrate.Enabled = false;
                }
                else {
                    addStatus("PN:" + textPN.Text.Trim() + " not calibrated");
                    btn_Calibrate.Enabled = true;
                }
                PN_change = false;
            }
            
           
        }

        private void cmbTestNo_ini() { 
           
            for(int i=0;i<maxTestNum;i++){
                cmbTestNo.Items.Add((i + 1).ToString());
            }
            cmbTestNo.SelectedIndex = 0;
            
        }

        #region TCP/IP
        
        private void btnTCPStart_Click(object sender, EventArgs e)
        {
            try
            {
                IPHostEntry myHost = new IPHostEntry();
                myHost = Dns.GetHostByName("");
                string str = myHost.AddressList[0].ToString();
                myIP = IPAddress.Parse(str);
            }
            catch
            {
                MessageBoxEx.Show("您輸入的IP地址格式不正確，請重新輸入!");
            }
            try
            {
                threadServer = new Thread(new ThreadStart(accpServer));
                threadServer.IsBackground = true;
                threadServer.Start();

                threadCheck = new Thread(new ThreadStart(dicConnectCheck));
                threadCheck.IsBackground = true;
                threadCheck.Start();
            }
            catch (Exception ee)
            {
                this.rTextTCPLog.AppendText(ee.Message);
                
            }
        }

        private void dicConnectCheck()
        {
           // Control.CheckForIllegalCrossThreadCalls = false;//取消線程保護
            do
            {
                if (accSock != null)
                {

                    try
                    {
                        Byte[] Rec = new Byte[64];
                        byte[] sendByte = new byte[64];
                        string send = "mmmmm" + "\r\n";
                        NetworkStream netStream = new NetworkStream(accSock);
                        sendByte = System.Text.Encoding.ASCII.GetBytes(send.ToCharArray());
                        netStream.Write(sendByte, 0, sendByte.Length);
                    }
                    catch (Exception e)
                    {
                        addLog("DisConnect to Client");

                       
                        
                        btnTCPStop.PerformClick();
                        btnTCPStart.PerformClick();
                        accSock = null;
                        return;
                    }

                    Thread.Sleep(1000);
                }
            }
            while (check);
        }


        private void accpServer()
        {
            //Control.CheckForIllegalCrossThreadCalls = false;//取消線程保護
            MyServer = new IPEndPoint(myIP, Int32.Parse(this.textPort.Text));
            sock = new System.Net.Sockets.Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            sock.Bind(MyServer);
            sock.Listen(50);
            addLog("Port: " + this.textPort.Text + " , Start Listen......");
           
            accSock = sock.Accept();
            if (accSock.Connected)
            {
                sock.Close();
                addLog("Connect to Client");
               
                while (check)
                {
                    try
                    {
                        Byte[] Rec = new Byte[64];
                        NetworkStream netStream = new NetworkStream(accSock);
                        netStream.Read(Rec, 0, Rec.Length);
                        string RecMessage =
                            System.Text.Encoding.ASCII.GetString(Rec);
                        addLog(RecMessage);
                      
                    }
                    catch {
                        return;
                    }
                 
                }
            }
            else {
                addLog("Disconnect to Client");
              
            }
        }

        private void btnTCPSend_Click(object sender, EventArgs e)
        {
            string[] temp = this.textSend.Text.Trim().Split(',');
            string jsonStr = Util.setTestJson(temp[0], temp[1], temp[2]);
            sendMsg(jsonStr);
            this.textSend.Text = "";
           
        }

        private void sendMsg(string msg) {
            try
            {
                byte[] sendByte = new byte[64];
                string send = msg + "\r\n";
                NetworkStream netStream = new NetworkStream(accSock);
                sendByte = System.Text.Encoding.ASCII.GetBytes(send.ToCharArray());
                netStream.Write(sendByte, 0, sendByte.Length);
                rTextStatus.AppendText(Util.formatMsg("TCP/IP send success") + "\n");
                //this.textSend.Text = "";
            }
            catch
            {
                rTextStatus.AppendText(Util.formatMsg("TCP/IP send fail") + "\n");
                //MessageBox.Show("連接尚未建立!無法連接!");
            }

        }

        private void btnTCPStop_Click(object sender, EventArgs e)
        {
            try
            {
                sock.Close();
                //threadCheck.Abort();
                threadServer.Abort();
                threadCheck.Abort();
                //sock.Close();
                addLog("监听停止");
              
            }
            catch
            {
                addLog("监听尚未开始，关闭无效");
               
            }
        }

        #endregion

        #region FormScale

       //设置窗口控件随窗口大小改变而改变
        public void AutoScale(Form frm)
        {
            frm.Tag = frm.Width.ToString() + "," + frm.Height.ToString();
            frm.SizeChanged += new EventHandler(frm_SizeChanged);
        }
        public void frm_SizeChanged(object sender, EventArgs e)
        {
            //最小化缩放时处理会变形，且没有意义。
            if (((Form)sender).WindowState == FormWindowState.Minimized) {
                return;
            }
            string[] tmp = ((Form)sender).Tag.ToString().Split(',');
            float width = (float)((Form)sender).Width / (float)Convert.ToInt32(tmp[0]);
            float height = (float)((Form)sender).Height / (float)Convert.ToInt32(tmp[1]);
            ((Form)sender).Tag = ((Form)sender).Width.ToString() + "," + ((Form)sender).Height;
            string str = ((Form)sender).Tag.ToString();
            // int font_size = Int32.Parse(str.Substring(0, str.IndexOf(','))) / 100;
            //也可使字体随之改变
            float tempWidth = 0F;
            float tempHeight = 0F;
            foreach (Control control in ((Form)sender).Controls)
            {
                if (control is DataGridView)
                    continue;
                if (control is TextBox)
                {
                    tempHeight = height;
                    tempWidth = width;
                }
                if (control is Button)
                {
                    if (this.WindowState == FormWindowState.Maximized)
                        tempHeight -= 0.4F;
                    else
                        tempHeight += 0.2F;
                    control.Scale(new SizeF(tempWidth, tempHeight));
                }
                else
                {
                    control.Scale(new SizeF(width, height));
                }
            }
        }
        
        #endregion
        private void chkAutoSN_CheckedChanged(object sender, EventArgs e)
        {
            if (chkAutoSN.Checked)
            {
                autoSN_ini();
            }
            else {
                autoSNStatusSet();
            }
            
        }

        private void autoSN_ini() { 
           
            MOPNCheckResult ret=  Util.MOPNCheck(testMO, testPN);
            if (ret.result)
            {
                textSN.Enabled = false;
                textSN.BackColor = Color.Gray;
                textSN.ForeColor = Color.White;
                addStatus("MO,PN matched");
                MONumber = ret.MONumber;
              
            }
            else {
                MONumber = -1;
                autoSNStatusSet();
                MessageBoxEx.Show(ret.msg);
            }
            
        }

        private void skinStyle_ini() {
            foreach (eStyle suit in Enum.GetValues(typeof(eStyle)))
            {
                cmbSkin.Items.Add(suit.ToString());
            }

        }

        private void cmbSkin_SelectedIndexChanged(object sender, EventArgs e)
        {
            styleManager1.ManagerStyle = (eStyle)cmbSkin.SelectedIndex;
        }



        delegate void setProgressCallback(int value,bool step);
        private void setProgress(int value, bool step)
        {
            if (progressBarX1.InvokeRequired)
            {
                setProgressCallback d = new setProgressCallback(setProgress);
                this.Invoke(d, new object[] { value,step });
            }
            else {
                if (step)
                {
                    progressBarX1.Value = progressBarX1.Value+value;
                }
                else {
                    progressBarX1.Value = value;
                }
                
            }
        }

        delegate void setSNFocusCallback();
        private void setSNFocus() {
            if (this.textSN.InvokeRequired)
            {
                setSNFocusCallback d = new setSNFocusCallback(setSNFocus);
                this.Invoke(d);
            }
            else {
                this.textSN.Focus();
            }
        }

        delegate void clearSNtextCallback();
        private void clearSNtext() {
            if (this.textSN.InvokeRequired)
            {
                clearSNtextCallback d = new clearSNtextCallback(clearSNtext);
                this.Invoke(d);

            }
            else {
                this.textSN.Text = "";
            }
           
        }

        delegate void setStartCallback(bool status);
        private void setStart(bool status) {
            if (btnStart.InvokeRequired)
            {
                setStartCallback d = new setStartCallback(setStart);
                this.Invoke(d, new object[] { status });
            }
            else {
                btnStart.Enabled = status;
            }
        }

        delegate void setCaliCallback(bool status);
        private void setCali(bool status)
        {
            if (btn_Calibrate.InvokeRequired)
            {
                setCaliCallback d = new setCaliCallback(setCali);
                this.Invoke(d, new object[] { status });
            }
            else
            {
                btn_Calibrate.Enabled = status;
            }
        }

        delegate void setCableStatusCallback(string msg);
        private void setCableStatus(string msg) {
            if (labelCableStatus.InvokeRequired)
            {
                setCableStatusCallback d = new setCableStatusCallback(setCableStatus);
                this.Invoke(d, new object[] { msg });
            }
            else {
                labelCableStatus.Text = msg;
            }
        }


        delegate void setResultCallback(string text, Color color);
        private void setResult(string text,Color color) {
            if (labelResult.InvokeRequired)
            {
                setResultCallback d = new setResultCallback(setResult);
                this.Invoke(d, new object[] { text,color });
            }
            else {
                labelResult.Text = text;
                labelResult.BackColor = color;
              
            }
        }
        delegate void SetchartClearCallback(Chart chart);
        delegate void SetDrawLineCallBack(Chart chart,plotData temp,string serialName,LineType lineType);
        private void chartClear(Chart chart) {
            if (chart.InvokeRequired)
            {
                SetchartClearCallback d = new SetchartClearCallback(chartClear);
                this.Invoke(d, new object[] { chart});
            }
            else {
                chart.Series.Clear();
            }
        }

        private void cmbAdapter_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cmbAdapter.SelectedIndex)
            {
                case 0:
                    I2CDevice = new VCI_GYI2C(GYIDeviceType, DeviceInd, writeBufferSize);
                    break;
                case 1:

                    if (cmbPorts.Text == "") {
                        MessageBoxEx.Show("please choose a com port first");
                        cmbAdapter.SelectedIndex = 0;
                        return;
                    }
                    comm.PortName = cmbPorts.Text;
                    comm.BaudRate = 115200;
                    comm.DataBits = 8;
                    comm.Parity = Parity.None;
                    comm.StopBits = StopBits.One;
                    comm.ReadBufferSize = 1024;
                    comm.WriteBufferSize = 1024;
                    I2CDevice = new LuxshareI2C(comm, writeBufferSize, LuxshareIICTimeOut);
                    break;
                case 2:
                    I2CDevice = new CP2112(CP2102DeviceNum, CP2102TImeOut, writeBufferSize);
                    break;

            }



        }

        private void getSerialPorts()
        {
            //检查是否含有串口  


            string[] str = SerialPort.GetPortNames();
            if (str == null)
            {
                MessageBoxEx.Show("本机没有串口！", "Error");
                return;
            }
            if (str.Length == 0)
            {
                MessageBoxEx.Show("本机没有串口！", "Error");
                return;
            }
            Array.Sort(str);
            //添加串口项目  
            foreach (string s in str)
            {//获取有多少个COM口  
                cmbPorts.Items.Add(s);
            }

            //串口设置默认选择项  
            cmbPorts.SelectedIndex = 0;         //设置cbSerial的默认选项  
        }

        private void cmbPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cmbAdapter.SelectedIndex)
            {
                case 0:
                    I2CDevice = new VCI_GYI2C(GYIDeviceType, DeviceInd, writeBufferSize);
                    break;
                case 1:
                    comm.PortName = cmbPorts.Text;
                    comm.BaudRate = 115200;
                    comm.DataBits = 8;
                    comm.Parity = Parity.None;
                    comm.StopBits = StopBits.One;
                    comm.ReadBufferSize = 1024;
                    comm.WriteBufferSize = 1024;
                    I2CDevice = new LuxshareI2C(comm, writeBufferSize, LuxshareIICTimeOut);
                    break;
                case 2:
                    I2CDevice = new CP2112(CP2102DeviceNum, CP2102TImeOut, writeBufferSize);
                    break;

            }
        }

        private void chkSerialPortChoose_CheckedChanged(object sender, EventArgs e)
        {
            if (chkSerialPortChoose.Checked)
            {
                DeviceInd = cmbPorts.SelectedIndex;
            }
            else
            {
                DeviceInd = 0;
            }
        }

     

       

        private Dictionary<string, bool> snpCheck(string s32pFilepath, SNPPort snpPort, Dictionary<string, plotData> spec)
        {
            addStatus("start clear charts");
  
            foreach (KeyValuePair<string, Chart> chart in chartDic)
            {
                chartClear(chart.Value);
            }

            Dictionary<string,string[]>pairNameDictionary=new Dictionary<string, string[]>();

           // string[] testItems = checkTDD ? new[] { "SINGLE", "SDD21", "SDD11", "TDD11", "TDD22" } : new[] { "SINGLE", "SDD21", "SDD11" };
            string[] testItems = chartDic.Keys.ToArray();

            bool action = false;
            string msg = "";
            Dictionary<string, plotData[]> data = Util.getAnalyzedData(
                testItems, s32pFilepath, snpPort, spec, tdds, ref action, ref msg, ref pairNameDictionary);
          
            if (!action)
            {
                addStatus(msg);
                MessageBoxEx.Show(msg);
                return null;
            }
            Dictionary<string, bool> result = Util.judge(spec, data);
            if (blSaveTxt)
            {
                string testSN = null;
                textSN.Invoke(new MethodInvoker(() =>
                {
                    testSN = textSN.Text;
                }));
                Util.dataSave(txtSaveFolder + "\\" + testPN + "\\SN-" + testSN+"\\txt\\"+testNo,data);
            }
            
            addStatus("finished judge data");
           
            foreach (string testItem in testItems)
            {
               Chart tempChart = chartDic[testItem];
                plotData[] temp = data[testItem];
                for (int i = 0; i < temp.Length; i++)
                {
                   // addStatus("chart " + testItem + i+" start");
                    if (pairNameDictionary.ContainsKey(testItem))
                    {
                       
                        LineType lineType = testItem.StartsWith("T") ? LineType.Time : LineType.Fre;
                        DrawLine(tempChart, temp[i], pairNameDictionary[testItem][i], lineType);
                       
                    }
                    else
                    {
                        addStatus(testItem+" not exsit");
                    }
 
                }

                drawSpec(testItem, spec, tempChart);
            }

         

            foreach (var testResult in result)
            {
                addStatus(testResult.Key + ":" + Util.boolToString(testResult.Value));
                // rTextStatus.AppendText(Util.formatMsg(testResult.Key + ":" + Util.boolToString(testResult.Value)) + "\n");
            }
            data = null;
            return result;

        }


        private void drawSpec(string itemName, Dictionary<string, plotData> spec, Chart chart)
        {
            if (spec.ContainsKey(itemName + "_UPPER")) {
                DrawLine(chart, spec[itemName + "_UPPER"], itemName + "_UPPER",LineType.Spec);
            }
            if (spec.ContainsKey(itemName + "_LOWER"))
            {
                DrawLine(chart, spec[itemName + "_LOWER"], itemName + "_LOWER",LineType.Spec);
            }
        }

     

        private delegate void SetaddStatusCallback(string msg);
        private void addStatus(string msg) {
            if (rTextStatus.InvokeRequired)
            {
                SetaddStatusCallback d = new SetaddStatusCallback(addStatus);
                this.Invoke(d, new object[] { msg});
            }
            else {
                rTextStatus.AppendText(Util.formatMsg(msg) + "\n");
            }
          
        }
        private delegate void SetAddlogCallback(string msg);

        private void addLog(string msg)
        {
            if (rTextTCPLog.InvokeRequired)
            {
                SetAddlogCallback d = new SetAddlogCallback(addLog);
                this.Invoke(d, new object[] { msg });
            }
            else {
                this.rTextTCPLog.AppendText(msg + "\n");
            }
           
        }

        private void txtMO_TextChanged(object sender, EventArgs e)
        {
            autoSNStatusSet();
        }

        private void autoSNStatusSet() {
            chkAutoSN.Checked = false;
            textSN.Enabled = true;
            textSN.BackColor = this.BackColor;
            textSN.ForeColor = this.ForeColor;
            txtMoSum.BackColor = this.BackColor;
        }
       private bool getSN(string MO,string PN){
           SNData snData=Util.getITSN(MO, PN);
          
           if (!Util.saveSNRecord(snData))
           {
               addStatus("save sn data to DB fail!");
               return false;
           }
           else
           {
               setDetailSN(snData);
               addStatus("save sn data to DB success!");
           }
           string sn = snData.label;
        textSN.Text = sn;
        addStatus("get sn: " + sn + " from WCF success!");
        
           int moSum=Util.getSavedNumber(MO, PN, int.Parse(cmbTestNo.Text));
           txtMoSum.Text = moSum.ToString();
           if (moSum > (MOTolerance + 100) * MONumber / 100)
           {
               
               txtMoSum.BackColor = Color.LightCyan;
               MessageBoxEx.Show("please note that:used sn mumber is more than MO num");
           }
        return true;
       }

       private void setDetailSN(SNData snData)
       {
           dbRecord[29] = snData.FSN;
           dbRecord[30] = "";
           dbRecord[31] = "";
           dbRecord[32] = snData.label;
           dbRecord[33] = snData.customerData;
           dbRecord[34] = snData.sn;
           dbRecord[35] = snData.snDec;
       }

       private bool writeSN(string sn) {

           if (openDevice())
           {
               string writeSN =  string.Format("{0:00}", sn.Length)+sn;// 
               byte[] writeData = Util.getBytes(writeSN);

               operationResult or = I2CDevice.writeDevice(SlaveAddr, 0, 0, writeData.Length, writeData);
               if (or.result)
               {
                   addStatus("write SN: " + sn + " suceess!");
                   if (closeDevice())
                   {
                       return true;
                   }
                   else
                   {
                       return false;
                   }

               }
               else
               {
                   addStatus("write SN: " + sn + " fail! reson: " + or.msg);
                   closeDevice();
                   return false;
               }
           }
           else {
               addStatus("open device fail,please check or replace the adapter");
               return false;
           }

         
       }


       private bool openDevice() {
           if (I2CDevice.openDevice())
           {
               addStatus("successful to open device!");
               return true;
           }
           else
           {
               addStatus("fail to open device!");
               return false;
           }
       }

       private bool closeDevice() {
           try
           {
               if (I2CDevice.closeDevice())
               {
                   addStatus("successful to close device!");
                   return true;
               }
               else
               {
                   addStatus("fail to close device!");
                   return false;
               }
           }
           catch {
               return false;
           }
          
       }

       private bool s32pAnalyze(string s32pFilepath, SNPPort snpPort, Dictionary<string, plotData> spec, string PN, ref Dictionary<string, bool> results)
       {
          
           bool ret=true;
           string msg = "";
           addStatus("analyze test data start");

           bool fileExist=false;
           int timeOutCreate=10000;
           int timeOutUse=10000;
           string fileMsg="";
           int fileCheckTime=0;

           fileExist=Util.FileIsUsing(s32pFilepath, timeOutCreate, timeOutUse, ref fileMsg, ref fileCheckTime);

           if (!fileExist) {
               addStatus(fileMsg);
               addStatus("analyze fail,please try again");
               return false;
           }

           addStatus("wait s32p File used time is:"+fileCheckTime.ToString()+"ms");

           results = snpCheck(s32pFilepath, snpPort, spec);
           if (results == null) {
               addStatus("analyze fail,please try again");
               return false;
           }
           addStatus("analyze test data finsihed");
         
           
           //Dictionary<string, bool> results=diffCheck(s32pFilepath, snpPort, spec);
           foreach (var item in results) {
               ret = ret && item.Value;
               msg = msg+item.Key + ":" + Util.boolToString(item.Value) + "\r\n";
           }

           if (ret)
           {
               string savePath = "cali\\" + DateTime.Now.ToString("yyyyMMdd");
               if (!Directory.Exists(@savePath))
               {
                   Directory.CreateDirectory(@savePath);
               }
               FileStream fs = File.Create(savePath + "\\" + PN + ".txt");
               StreamWriter swSaveWriter = new StreamWriter(fs);
               swSaveWriter.Write(msg);
               swSaveWriter.Close();
               fs.Close();
               addStatus("Calibration PASS");
           }
           else {
               addStatus("Calibration Fail");
           }
         
           return ret;
       }
       private bool getCalibratedStatus(string PN)
       {
           string caliFile = "cali\\" + DateTime.Now.ToString("yyyyMMdd")+"\\"+PN+".txt";
           return File.Exists(caliFile);
       }

       private void rbtPort0_CheckedChanged(object sender, EventArgs e)
       {
           if (rbtPort0.Checked) {
               snpPort = SNPPort.X1324;
           }
       }

       private void rbtPort1_CheckedChanged(object sender, EventArgs e)
       {
           if (rbtPort1.Checked) {
               snpPort = SNPPort.X1234;
           }
           
       }

       private void btn_Calibrate_Click(object sender, EventArgs e)
       {
           setCali(false);
           setStart(true);
           btnStart.PerformClick();
       }

       private void timer1_Tick(object sender, EventArgs e)
       {
           if (labelResult.BackColor == Color.Blue)
           {
               labelResult.BackColor = Color.BlueViolet;
               setProgress(1, true);
               return;
           }
           if (labelResult.BackColor == Color.BlueViolet)
           {
               labelResult.BackColor = Color.Blue;
               setProgress(1, true);
               return;
           }
       }

       private bool readConfig()
       {
           config readConfig = Util.getConfig(configFilePath);
           if (readConfig == null)
           {
               return false;
           }
           else
           {
               txtSaveFolder = readConfig.TxtSaveFolder;
               textTxtSaveFolderPath.Text = txtSaveFolder;
               s32pSaveFolder = readConfig.FileSavePath;
               textS32PSaveFolderPath.Text = s32pSaveFolder;

               clearSN = readConfig.ClearSN;
               chkSNClear.Checked = clearSN;

               maxTestNum = readConfig.MaxTestNum;

               txtCalFile.Text = readConfig.CalPath;
               chkCalFileEnable.Checked = readConfig.CalFileEnable;
               if (chkCalFileEnable.Checked&&(!File.Exists(readConfig.CalPath)))
               {
                   MessageBoxEx.Show("cal file is not exsit,can't set enable checked");
                   chkCalFileEnable.Checked = false;
               }
               textPort.Text = readConfig.Port;
               cmbAdapter.SelectedIndex = readConfig.AdapterIndex;
               cmbPorts.SelectedIndex = readConfig.ComIndex;
               setPortMap(readConfig.ConnectMap);

               chkWriteSN.Checked = readConfig.WriteSN;

               chkEEPROM.Checked = readConfig.WriteEEPROM;
               cmbSkin.SelectedIndex=readConfig.Skin;
               txtVisaAddress.Text = readConfig.VisaAddress;
               visaAddress = txtVisaAddress.Text;
               cmbResolution.SelectedIndex = readConfig.ResolutionIndex;
               MOTolerance=readConfig.MoTolerance>0?MOTolerance:0;
               chkDBOffline.Checked = readConfig.DbOffline;
              
               return true;
           }
       }

       private bool saveConfig() {
           config saveConfig = new config();
           saveConfig.FileSavePath = textS32PSaveFolderPath.Text;
           saveConfig.ClearSN = chkSNClear.Checked;
           if (maxTestNum == 0) {
               maxTestNum = 4;
           }
           saveConfig.MaxTestNum = maxTestNum;
           saveConfig.CalPath = txtCalFile.Text;
           saveConfig.CalFileEnable = chkCalFileEnable.Enabled;
           saveConfig.Port = textPort.Text;
           saveConfig.AdapterIndex = cmbAdapter.SelectedIndex;
           saveConfig.ComIndex = cmbPorts.SelectedIndex;
           saveConfig.ConnectMap = getPortMap();
           saveConfig.WriteSN = chkWriteSN.Checked;
           saveConfig.WriteEEPROM = chkEEPROM.Checked;
           saveConfig.Skin = cmbSkin.SelectedIndex;
           saveConfig.VisaAddress = txtVisaAddress.Text;
           saveConfig.ResolutionIndex = cmbResolution.SelectedIndex;
           saveConfig.MoTolerance = MOTolerance;
           saveConfig.TxtSaveFolder = textTxtSaveFolderPath.Text;
           saveConfig.DbOffline = chkDBOffline.Checked;
           return Util.saveConfig(saveConfig, configFilePath);
       }

       #region PNA portmap function
       private void setPortMap(int index) {
           if (index == 0) {
               rbtPort0.Checked = true; 
               rbtPort1.Checked = false;
           } 
           if (index == 1)
           {
               rbtPort0.Checked = false; 
               rbtPort1.Checked = true;
           }
       }

       private int getPortMap() {
           if (rbtPort0.Checked)
           {
               return 0;
           }
           else {
               return 1;
           }
       }
       #endregion

       private void txtCalFile_TextChanged(object sender, EventArgs e)
       {
           CalCheck();
       }

       private void chkCalFileEnable_CheckedChanged(object sender, EventArgs e)
       {
           if (chkCalFileEnable.Checked) {
               CalCheck();
           }
       }
       private void CalCheck() {
           if (!File.Exists(txtCalFile.Text.Trim())) {
               chkCalFileEnable.Checked = false;
           }
       }

       private void btnSaveFolder_Click(object sender, EventArgs e)
       {
           if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
           {
               textS32PSaveFolderPath.Text = folderBrowserDialog1.SelectedPath;
               addLog("select folder path success!");
              
           }
           else
           {
               addLog("cancel folder path select!");
           }
       }

       private void btnCalBrowse_Click(object sender, EventArgs e)
       {
           OpenFileDialog dialog = new OpenFileDialog();
           dialog.Multiselect = true;//该值确定是否可以选择多个文件
           dialog.Title = "请选择文件夹";
           dialog.Filter = "所有文件(*.*)|*.*";
           if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
           {
               txtCalFile.Text = dialog.FileName;
           }
   
       }

       private void btnSave_Click(object sender, EventArgs e)
       {
           if (saveConfig())
           {
               addLog("save config success!");
           }
           else {
               addLog("save config fail!");
           }
       }

     

        private enum LineType
        {
            Fre,
            Time,
            Spec
        }

       private void DrawLine(Chart chart, plotData temp, string seriName,LineType lineType)
       {
           if (chart.InvokeRequired)
           {
              
               SetDrawLineCallBack d = DrawLine;
               chart.Invoke(d, new object[] { chart, temp, seriName,lineType });
           }
           else
           {
               //绑定数据
               int index = chart.Series.Count;
              
               
               chart.Series.Add(seriName);
              
               Series currentSeries = chart.Series[index];
               //chart.Titles[index].Alignment = System.Drawing.ContentAlignment.TopRight;
               currentSeries.XValueType = ChartValueType.Single;  //设置X轴上的值类型
               //currentSeries.Label = "#VAL";                //设置显示X Y的值    
               //currentSeries.LabelForeColor = Color.Black;
               currentSeries.ToolTip = "#VALX:#VAL";     //鼠标移动到对应点显示数值
               currentSeries.ChartType = SeriesChartType.FastLine;    //图类型(折线)
               //currentSeries.ChartType = SeriesChartType.Line;    //图类型(折线)
               currentSeries.IsValueShownAsLabel = false;
               currentSeries.LegendText = seriName;
               currentSeries.IsVisibleInLegend = true;
               //chart.Legends[seriName].Enabled = true;
               //chart.Legends[seriName].MaximumAutoSize = 15;
               //chart.Series[0].IsValueShownAsLabel = true;

              // currentSeries.LabelForeColor = Color.Black;
               
              // currentSeries.CustomProperties = "DrawingStyle = Cylinder";
               currentSeries.Points.DataBindXY(temp.xData, temp.yData);
               
               //if (index == 0)
               //{
               //    CalloutAnnotation annotation = new CalloutAnnotation();
               //    annotation.AnchorDataPoint = currentSeries.Points[600];
               //    annotation.Text = "Just Won't Work";
               //    annotation.ForeColor = Color.Black;
               //    annotation.Font = new Font("Arial", 12); ;
                   
               //    annotation.LineWidth = 2;
               //    annotation.Width = 50;
               //    annotation.Height = 30;
                  
               //    annotation.Visible = true;
               //    chart.Annotations.Add(annotation);
                  

               //}
               

               switch (lineType)
               {
                   case LineType.Fre:
                       for (int i = 1; i < 10; i++)
                       {
                           CustomLabel label = new CustomLabel();
                           label.Text = (i * 5).ToString() + "Ghz";
                           label.ToPosition = i * 10000000000;
                           chart.ChartAreas[0].AxisX.CustomLabels.Add(label);
                           label.GridTicks = GridTickTypes.Gridline;
                       }
                       break;
                   case LineType.Time:
                       for (int i = 1; i < 10; i++)
                       {
                           CustomLabel label = new CustomLabel();
                           label.Text = (i * 1).ToString() + "ns";
                           label.ToPosition = (float)i * 2;
                           chart.ChartAreas[0].AxisX.CustomLabels.Add(label);
                           label.GridTicks = GridTickTypes.Gridline;
                       }
                     break;
                    
               }

               //chart.Visible = true;
           }


       }

     


       private bool diskFreeSpaceCheck() {
           long freespace = Util.GetHardDiskSpace(volume);
           if (freespace < 1000)
           {
               return false;
           }
           else {
               return true;
           }

       }


        private ReportInformation GetReportInformation()
        {
           
            string SN = null;
            textSN.Invoke(new MethodInvoker(() =>
            {
                SN = textSN.Text.Trim();
            }));
            ReportInformation ret;
            ret.application = "Yaowen Wang";
            ret.partDescription = PNDescription;
            ret.partNo = testPN;
            ret.fixtureSerialNo = "23";
            ret.reportNo = "HF-" + SN;
            ret.sampleNo = SN;
            ret.preparedBy = "Quanying Niu";
            ret.approvedBy = "Wave Zhang";
            ret.temprature = "23";
            ret.rHumidity = "60";
            ret.date = DateTime.UtcNow.ToString("yyyy-MM-dd");
            ret.tdrModel = "1.TDR:Keysight PLTS IFFT";
            ret.vnaModel = "2.PNA:Keysight 26.5GHz 32Port M9375A";
            return ret;
        }

      

        private void cmbTestNo_SelectedIndexChanged(object sender, EventArgs e)
        {
            testNo = this.cmbTestNo.SelectedIndex + 1;
            saveS32pPath = pnSaveFolderPath + "\\" + Util.slashRepalce(textSN.Text) + "_" + cmbTestNo.Text + ".s32p";
        }

        private void txtVisaAddress_TextChanged(object sender, EventArgs e)
        {
            visaAddress = txtVisaAddress.Text;
        }


        /// <summary>
        /// 测试项目初始化
        /// </summary>
        private void testItemCheckBoxIni()
        {
            int startX = 5;
            int startY = 5;
            int width = 130;
            int height = 20;
            int rowMargin = 2;
            int colMargin = 5;
           
            string[] testItems = {"SINGLE","SDD11", "SDD21","TDD11","TDD22","SCD22","SCD21-SDD21","SCC11","NEXT","FEXT","MDNEXT","MDFEXT"};

            int startNo = 0;
            int rows = 5;

            Dictionary<string, CheckBoxX> checkBoxDic=new Dictionary<string, CheckBoxX>();
            foreach (var VARIABLE in testItems)
            {
                int coordinateX = startNo / 5;
                int coordinateY = startNo % 5;
                CheckBoxX checkBox = new CheckBoxX();

                checkBox.Visible = true;
                checkBox.Size = new Size(width, height);
                checkBox.Text = VARIABLE;
                checkBox.Name = "chk_" + VARIABLE;
                checkBox.Font = new Font("Consolas", 11F, 
                    System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                checkBox.Location = new Point(startX + coordinateX * (width + rowMargin), startY + coordinateY*(height+colMargin));
                checkBox.CheckedChanged+=checkBox_CheckedChanged;
               // panelEx1.Controls.Add(checkBox);
                panelExTestItems.Controls.Add(checkBox);
                startNo = startNo + 1;
                checkBoxDic.Add(checkBox.Name, checkBox);
            }

            checkBoxDic["chk_SINGLE"].Checked = true;
            checkBoxDic["chk_SDD21"].Checked = true;
            checkBoxDic["chk_SDD11"].Checked = true;
        }

        private void checkBox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBoxX checkBox = (CheckBoxX) sender;
            TestItemAction testItem = checkBox.Checked ? TestItemAction.Add : TestItemAction.Remove;
            TestItemChange(checkBox.Text, testItem);

        }

        private enum TestItemAction
        {
            Add,
            Remove
        }

        private void TestItemChange(string testItem, TestItemAction actionItem)
        {
            switch (actionItem)
            {
                case TestItemAction.Remove:
                    if (chartDic.ContainsKey(testItem))
                    {
                        chartDic.Remove(testItem);
                        TabItem timRemove = this.tabControlChart.Tabs[testItem];
                        //TabItem timRemove = ((Func<TabItem>)(() =>
                        //{
                        //    TabItem ret = null;
                        //    foreach (TabItem tabItem in this.tabControlChart.Tabs)
                        //    {
                        //        if (tabItem.Name == testItem)
                        //        {
                        //            ret = tabItem;
                        //            break;
                        //        }
                        //    }
                        //    return ret;
                        //    }))();

                        this.tabControlChart.Tabs.Remove(timRemove);
                        
                    }
                    break;
                case TestItemAction.Add:
                    TabItem tim = this.tabControlChart.CreateTab(testItem);
                    tim.Name = testItem;
                    Chart chart = new Chart();
                    chart.Name = testItem;
                    chart.Width = 999;
                    chart.Height = 336;
                    chart.Location=new Point(4,0);
                    Legend legend = new Legend("legend");
                    legend.Title = "Legend";
                    legend.Font = new Font("Consolas", 11F,
                        System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                    chart.Legends.Add(legend);
                  
                   
                    ChartArea chartArea = new ChartArea("ChartArea1");
                    chartArea.CursorX.IsUserEnabled = true;
                    chartArea.CursorX.IsUserSelectionEnabled = true;
                    chartArea.CursorX.LineDashStyle = ChartDashStyle.DashDotDot;
                    chartArea.CursorY.IsUserEnabled = true;
                    chartArea.CursorY.IsUserSelectionEnabled = true;
                    chartArea.CursorY.LineDashStyle = ChartDashStyle.DashDotDot;
                    chart.ChartAreas.Add(chartArea);
                    tim.AttachedControl.Controls.Add(chart);
                    chart.ChartAreas[0].AxisY.IsStartedFromZero = false;
                    chart.Series.Clear();
                    chartDic.Add(testItem,chart);
                    break;

            }


        }

        /// <summary>
        /// 条码打印功能占位函数
        /// </summary>
        /// <returns></returns>
        private bool LabelPrint()
        {
            dbRecord[1] = "";
            return true;
        }

        private bool DBRecord_ini()
        {
            Array.Clear(dbRecord,0,dbRecord.Length);
            
            dbRecord[0] = testPN;
            dbRecord[1] = "nolabel";
            dbRecord[3] = "";
            dbRecord[5] = "Yaowen Wang";
            dbRecord[6] = "Quanying Niu";
            dbRecord[7] = "Wave Zhang";
            dbRecord[10] = Environment.MachineName;
            dbRecord[36] = testMO;
            return true;
        }

        private bool DBRecord_get(string sn,int testCount,bool testResult,int testTime,string EEPRomResult,
            bool nextTF,bool fextTF)
        {
            dbRecord[2] = sn;
            dbRecord[4] = testResult?"PASS":"FAIL";
            dbRecord[8] = DateTime.Now.ToString("HH:mm:ss yyyy/MM/dd");
            dbRecord[9] = testTime + "S";

            dbRecord[11] = EEPRomResult;
            dbRecord[12] = "0";
            dbRecord[13] = "0";
            dbRecord[14] = nextTF?"1":"0";
            dbRecord[15] = fextTF ? "1" : "0";
            dbRecord[16] = "1";
            dbRecord[17] = "1";
            dbRecord[18] = "0";

            dbRecord[19] = "P#" + sn + "_" + testCount + "#Thru.zip";
            dbRecord[20] = "NULL";
            dbRecord[21] = "NULL";
            dbRecord[22] = nextTF ? "P#" + sn + "_" + testCount + "#NextTXT.zip":"NULL";
            dbRecord[23] = "NULL";
            dbRecord[24] = fextTF ? "P#" + sn + "_" + testCount + "#FextTXT.zip" : "NULL";
            dbRecord[25] = "P#" + sn + "_" + testCount + "#TXT.zip";
            dbRecord[26] = "NULL";
            dbRecord[27] = EEPRomResult != "EEPROM:None" ? "P#" + sn + "_" + testCount + "#FextTXT.zip" : "NULL";
            dbRecord[28] = "P#" + sn + "_" + testCount + "#Summary.zip";

            dbRecord[37] = "";
            dbRecord[38] = "NULL";
            dbRecord[39] = "S32pSave";
            dbRecord[40] = "S32P";

            return true;
        }

        private void buttonX1_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                textTxtSaveFolderPath.Text = folderBrowserDialog1.SelectedPath;
                addLog("select folder path success!");

            }
            else
            {
                addLog("cancel folder path select!");
            }
        }

        private void chkUpload_CheckedChanged(object sender, EventArgs e)
        {

            if (chkUpload.Checked)
            {
                chkSaveTxt.Checked = true;
                blUpload = true;
                blSaveTxt = true;
                chkSaveTxt.Enabled = false;
            }
            else
            {
                blUpload = false;
                chkSaveTxt.Enabled = true;
            }
        }

        private void chkSaveTxt_CheckedChanged(object sender, EventArgs e)
        {
            blSaveTxt = chkSaveTxt.Checked;
        }
    
    }

    class PNASaver
    {
        public delegate void saveFileHandler(string S32pFilePath);
        public delegate void pnaConnectCheckeHandler(bool connected);
        public event saveFileHandler saveFinished;
        public event saveFileHandler saveBefore;
        public event pnaConnectCheckeHandler pnaConnectChecked;
        public void saveS32p(string filePath,string visaAddress,string Resolution)
        {
            if (saveBefore != null)
            {
                saveBefore(filePath);
            }

#if !DEBUG
   
            PLTS plts = new PLTS();
            if (!plts.Connected)
            {
                plts.Connect(visaAddress);
            }

            if (pnaConnectChecked != null)
            {
                pnaConnectChecked(plts.Connected);
            }
            
            plts.CloseAllFiles();
            plts.MeasureS32pFile();

            int fileNumber = plts.GetActiveFileIndex();

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
            plts.ExportFile(fileNumber, 32, filePath, Resolution);
            plts.Disconnect();
           
#endif
            if (saveFinished != null)
            {
                saveFinished(filePath);
            }

        }
     
    }
   
}
