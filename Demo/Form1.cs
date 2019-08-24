using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using P9375;

namespace Demo
{
    public partial class Form1 : Form
    {
        P9375A _p9375A=new P9375A();
        private SaveFileType _saveFileType = SaveFileType.Snp;
        

        enum SaveFileType
        {
            Snp,
            Txt
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _p9375A.OnMemoryDataGet += _p9375A_OnMemoryDataGet;
            _p9375A.BeforeGetfre+=_p9375A_BeforeGetfre;
            _p9375A.OnFreGet+=P9375AOnFreGet;
        }

        private void P9375AOnFreGet(double[] obj)
        {
            AddLog("get fre data finsihed");
        }

        private void _p9375A_BeforeGetfre()
        {
           AddLog("start get fre data");
        }

        private void chkConnect_CheckedChanged(object sender, EventArgs e)
        {
            if (chkConnect.Checked)
            {
                try
                {
                    _p9375A.Connect(txtVisa.Text);
                    chkConnect.Checked = true;
                    AddLog("connect to vna success");
                }
                catch (Exception exception)
                {
                    AddLog("connect to vna fail");
                    chkConnect.Checked = false;
                    ShowError(exception);

                }

            }
           
        }

        private void rbFileType_Clicked(object sender, EventArgs e)
        {
            if (rbTxt.Checked)
            {
                _saveFileType = SaveFileType.Txt;
            }

            if (rbSnp.Checked)
            {
                _saveFileType = SaveFileType.Snp;
            }
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog sfd=new SaveFileDialog())
            {
                string SnpType = _saveFileType.ToString().ToLower();
                sfd.Title = "Save Snp files";
                sfd.Filter = SnpType + " files (*." + SnpType + ")|*." + SnpType + "|All files(*.*)|*.*";
                sfd.RestoreDirectory = true;

                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    txtFilePath.Text = sfd.FileName;
                  
                }
            }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
           Thread saveThread=new Thread(DoSave);
           saveThread.Start();
        }

        private void DoSave()
        {
            AddLog("start save");
            try
            {
                switch (_saveFileType)
                {
                    case SaveFileType.Snp:
                        _p9375A.StoreS2P(txtFilePath.Text, 32);
                        break;
                    case SaveFileType.Txt:
                        _p9375A.StorePure(txtFilePath.Text, 32);
                        break;
                }
            }
            catch (Exception exception)
            {
                ShowError(exception);
            }


            AddLog("save finished");
        }

        private void _p9375A_OnMemoryDataGet(float[] data)
        {
            AddLog("get Memory data finsihed");
        }

       
        private void AddLog(string msg)
        {
            if (rtStatus.InvokeRequired)
            {
                Action<string> d = AddLog;
                this.Invoke(d, new object[] { msg });
            }
            else
            {
                this.rtStatus.AppendText(DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss")+"         "+msg + "\n");
            }

        }

        private void ShowError(Exception exception)
        {
            MessageBox.Show(String.Format("error:{0}" + Environment.NewLine
                                                      + "source:{1}" + Environment.NewLine + "trace:{2}",
                exception.Message, exception.Source, exception.StackTrace));
        }
    }
}
