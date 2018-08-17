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
using Ivi.Visa.Interop;


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

        Stopwatch sw = new Stopwatch();
        

        #region SI
        Dictionary<string, plotData> spec = new Dictionary<string, plotData>();
        TDD[]tdds=new TDD[2];
        public bool calibrated = false;
        public SNPPort snpPort = SNPPort.X1234;
        #endregion

        public static bool clearSN;
        public static string s32pSaveFolder;
        public static int maxTestNum;

        public bool PN_change = false;

        AgilentPNA835x.Application PNA835;
        //public PLTS plts = new PLTS();
        public string visaAddress = "";
        //private bool pltsConnected = false;
        IScpiStringParser2 scpiParser;
        public string channelSelStr = "";
        public string channelSel = "";
        public string saveFolderPath="";
        public string saveBaseFolderPath = "";
        public string volume = "";
        public string saveS32pPath = "";
        public int testNo = -1;
        public const string configFilePath = "config.xml";
        public int MONumber = -1;//工单数量
        public int MOTolerance=20;//工单数量误差百分比
        public Dictionary<string, testParams> testparamList;

        public Dictionary<string, Chart> chartDic = new Dictionary<string, Chart>();
        
        public frmMain()
        {
            InitializeComponent();
        }

        enum TestStatus
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
                    sw.Stop();
                    setResult("Fail",Color.Red);
                    btnStart.Enabled = true;
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
            if (!diskFreeSpaceCheck()) {
                MessageBoxEx.Show("磁盘剩余空间不足1G，请清理后再测试！");
                return;
            }

            
            addStatus("start test");
            sw.Start();
            setCableStatus("");
            setProgress(0, false);
            btnStart.Enabled = false;
          
            setProgress(3, false);
            if (chkAutoSN.Checked)
            {
                if (!getSN(txtMO.Text.Trim(), textPN.Text.Trim())) {
                    return;
                }
                setProgress(5, false);
            }
            else
            {
                if (textSN.Text.Trim().Equals(""))
                {
                    labelResult.Text = "Fail";
                    labelResult.BackColor = Color.Red;
                    btnStart.Enabled = true;
                    MessageBoxEx.Show("SN不能为空");
                    return;
                }
            }
            saveS32pPath = @saveFolderPath + "\\" + Util.slashRepalce(textSN.Text) + "_" + cmbTestNo.Text + ".s32p";
            if (chkWriteSN.Checked) {
                if (!writeSN(textSN.Text.Trim())) {
                    MessageBoxEx.Show("写入SN失败，请确认烧录盒子或线缆连接是否OK后再重试");
                    labelResult.Text = "Fail";
                    labelResult.BackColor = Color.Red;
                    btnStart.Enabled = true;
                    return;
                }
                setProgress(15, false);
            }

            StatusSet(TestStatus.Working);
           
            //labelResult.Text = "Working";
            //labelResult.BackColor = Color.Blue;

         

            setProgress(35, false);

           
            setProgress(45, false);

            timer1.Enabled = true;
            addStatus("start get S32P");
           
            Thread threadGetS32p = new Thread(new ThreadStart(getS32p));
            threadGetS32p.Start();

           
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
         
            #if DEBUG
        
                        button1.Visible = true;
            
            #endif
            charts_ini();
            setCableStatus("");
            btn_Calibrate.Enabled = false;
            skinStyle_ini();
            getSerialPorts();
            cmbAdapter.SelectedIndex = 0;
            if (!readConfig()) {
                MessageBoxEx.Show("read config file error!");
            }
            cmbTestNo_ini();

           // 
            
            
            AutoScale(this);
           
            
            btnStart.Enabled = false;
            rbtPort1.Checked = true;
            labelX2.ForeColor = Color.DarkOliveGreen;//标题颜色
            labelResult.Text = "";

            

            //FileSaveConfig fsc = Util.getFileSaveConfig(configFilePath);
            //clearSN = Util.getSNClearConfig(configFilePath);
            //textSaveFolderPath.Text = s32pSaveFolder;
            if (Directory.Exists(@s32pSaveFolder))
            {

            }
            else
            {
                MessageBoxEx.Show("path:" + s32pSaveFolder + " not exist");
                MessageBoxEx.Show("This application will auto create this path");
                Directory.CreateDirectory(s32pSaveFolder);//创建该文件夹
            }
           
            saveBaseFolderPath = s32pSaveFolder;

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
            //MessageBox.Show(testparamList[firstChannel].channelName);
            channelSelStr = "CALC:PAR:SEL '" + testparamList[firstChannel].channelName + "'";
            channelSel = (Sdd21.trace + 1).ToString();
