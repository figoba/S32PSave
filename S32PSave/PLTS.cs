using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ivi.Visa.Interop;
using System.Threading;

namespace S32PSave
{
    public class PLTS
    {
        private FormattedIO488 ioDmm = new FormattedIO488();
        private bool _connected = false;

        public void Connect(string visaAddress)
        {
            ResourceManager grm = new ResourceManager();
            ioDmm.IO = (IMessage)grm.Open(visaAddress, AccessMode.NO_LOCK, 0, "");
            _connected = true;
        }

        public bool Connected
        {
            get
            {
                return _connected;
            }
        }

        public void Disconnect()
        {
            ioDmm.IO.Close();
            _connected = false;
            ioDmm = null;
        }

        public string ReadString()
        {
            return ioDmm.ReadString().TrimEnd('\n').Trim('\"');
        }

        private void OPC()
        {
            ioDmm.WriteString("*opc?");
            ReadString();
        }

        public void CloseAllFiles()
        {
            ioDmm.WriteString(":ACLS");
        }

       

        public void MeasureS32pFile()
        {
            int timeout = ioDmm.IO.Timeout;
            ioDmm.IO.Timeout = 30000;

            string cmd = ":MEASure:SETup:VIEW:NAME ' Frequency Domain (Single-Ended)'";
            //string cmd = ":MEASure:SETup:VIEW:NAME 'MiniSAS (32p)'";
            ioDmm.WriteString(cmd);

            cmd = ":MEASure:SETup:PORTs:COUNt 32";
            ioDmm.WriteString(cmd);

            cmd = ":MEASure:SINGle";
            ioDmm.WriteString(cmd);

            OPC();

            ioDmm.IO.Timeout = timeout;
        }

        public void ImportSnpFile(string snpFile)
        {
            string cmd = ":IMPort:DOMain FREQuency";
            ioDmm.WriteString(cmd);

            cmd = ":IMPort:TYPE TSOne";
            ioDmm.WriteString(cmd);

            cmd = ":IMPort:RANGe ALL";
            ioDmm.WriteString(cmd);

            cmd = string.Format(":IMPort '{0}'", snpFile);
            ioDmm.WriteString(cmd);
        }

        public int GetActiveFileIndex()
        {
            string cmd = "File:Active?";
            ioDmm.WriteString(cmd);

            string result = ReadString();
            return int.Parse(result);
        }

        public void SetWindowTypeAndCoefficient(int fileNumber, TimeDomainWindowTypes type, double coeff)
        {
            int timeout = ioDmm.IO.Timeout;
            ioDmm.IO.Timeout = 20000;

            string cmd = string.Format(":FILE{0}:TDOMain:WINDow:TYPE {1}", fileNumber, type.ToCmdString());
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:TDOMain:WINDow:COEF {1}", fileNumber, coeff);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:TDOMain:APPL", fileNumber);
            ioDmm.WriteString(cmd);

            OPC();

            ioDmm.IO.Timeout = timeout;
        }

        public void AddTDD11ImpedancePlot(int fileNumber, int viewNumber)
        {
            string cmd = string.Format(":FILE{0}:NView 'Time Domain (Differential)'", fileNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:NPLot 'TDD11'", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT1:FORMat SIN", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT1:SCAL:AUTO", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);
        }

        public void AddSDD21Plot(int fileNumber, int viewNumber)
        {
            string cmd = string.Format(":FILE{0}:NView 'Frequency Domain (Balanced)'", fileNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:NPLot 'SDD21'", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT1:SCAL:AUTO", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);
        }

        public void AddS21AndS43UnwrappedPhasePlots(int fileNumber, int viewNumber)
        {
            string cmd = string.Format(":FILE{0}:NView 'Frequency Domain (Single-Ended)'", fileNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:NPLot 'S21'", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT1:NTRace 'S43'", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT1:FORMat PUNWrapped", fileNumber, viewNumber);
            ioDmm.WriteString(cmd);
        }

        private double GetStatisticData(int fileNumber, int viewNumber, int plotNumber)
        {
            string cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:TRACe1:STAT:DATA?", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            string result = ReadString();
            return double.Parse(result);
        }

        public void GetTraceStatistics(int fileNumber, int viewNumber, int plotNumber, double rangeStart, double rangeStop, ref double peakToPeak, ref double stdDev, ref double mean, ref double min, ref double max)
        {
            int timeout = ioDmm.IO.Timeout;
            ioDmm.IO.Timeout = 20000;

            string cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STATistics:SPAN USER", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT:USER:STAR {3}", fileNumber, viewNumber, plotNumber, rangeStart);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT:USER:STOP {3}", fileNumber, viewNumber, plotNumber, rangeStop);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT ON", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT:TYPE PTP", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            peakToPeak = GetStatisticData(fileNumber, viewNumber, 1);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT:TYPE SDEV", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            stdDev = GetStatisticData(fileNumber, viewNumber, 1);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT:TYPE MEAN", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            mean = GetStatisticData(fileNumber, viewNumber, 1);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT:TYPE MIN", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            min = GetStatisticData(fileNumber, viewNumber, 1);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:STAT:TYPE MAX", fileNumber, viewNumber, plotNumber);
            ioDmm.WriteString(cmd);

            max = GetStatisticData(fileNumber, viewNumber, 1);

            ioDmm.IO.Timeout = timeout;
        }

        public double GetMarkerReadout(int fileNumber, int viewNumber, int plotNumber, int traceNumber, int markerNumber, double xPos, string unit)
        {
            string cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:MARK{3} ON", fileNumber, viewNumber, plotNumber, markerNumber);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:MARK{3}:X {4}{5}", fileNumber, viewNumber, plotNumber, markerNumber, xPos, unit);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:TRACe{3}:MARK{4}:Y?", fileNumber, viewNumber, plotNumber, traceNumber, markerNumber);
            ioDmm.WriteString(cmd);

            string result = ReadString();
            return double.Parse(result);
        }

