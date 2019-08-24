using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using DevComponents.DotNetBar;
using ZedGraph;
using Axis = ZedGraph.Axis;
using Chart = System.Windows.Forms.DataVisualization.Charting.Chart;
using Legend = System.Windows.Forms.DataVisualization.Charting.Legend;
using TabControl = DevComponents.DotNetBar.TabControl;


namespace S32PSave.Draw
{
    public enum LineType
    {
        Fre,
        Time,
        Spec
    }
    interface IChart
    {
        object ChartAdd(string testItem);
        bool ChartDel(string testItem);
        bool ChartDel();
        void DrawLine(object tChart, plotData temp, string seriName, LineType lineType);
        void DrawSpec(string itemName, Dictionary<string, plotData> spec, object tChart);
        void ChartClear(object tChart);
        

    }

    class VsChart:IChart
    {
        private TabControl doneTabControl;

        public VsChart(TabControl tabControl)
        {
            this.doneTabControl = tabControl;
        }
       
        public object ChartAdd(string testItem)
        {
            TabItem tim = doneTabControl.CreateTab(testItem);
            tim.Name = testItem;
            Chart chart = new Chart();
            chart.Name = testItem;
            chart.Width = 999;
            chart.Height = 336;
            chart.Location = new Point(4, 0);
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
            return chart;
        }

        public bool ChartDel(string testItem)
        {
           // chartDic.Remove(testItem);
            TabItem timRemove = doneTabControl.Tabs[testItem];
            doneTabControl.Tabs.Remove(timRemove);
            return true;
        }

        public bool ChartDel()
        {
           
            doneTabControl.Tabs.Clear();
            return true;
        }

