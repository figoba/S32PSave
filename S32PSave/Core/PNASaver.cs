using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace S32PSave.Core
{
    class PNASaver
    {
        public delegate void saveFileHandler(string S32pFilePath);
        public delegate void pnaConnectCheckeHandler(bool connected);
        public event saveFileHandler OnsaveFinished;
        public event saveFileHandler OnsaveBefore;
        public event pnaConnectCheckeHandler OnpnaConnectChecked;
        public void saveS32p(string filePath, string visaAddress, string Resolution)
        {
            if (OnsaveBefore != null)
            {
                OnsaveBefore(filePath);
            }

#if !DEBUG
            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }



            try
            {
                P9375A p9375A=new P9375A();
                p9375A.Connect(visaAddress);
                if (OnpnaConnectChecked != null)
                {
                    OnpnaConnectChecked(p9375A.IsConnect());
                }
                p9375A.StoreS2P(filePath,32);

            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }


           
#endif
            if (OnsaveFinished != null)
            {
                OnsaveFinished(filePath);
            }

        }

    }
}