        public void DoDifferentialThruAFR(string thruFileName, string fixture1, string fixture2)
        {
            int timeout = ioDmm.IO.Timeout;
            ioDmm.IO.Timeout = 100000;

            string cmd = ":AFR:INIT";
            ioDmm.WriteString(cmd);

            cmd = ":AFR:FIXTure:INPuts DIFFerential";
            ioDmm.WriteString(cmd);

            cmd = ":AFR:FIXTure:MEASurement 4";
            ioDmm.WriteString(cmd);

            cmd = ":AFR:FIXTure:CLENgth OFF";
            ioDmm.WriteString(cmd);

            cmd = ":AFR:FIXTure:BLIMited OFF";
            ioDmm.WriteString(cmd);

            cmd = ":AFR:STANdard:USE THRU,ON";
            ioDmm.WriteString(cmd);

            cmd = string.Format(":AFR:STANdard:LOAD THRU,'{0}'", thruFileName);
            ioDmm.WriteString(cmd);

            cmd = ":AFR:SAVE:PORTs PLTS";
            ioDmm.WriteString(cmd);

            cmd = string.Format(":AFR:SAVE:FILename '{0}','{1}'", fixture1, fixture2);
            ioDmm.WriteString(cmd);

            OPC();

            ioDmm.IO.Timeout = timeout;
        }

        public void DoFourPortDeembedding(int dutFileNumber, string fixture1File, string fixture2File)
        {
            int timeout = ioDmm.IO.Timeout;
            ioDmm.IO.Timeout = 100000;

            string cmd = string.Format(":FILE{0}:DEEMbed:FILename 1,'{1}'", dutFileNumber, fixture1File);
            ioDmm.WriteString(cmd);

            cmd = string.Format(":FILE{0}:DEEMbed:FILename 2,'{1}'", dutFileNumber, fixture2File);
            ioDmm.WriteString(cmd);

            cmd = string.Format("FILE{0}:DEEMbed:STATe ON", dutFileNumber);
            ioDmm.WriteString(cmd);

            OPC();

            ioDmm.IO.Timeout = timeout;
        }

        public void ExportFile(int fileNumber, int portCnt, string fileName, string resolution)
        {
            string cmd = ":EXPort:INITialize";
            ioDmm.WriteString(cmd);

            cmd = ":EXPort:FORMat RI";
            ioDmm.WriteString(cmd);

            cmd = string.Format(":EXPort:PORTs:COUNt {0}", portCnt);
            ioDmm.WriteString(cmd);

            cmd = ":EXPort:SDATa SENDed";
            ioDmm.WriteString(cmd);

            cmd = ":EXPort:UNIT HZ";
            ioDmm.WriteString(cmd);

            cmd = ":EXPort:RESolution " + resolution;
            ioDmm.WriteString(cmd);

            

            cmd = string.Format(":FILE{0}:EXPort '{1}'", fileNumber, fileName);
            ioDmm.WriteString(cmd);

        }

        public void ExportImage(int fileNumber, int viewNumber, int plotNumber, string filePath)
        {
            string cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:IMAGe:SAVE '{3}'", fileNumber, viewNumber, plotNumber, filePath);
            ioDmm.WriteString(cmd);
        }

        public void SaveTraceData(int fileNumber, int viewNumber, int plotNumber, int traceNumber, ref double[] xData, ref double[] yData)
        {
            int timeout = ioDmm.IO.Timeout;
            ioDmm.IO.Timeout = 200000;

            string cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:TRACe{3}:DATA:X?", fileNumber, viewNumber, plotNumber, traceNumber);

            ioDmm.WriteString(cmd);

            string result = ReadString();

            string[] arr = result.Split(',');
            int len = arr.Length;

            xData = new double[len];
            yData = new double[len];

            for (int i = 0; i < len; ++i)
            {
                xData[i] = double.Parse(arr[i]);
            }

            cmd = string.Format(":FILE{0}:VIEW{1}:PLOT{2}:TRACe{3}:DATA:Y?", fileNumber, viewNumber, plotNumber, traceNumber);

            ioDmm.WriteString(cmd);

            result = ReadString();

            arr = result.Split(',');
            for (int i = 0; i < len; ++i)
            {
                yData[i] = double.Parse(arr[i]);
            }

            ioDmm.IO.Timeout = timeout;
        }
    }

    public enum TimeDomainWindowTypes
    {
        EXPonential,
        KAISer,
        GAUSsian,
        CHEByshev,
        HANNing,
        HAMMing,
        BLACkman
    }

    public static class TimeDomainWindowTypesExtension
    {
        public static string ToCmdString(this TimeDomainWindowTypes type)
        {
            switch (type)
            {
                case TimeDomainWindowTypes.EXPonential:
                    return "EXPonential";
                case TimeDomainWindowTypes.KAISer:
                    return "KAISer";
                case TimeDomainWindowTypes.GAUSsian:
                    return "GAUSsian";
                case TimeDomainWindowTypes.CHEByshev:
                    return "CHEByshev";
                case TimeDomainWindowTypes.HANNing:
                    return "HANNing";
                case TimeDomainWindowTypes.HAMMing:
                    return "HAMMing";
                case TimeDomainWindowTypes.BLACkman:
                    return "BLACkman";
                default:
                    return "EXPonential";
            }
        }
    }

}