        delegate void SetDrawLineCallBack(Chart chart, plotData temp, string serialName, LineType lineType);
        public void DrawLine(object oChart, plotData temp, string seriName, LineType lineType)
        {
            Chart chart = (Chart) oChart;
            if (chart.InvokeRequired)
            {

                SetDrawLineCallBack d = DrawLine;
                chart.Invoke(d, new object[] { chart, temp, seriName, lineType });
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

        public void DrawSpec(string itemName, Dictionary<string, plotData> spec, object tChart)
        {
            if (spec.ContainsKey(itemName + "_UPPER"))
            {
                DrawLine(tChart, spec[itemName + "_UPPER"], itemName + "_UPPER", LineType.Spec);
            }
            if (spec.ContainsKey(itemName + "_LOWER"))
            {
                DrawLine(tChart, spec[itemName + "_LOWER"], itemName + "_LOWER", LineType.Spec);
            }
        }
        delegate void SetchartClearCallback(Chart chart);
        public void ChartClear(object tChart)
        {
            Chart chart = (Chart) tChart;
            if (chart.InvokeRequired)
            {
                SetchartClearCallback d = new SetchartClearCallback(ChartClear);
                chart.Invoke(d, new object[] { chart });
            }
            else
            {
                chart.Series.Clear();
            }
        }
    }

    class ZedChart:IChart
    {
        private TabControl doneTabControl;

        public ZedChart(TabControl tabControl)
        {
            this.doneTabControl = tabControl;
        }
        public object ChartAdd(string testItem)
        {
            TabItem tim = doneTabControl.CreateTab(testItem);
            tim.Name = testItem;
            ZedGraphControl zedGraph = new ZedGraphControl();
            zedGraph.AutoSizeMode = AutoSizeMode.GrowOnly;
            zedGraph.Height = 237;
            zedGraph.Width = 751;
            zedGraph.Location=new Point(2, -1);
            
            
            GraphPane myPane = zedGraph.GraphPane;

            // Set the titles and axis labels

            myPane.Title.Text = testItem;
            myPane.Title.IsVisible = false;
            //myPane.Title.FontSpec=
            myPane.XAxis.MajorGrid.IsVisible = true;
            myPane.XAxis.MajorGrid.DashOn = 1000;
            myPane.YAxis.MajorGrid.DashOn = 1000;

            myPane.YAxis.MajorGrid.IsVisible = true;
            myPane.XAxis.Title.IsVisible = false;
           // myPane.XAxis.Title.Text = "X Value Figo";
            myPane.Chart.Border.IsVisible = false;//首先设置边框为无
            myPane.XAxis.MajorTic.IsOpposite = false;//然后设置X轴对面轴大间隔为无
            myPane.XAxis.MinorTic.IsOpposite = false;//然后设置X轴对面轴大间隔为无
            myPane.YAxis.MajorTic.IsOpposite = false;//设置Y轴对面轴大间隔为无
            myPane.YAxis.MinorTic.IsOpposite = false;//设置Y轴对面轴小间隔为无
            myPane.YAxis.Title.IsVisible = false;
            
            myPane.XAxis.MinorGrid.IsVisible = false;

            if (testItem.StartsWith("T"))
            {
                myPane.XAxis.Scale.MajorStep = 1;
                myPane.XAxis.Scale.Max = 5.0;
            }
            else
            {
                myPane.XAxis.Scale.MajorStep = 5000000000;
                myPane.XAxis.Scale.Max = 26500000000;
            }
           
            
            myPane.XAxis.ScaleFormatEvent += XAxis_ScaleFormatEvent; 
            myPane.CurveList.Clear();
            tim.AttachedControl.Controls.Add(zedGraph);
            return zedGraph;
        }

        public bool ChartDel(string testItem)
        {
            // chartDic.Remove(testItem);
            TabItem timRemove = doneTabControl.Tabs[testItem];
            doneTabControl.Tabs.Remove(timRemove);
            return true;
        }

        public bool ChartDel()
        {
            doneTabControl.Tabs.Clear();
            return true;
        }

        delegate void SetDrawLineCallBack(ZedGraphControl chart, plotData temp, string serialName, LineType lineType);
        public void DrawLine(object tChart, plotData temp, string seriName, LineType lineType)
        {
            ZedGraphControl chart = (ZedGraphControl)tChart;
            GraphPane myPane = chart.GraphPane;
            if (chart.InvokeRequired)
            {

                SetDrawLineCallBack d = DrawLine;
                chart.Invoke(d, new object[] { chart, temp, seriName, lineType });
            }
            else
            {


                PointPairList list = new PointPairList();
                //int length = temp.xData.Length;

                //for (int i = 0; i < length; i++)
                //{
                //    list.Add(temp.xData[i],temp.yData[i]);

                //}
                //double[]a=new double[100];
                // Generate a blue curve with circle symbols, and "My Curve 2" in the legend
                LineItem myCurve1 =
                    new LineItem(seriName, temp.xData.Select(x => (double)x).ToArray(), temp.yData.Select(x => (double)x).ToArray(),
                        lineType == LineType.Spec ? Color.Red : Util.getRandomColor(), SymbolType.None, 0.1f);
                myCurve1.Line.IsSmooth = true;
                myCurve1.Line.SmoothTension = 0.1F;
                myCurve1.Line.GradientFill.Type = FillType.Brush;
                myPane.CurveList.Add(myCurve1);
               // myPane.AddCurve(seriName, temp.xData.Select(x => (double)x).ToArray(), temp.yData.Select(x => (double)x).ToArray(), lineType == LineType.Spec ? Color.Red : Util.getRandomColor(), SymbolType.None);
                
                myPane.Legend.Position = LegendPos.InsideBotRight;


               
                chart.AxisChange();
                //chart.IsAntiAlias = true;
                chart.Refresh();
            }
        }

        public void DrawSpec(string itemName, Dictionary<string, plotData> spec, object tChart)
        {
            if (spec.ContainsKey(itemName + "_UPPER"))
            {
                DrawLine(tChart, spec[itemName + "_UPPER"], itemName + "_UPPER", LineType.Spec);
            }
            if (spec.ContainsKey(itemName + "_LOWER"))
            {
                DrawLine(tChart, spec[itemName + "_LOWER"], itemName + "_LOWER", LineType.Spec);
            }
        }
        delegate void SetchartClearCallback(ZedGraphControl chart);
        public void ChartClear(object tChart)
        {
            ZedGraphControl chart = (ZedGraphControl)tChart;
            if (chart.InvokeRequired)
            {
                SetchartClearCallback d = new SetchartClearCallback(ChartClear);
                chart.Invoke(d, new object[] { chart });
            }
            else
            {
                chart.GraphPane.CurveList.Clear();
                chart.Refresh();
            }
        }
        string XAxis_ScaleFormatEvent(GraphPane pane, Axis axis, double val, int index)
        {
            string name = pane.Title.Text;
            if (name.StartsWith("T"))
            {
                return (index  + "ns");
            }
            else
            {
                return (index * 5 + "Ghz");
            }
            //根据 val值 返回你需要的 string
            
        }
    }
}