#endif
            volume = saveBaseFolderPath.Substring(0, saveBaseFolderPath.IndexOf(':'));
            //btnStart.Enabled = true;
        }


        private void getS32P_Event()
        {

            PNASaver a = new PNASaver();
           // string dataFile = @saveFolderPath + "\\" + textSN.Text + "_" + cmbTestNo.Text + ".s32p";
            a.saveBefore += On_SaveBefore;
            a.saveFinished += On_SaveFinished;
            a.saveS32p("", saveS32pPath, cmbResolution.SelectedItem.ToString());
        }
        void On_SaveBefore(object sender, S32PSaveBeforeEventArgs e)
        {
            sendWriting();
        }
        private void On_SaveFinished(object sender, S32PSaveFinishedEventArgs e)
        {
            setCableStatus("请拔出线缆");
            addStatus("finished get S32P");
            setStart(true);
            timer1.Enabled = false;
            dataCali();
            sendTCPAnalyzeCMD();
            if (clearSN)
            {
                clearSNtext();
               // this.textSN.Text = "";
            }
            setSNFocus();
            sw.Stop();

            TimeSpan ts2 = sw.Elapsed;
            addStatus("used time is:" + ts2.TotalMilliseconds + " ms");
            sw.Reset();
        }

        private void dataCali()
        {
            Dictionary<string, bool> results = new Dictionary<string, bool>();
            if (!calibrated)
            {
                addStatus("start calibrate");
                calibrated = calibrate(saveS32pPath, snpPort, spec, textPN.Text.Trim(), ref results);
                if (calibrated)
                {
                    StatusSet(TestStatus.Pass);
                    //setResult(true);
                    setStart(true);
                    setCali(false);
                    addStatus("calibrate PASS,now you can start test");
                }
                else
                {
                    StatusSet(TestStatus.Fail);
                    //setResult(false);
                    setStart(false);
                    setCali(true);
                    // btnStart.Enabled = false;
                    addStatus("calibrate Fail,please try again");
                }
            }
            else
            {
                string testResult = "";
                if (chkDataCheck.Checked)
                {
                    addStatus("data check set true,start data check");
                    bool checkResult = calibrate(saveS32pPath, snpPort, spec, textPN.Text.Trim(), ref  results);
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

                }
                else
                {
                    addStatus("data check set false, data check cancel");
                    StatusSet(TestStatus.Pass);

                }

                addStatus(saveTestRecord(testResult) ? "insert test record success" : "insert test record fail");
                setStart(true);
            }
        }
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


        private void getS32p()
        {
            string noText = null;
            cmbTestNo.Invoke(new MethodInvoker(() => { noText = cmbTestNo.Text; }));
            //string dataFile = @saveFolderPath + "\\" + Util.slashRepalce(textSN.Text) + "_" + noText + ".s32p";
#if !DEBUG
            if (accSock != null && chkEEPROM.Checked)
            {
                if (accSock.Connected)
                {
                    string Msg = Util.setTestJson(textSN.Text, cmbTestNo.Text, "1");
                    addStatus("start EEPROM Writing....");
                    sendMsg(Msg);
                 }
            }

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
            plts = null;
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
                calibrated = calibrate(saveS32pPath, snpPort, spec, textPN.Text.Trim(), ref results);
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
                    // btnStart.Enabled = false;
                    addStatus("calibrate Fail,please try again");
                }
            }
            else
            {
                string testResult = "";
                if (chkDataCheck.Checked)
                {
                    addStatus("data check set true,start data check");
                    //System.GC.Collect();
                    //addStatus("clean memory success");
                    bool checkResult = calibrate(saveS32pPath, snpPort, spec, textPN.Text.Trim(), ref results);
                    if (checkResult)
                    {
                        StatusSet(TestStatus.Pass);
                       // setResult(true);
                        testResult = "PASS";
                        addStatus("data check PASS");
                    }
                    else
                    {
                        StatusSet(TestStatus.Fail);
                        //setResult(false);
                        testResult = "Fail";
                        addStatus("data check Fail");
                    }
                }
                else
                {
                    addStatus("data check set false, data check cancel");
                    StatusSet(TestStatus.Pass);
                    //setResult(true);
                }

                if (saveTestRecord(testResult))
                {
                    addStatus("insert test record success");
                }
                else
                {
                    addStatus("insert test record fail");
                }

                setStart(true);
            }


            setProgress(200, false);

            sw.Stop();
            TimeSpan ts2 = sw.Elapsed;
            addStatus("used time is:" + ts2.TotalMilliseconds + " ms");
            sw.Reset();


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
                return true;
            }
            else {
                return false;
            }
        }

        private void textPN_TextChanged(object sender, EventArgs e)
        {
            PN_change = true;
            autoSNStatusSet();
            //if (!chkManualCal.Checked) {
            //    string CALFilePath = "";
            //}
           
           
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
                btnStart.Enabled = false;
                return false;
            }
            else {
                saveFolderPath = saveBaseFolderPath + PN;
                if (!Directory.Exists(@saveFolderPath)) {
                    Directory.CreateDirectory(@saveFolderPath);//创建该文件夹
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
                spec = Util.getPNSpec(textPN.Text.Trim(),ref tdds);
                if (spec != null)
                {
                    addStatus("get PN spec from DB success!");
                }
                else {
                    btnStart.Enabled = false;
                    btn_Calibrate.Enabled = false;
                    MessageBoxEx.Show("get PN spec from DB fail!");
                    addStatus("get PN spec from DB fail!");
                    return;
                }
                calibrated = getCalibratedStatus(textPN.Text.Trim());
                if (calibrated)
                {
                    addStatus("PN:" + textPN.Text.Trim() + " calibrated");
                    btnStart.Enabled = true;
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

                    //if (!accSock.Connected) {
                    //    MessageBox.Show("DisConnect to Client");
                    //    this.textState.AppendText("DisConnect to Client");
                    //    return;
                    //}
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
            //try
            //{
            //    byte[] sendByte = new byte[64];
            //    string send = this.textSend.Text + "\r\n";
            //    NetworkStream netStream = new NetworkStream(accSock);
            //    sendByte = System.Text.Encoding.ASCII.GetBytes(send.ToCharArray());
            //    netStream.Write(sendByte, 0, sendByte.Length);
            //    this.textSend.Text = "";
            //}
            //catch
            //{
            //    MessageBox.Show("連接尚未建立!無法連接!");
            //}
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
            string MO=txtMO.Text.Trim();
            string PN=textPN.Text.Trim();
            MOPNCheckResult ret=  Util.MOPNCheck(MO, PN);
            if (ret.result)
            {
                textSN.Enabled = false;
                textSN.BackColor = Color.Gray;
                textSN.ForeColor = Color.White;
                addStatus("MO,PN matched");
                MONumber = ret.MONumber;
                //spec = Util.getPNSpec(PN);
                //if (spec == null)
                //{
                //    addStatus("query PN spec from database fail!");
                //    autoSNStatusSet();
                //}
                //else
                //{
                //    addStatus("query PN spec from database success!");
                //}
               
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


        private void insertTestRecordAdd() {
            testRecord tRecord = new testRecord();
            tRecord.PN = "AAA";
            tRecord.MO = "BBB";
            tRecord.testNo = 1;
            tRecord.sn = "9999";
            tRecord.snType = SNType.ITAutoGet;
            tRecord.SDD21 = itemTestResult.PASS;
            tRecord.dataCheck = itemTestResult.Fail;
            tRecord.result = itemTestResult.None;
            tRecord.snpFilePath = "c:\\AA.s32p";
            tRecord.testUser = "Figo";
            tRecord.testTime = DateTime.Now;

            if (Util.saveTestRecord(tRecord)) {
                MessageBox.Show("OK");
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
           SNData a= Util.getITSN("E511D-180700157", "L99HE001-SD-R");
           //MessageBox.Show(a.label);

            test100();
            //setProgress(3,true);
            //progressBarX1.Value = progressBarX1.Value + 10;
            //DeleteItselfByCMD();
            //Thread a = new Thread(new ThreadStart(test100));
            //a.Start();
        }


       
        private void test100() {
            Dictionary<string, plotData> spec = Util.getPNSpec("Figo33",ref tdds);
            for (int i = 0; i < 1; i++)
            {
                addStatus("----------------------------------");
                test(spec);
                //System.GC.Collect();
                Process CurrentProcess = Process.GetCurrentProcess();
                //var p1 = new PerformanceCounter("Process", "Working Set - Private", "S32PSave.exe");
                //string bb = (p1.NextValue() / 1024 / 1024).ToString("0.0") + "MB";
                string aa = (CurrentProcess.WorkingSet64 / 1024 / 1024).ToString() + "M (" + (CurrentProcess.WorkingSet64 / 1024).ToString() + "KB)";
                
                addStatus("testtime is:" + i.ToString() + "                use memory is:" + aa);
                addStatus("----------------------------------");
               
           
             
          
            }
        }

        private void test(Dictionary<string, plotData> spec)
        {
            string filePath = @"B:\myData.mdf";
            chkDataCheck.Checked = true;
            StatusSet(TestStatus.Pass);
            this.textSN.Text = "";
            timer1.Enabled = false;
            setSNFocus();
            setStart(true);
           // plotData temp = Util.read(filePath);
            //chartSDD21.Series.Clear();
           
           // chartClear(chartSDD21Full);
            //chartClear(chartSDD11Full);
            //chartSDD21Full.Series.Clear();
            //chartSDD11Full.Series.Clear();

            string s32pFilepath = @"D:\copyFiles\85MX1D08D_1.s32p";

            snpCheck(s32pFilepath, SNPPort.X1234, spec,true);
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

        private void charts_ini() {
            chartDic = new Dictionary<string, Chart>()
            {
                {"SINGLE",chartSingle},
                {"SDD21",chartSDD21Full},
                {"SDD11",chartSDD11Full},
                {"TDD11",chartTDD11Full},
                {"TDD22",chartTDD22Full}
            };

            foreach (KeyValuePair<string,Chart>chart in chartDic)
            {
                chart.Value.ChartAreas[0].AxisY.IsStartedFromZero = false;
            }
            
            //drawDataIni(chartSDD21Full);
            //drawDataIni(chartSDD11Full);
            //drawDataIniTDD(chartTDD11Full);
        }

        private Dictionary<string, bool> diffCheck(string s32pFilepath, SNPPort snpPort, Dictionary<string, plotData> spec)
        {

            chartSDD21Full.Series.Clear();
            chartSDD11Full.Series.Clear();

            string[] SDD21 = { "SDD21", "SDD43", "SDD65", "SDD87", "SDD10_9", "SDD12_11", "SDD14_13", "SDD16_15" };
            string[] SDD11 = { "SDD11", "SDD33", "SDD55", "SDD77", "SDD99", "SDD11_11", "SDD13_13", "SDD15_15" };
            Dictionary<string, string[]> item = new Dictionary<string, string[]>();
            item.Add("SDD21", SDD21);
            item.Add("SDD11", SDD11);

            bool action = false;
            string msg = "";
            Dictionary<string, plotData[]> data = Util.getDiff(item, s32pFilepath, snpPort,spec,ref action,ref msg);
            if (!action) {
                addStatus(msg);
                MessageBoxEx.Show(msg);
                return null;
            }
            //if (data == null) {
               
            //}
            Dictionary<string, bool> result = Util.judge(spec, data);
            for (int i = 0; i < data["SDD21"].Length; i++)
            {
                DrawLine(chartSDD21Full, data["SDD21"][i], SDD21[i],LineType.Fre);
            }
            drawSpec("SDD21", spec, chartSDD21Full);
            for (int i = 0; i < data["SDD11"].Length; i++)
            {
                DrawLine(chartSDD11Full, data["SDD11"][i], SDD11[i],LineType.Fre);
            }
            drawSpec("SDD11", spec, chartSDD11Full);

            foreach (var testResult in result)
            {
                addStatus(testResult.Key + ":" + Util.boolToString(testResult.Value));
                // rTextStatus.AppendText(Util.formatMsg(testResult.Key + ":" + Util.boolToString(testResult.Value)) + "\n");
            }
            data = null;
            return result;

        }

       

        private Dictionary<string, bool> snpCheck(string s32pFilepath, SNPPort snpPort, Dictionary<string, plotData> spec,bool checkTDD)
        {
            addStatus("start clear charts");
  
            foreach (KeyValuePair<string, Chart> chart in chartDic)
            {
                chartClear(chart.Value);
            }

            Dictionary<string,string[]>pairNameDictionary=new Dictionary<string, string[]>();

            string[] testItems = checkTDD ? new[] { "SINGLE", "SDD21", "SDD11", "TDD11", "TDD22" } : new[] { "SINGLE", "SDD21", "SDD11" };

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

        private delegate void MsgExCallback(string msg);

        private void MsgEx(string msg)
        {
            if (this.InvokeRequired)
            {
                MsgExCallback d=new MsgExCallback(MsgEx);
                this.Invoke(d, new object[] {msg});
            }
            else
            {
                MessageBoxEx.Show(msg);
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
           else {
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

       private bool calibrate(string s32pFilepath, SNPPort snpPort, Dictionary<string, plotData> spec, string PN, ref Dictionary<string, bool> results)
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

           results = snpCheck(s32pFilepath, snpPort, spec, chkTDDCheck.Checked);
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
               StreamWriter sw = new StreamWriter(fs);
               sw.Write(msg);
               sw.Close();
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
           btnStart.Enabled = true;
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
               s32pSaveFolder = readConfig.FileSavePath;
               textSaveFolderPath.Text = s32pSaveFolder;

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
              
               return true;
           }
       }

       private bool saveConfig() {
           config saveConfig = new config();
           saveConfig.FileSavePath = textSaveFolderPath.Text;
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
               textSaveFolderPath.Text = folderBrowserDialog1.SelectedPath;
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

       private  void drawDataIni(Chart chart)
       {
           //标题
           //chart.Titles.Add("a柱状图数据分析");
           //chart.Titles.Add("b柱状图数据分析");
           //chart.Titles.Add("SDD21");
           //chart.Titles[0].ForeColor = Color.White;
           //chart.Titles[0].Font = new Font("微软雅黑", 12f, FontStyle.Regular);
           //chart.Titles[0].Alignment = ContentAlignment.TopCenter;

           chart.Visible = false;


           //chart.Titles[1].ForeColor = Color.White;
           //chart.Titles[1].Font = new Font("微软雅黑", 8f, FontStyle.Regular);
           //chart.Titles[1].Alignment = ContentAlignment.TopRight;

           //控件背景
           chart.BackColor = Color.Transparent;
           //图表区背景
           chart.ChartAreas[0].BackColor = Color.Transparent;
           chart.ChartAreas[0].BorderColor = Color.Transparent;
           //X轴标签间距
           // chart.ChartAreas[0].AxisX.Interval=5000000000;
           //chart.ChartAreas[0].AxisX.LabelStyle.IsStaggered = true;
           chart.ChartAreas[0].AxisX.LabelStyle.Angle = 0;
           chart.ChartAreas[0].AxisX.TitleFont = new Font("微软雅黑", 14f, FontStyle.Regular);
           chart.ChartAreas[0].AxisX.TitleForeColor = Color.Black;


           //X坐标轴颜色
           chart.ChartAreas[0].AxisX.LineColor = ColorTranslator.FromHtml("#38587a"); ;
           chart.ChartAreas[0].AxisX.LabelStyle.ForeColor = Color.Black;
           chart.ChartAreas[0].AxisX.LabelStyle.Font = new Font("微软雅黑", 10f, FontStyle.Regular);
           //X坐标轴标题
           //chart.ChartAreas[0].AxisX.Title = "数量(宗)";
           //chart.ChartAreas[0].AxisX.TitleFont = new Font("微软雅黑", 10f, FontStyle.Regular);
           //chart.ChartAreas[0].AxisX.TitleForeColor = Color.White;
           //chart.ChartAreas[0].AxisX.TextOrientation = TextOrientation.Horizontal;
           //chart.ChartAreas[0].AxisX.ToolTip = "数量(宗)";
           //X轴网络线条
           chart.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
           chart.ChartAreas[0].AxisX.MajorGrid.LineColor = ColorTranslator.FromHtml("#2c4c6d");

           //Y坐标轴颜色
           chart.ChartAreas[0].AxisY.LineColor = ColorTranslator.FromHtml("#38587a");
           chart.ChartAreas[0].AxisY.LabelStyle.ForeColor = Color.Black;
           chart.ChartAreas[0].AxisY.LabelStyle.Font = new Font("微软雅黑", 10f, FontStyle.Regular);
           //Y坐标轴标题
           chart.ChartAreas[0].AxisY.Title = "loss";
           chart.ChartAreas[0].AxisY.TitleFont = new Font("微软雅黑", 10f, FontStyle.Regular);
           chart.ChartAreas[0].AxisY.TitleForeColor = Color.Black;
           chart.ChartAreas[0].AxisY.TextOrientation = TextOrientation.Rotated270;
           chart.ChartAreas[0].AxisY.ToolTip = "loss";
           //Y轴网格线条
           chart.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
           chart.ChartAreas[0].AxisY.MajorGrid.LineColor = ColorTranslator.FromHtml("#2c4c6d");

           chart.ChartAreas[0].AxisY2.LineColor = Color.Transparent;
           chart.ChartAreas[0].BackGradientStyle = GradientStyle.TopBottom;


           //Legend legend = new Legend("legend");
           //legend.Title = "legendTitle";


           //chart.Legends.Add(legend);
           //chart.Legends[0].Position.Auto = false;



       }


       private void drawDataIniTDD(Chart chart)
       {
           //标题
           //chart.Titles.Add("a柱状图数据分析");
           //chart.Titles.Add("b柱状图数据分析");
           //chart.Titles.Add("SDD21");
           //chart.Titles[0].ForeColor = Color.White;
           //chart.Titles[0].Font = new Font("微软雅黑", 12f, FontStyle.Regular);
           //chart.Titles[0].Alignment = ContentAlignment.TopCenter;

           chart.Visible = false;


           //chart.Titles[1].ForeColor = Color.White;
           //chart.Titles[1].Font = new Font("微软雅黑", 8f, FontStyle.Regular);
           //chart.Titles[1].Alignment = ContentAlignment.TopRight;

           //控件背景
           chart.BackColor = Color.Transparent;
           //图表区背景
           chart.ChartAreas[0].BackColor = Color.Transparent;
           chart.ChartAreas[0].BorderColor = Color.Transparent;
           //X轴标签间距
           // chart.ChartAreas[0].AxisX.Interval=5000000000;
           //chart.ChartAreas[0].AxisX.LabelStyle.IsStaggered = true;
           chart.ChartAreas[0].AxisX.LabelStyle.Angle = 0;
           chart.ChartAreas[0].AxisX.TitleFont = new Font("微软雅黑", 14f, FontStyle.Regular);
           chart.ChartAreas[0].AxisX.TitleForeColor = Color.Black;


           //X坐标轴颜色
           chart.ChartAreas[0].AxisX.LineColor = ColorTranslator.FromHtml("#38587a"); ;
           chart.ChartAreas[0].AxisX.LabelStyle.ForeColor = Color.Black;
           chart.ChartAreas[0].AxisX.LabelStyle.Font = new Font("微软雅黑", 10f, FontStyle.Regular);
           //X坐标轴标题
           //chart.ChartAreas[0].AxisX.Title = "数量(宗)";
           //chart.ChartAreas[0].AxisX.TitleFont = new Font("微软雅黑", 10f, FontStyle.Regular);
           //chart.ChartAreas[0].AxisX.TitleForeColor = Color.White;
           //chart.ChartAreas[0].AxisX.TextOrientation = TextOrientation.Horizontal;
           //chart.ChartAreas[0].AxisX.ToolTip = "数量(宗)";
           //X轴网络线条
           chart.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
           chart.ChartAreas[0].AxisX.MajorGrid.LineColor = ColorTranslator.FromHtml("#2c4c6d");

           //Y坐标轴颜色
           chart.ChartAreas[0].AxisY.LineColor = ColorTranslator.FromHtml("#38587a");
           chart.ChartAreas[0].AxisY.LabelStyle.ForeColor = Color.Black;
           chart.ChartAreas[0].AxisY.LabelStyle.Font = new Font("微软雅黑", 10f, FontStyle.Regular);
           //Y坐标轴标题
           chart.ChartAreas[0].AxisY.Title = "resistance";
           chart.ChartAreas[0].AxisY.TitleFont = new Font("微软雅黑", 10f, FontStyle.Regular);
           chart.ChartAreas[0].AxisY.TitleForeColor = Color.Black;
           chart.ChartAreas[0].AxisY.TextOrientation = TextOrientation.Rotated270;
           chart.ChartAreas[0].AxisY.ToolTip = "resistance";
           //Y轴网格线条
           chart.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
           chart.ChartAreas[0].AxisY.MajorGrid.LineColor = ColorTranslator.FromHtml("#2c4c6d");
           chart.ChartAreas[0].AxisY.IsStartedFromZero = false;
           //chart.ChartAreas[0].AxisY.Minimum = 80;

           chart.ChartAreas[0].AxisY2.LineColor = Color.Transparent;
           chart.ChartAreas[0].BackGradientStyle = GradientStyle.TopBottom;


           //Legend legend = new Legend("legend");
           //legend.Title = "legendTitle";


           //chart.Legends.Add(legend);
           //chart.Legends[0].Position.Auto = false;



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
               SetDrawLineCallBack d = new SetDrawLineCallBack(DrawLine);
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
               currentSeries.Label = "#VAL";                //设置显示X Y的值    
               currentSeries.LabelForeColor = Color.Black;
               currentSeries.ToolTip = "#VALX:#VAL";     //鼠标移动到对应点显示数值
               currentSeries.ChartType = SeriesChartType.FastLine;    //图类型(折线)
               currentSeries.LegendText = seriName;
               //chart.Series[0].IsValueShownAsLabel = true;
               currentSeries.LabelForeColor = Color.Black;
               currentSeries.CustomProperties = "DrawingStyle = Cylinder";
               currentSeries.Points.DataBindXY(temp.xData, temp.yData);

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

               chart.Visible = true;
           }


       }

       private  void EmputyLine(Chart chart)
       {
           chart.Series[0].Points.Clear();
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

      

      

        private void cmbTestNo_SelectedIndexChanged(object sender, EventArgs e)
        {
            testNo = this.cmbTestNo.SelectedIndex + 1;
            saveS32pPath = @saveFolderPath + "\\" + Util.slashRepalce(textSN.Text) + "_" + cmbTestNo.Text + ".s32p";
        }

        private void txtVisaAddress_TextChanged(object sender, EventArgs e)
        {
            visaAddress = txtVisaAddress.Text;
        }

    
    }

    class PNASaver
    {
        public event EventHandler<S32PSaveFinishedEventArgs> saveFinished;
        public event EventHandler<S32PSaveBeforeEventArgs> saveBefore;
        public void saveS32p(string filePath,string visaAddress,string Resolution)
        {
            S32PSaveBeforeEventArgs argsStart = new S32PSaveBeforeEventArgs();
            OnThresholdStart(argsStart);
            //Thread.Sleep(8000);
            PLTS plts = new PLTS();
            if (!plts.Connected) {
                plts.Connect(visaAddress);
            }
            if (!plts.Connected) {
                MessageBoxEx.Show("connect PLTS fail");
                return;
            }
            plts.MeasureS32pFile();

            int fileNumber = plts.GetActiveFileIndex();
            //string dataFile = @saveFolderPath + "\\" + textSN.Text + "_" + cmbTestNo.Text + ".s32p";
            plts.ExportFile(fileNumber, 32, filePath, Resolution);
            plts.CloseAllFiles();
           // plts.measureTest();
            S32PSaveFinishedEventArgs argsFinsihed = new S32PSaveFinishedEventArgs();
            OnThresholdReached(argsFinsihed);

        }
        protected virtual void OnThresholdReached(S32PSaveFinishedEventArgs e)
        {
            EventHandler<S32PSaveFinishedEventArgs> handler = saveFinished;
            if (handler != null)
            {
                handler(this, e);//触发回调函数
            }
        }
        protected virtual void OnThresholdStart(S32PSaveBeforeEventArgs e)
        {
            EventHandler<S32PSaveBeforeEventArgs> handler = saveBefore;
            if (handler != null)
            {
                handler(this, e);//触发回调函数
            }
        }
    }
    public class S32PSaveFinishedEventArgs : EventArgs
    {

    }
    public class S32PSaveBeforeEventArgs : EventArgs
    {

    }
}
