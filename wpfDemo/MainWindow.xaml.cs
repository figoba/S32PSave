using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using Microsoft.Win32;

namespace wpfDemo
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DispatcherTimer timer=new DispatcherTimer(TimeSpan.FromMilliseconds(80),
                DispatcherPriority.Normal, (object sender, EventArgs args) =>
                {
                    int newValue = Counter == int.MaxValue ? 0 : Counter + 1;
                    SetValue(counterKey,newValue);

                },Dispatcher
                    );
        }

        private static readonly DependencyPropertyKey counterKey =
            DependencyProperty.RegisterReadOnly("Counter",
                typeof(int),
                typeof(MainWindow),
                new PropertyMetadata(0));

        public int Counter
        {
            get { return (int) GetValue(counterKey.DependencyProperty); }
        }

       

        private void BtnBrowse_OnClick(object sender, RoutedEventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();

        }

        private void BtnSave_OnClick(object sender, RoutedEventArgs e)
        {
            rtStatus.Background = Brushes.White;
            var driver = new CodeDriver();
            bool isError;
            rtStatus.AppendText(driver.CompileAndRun(TxtFilePath.Text, out isError));
            if (isError)
            {
                rtStatus.Background = Brushes.Red;
            }
        }
    }
}
