using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ClassLibrary_Burn;
using RomMapConvert.Impl;

namespace S32PSave.Core
{
    

    public struct BurnAdapter
    {
        public enum Type
        {
            GYIC,
            CP2102,
            CP2112
        }

        public Type type;
        public string connectString;
    }
    class EEPROM
    {
        private string _connectStr;
        private BurnAdapter _burnAdapter;
        Class_Burn cb = new Class_Burn();
        RomConvert RC = new RomConvert();

        public EEPROM(BurnAdapter burnAdapter)
        {
            this._burnAdapter = burnAdapter;
            IniAdapter();
        }

        private void IniAdapter()
        {
            bool bIni;
            string msg = "";
            bIni = _burnAdapter.type == BurnAdapter.Type.CP2102 ? 
                cb.Init(ref msg, (int)_burnAdapter.type, int.Parse(_burnAdapter.connectString)) : 
                cb.Init(ref msg, (int)_burnAdapter.type);
            if (!bIni)
            {
                throw new Exception("initial adapter fail:"+msg);
            }   

        }

        //private bool Write()
        //{
        //    byte[] Pswd_Null = null;
        //    byte[][] Pswd_H3C = { new byte[] { 0x61, 0x30, 0x7A, 0x39 }, new byte[] { 0x61, 0x30, 0x7A, 0x39 } };
        //    string Msg = "";
        //    bool flag;
        //    byte[][] _temp = RC.GetRomMapCross("L99SF001-SD-H", "1904050897/Z00A2R1845S004155");
        //    flag = cb.OpenDevice(ref Msg);
        //    flag = cb.EEPROM_Write(Class_Burn.ProduceTpye.SFP, Class_Burn.CustomerTpye.H3C, false, Pswd_Null, Pswd_Null, _temp[0], 0, ref Msg);
        //}
       
    }
}
