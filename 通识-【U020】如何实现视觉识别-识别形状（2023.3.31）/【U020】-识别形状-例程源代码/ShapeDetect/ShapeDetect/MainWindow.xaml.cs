using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

namespace ShapeDetect
{
    /// <summary>
    /// 形状识别
    /// </summary>
    public partial class MainWindow : Window
    {
        //定义检测模式
        int IMAGE_MODE = 1, VIDEO_MODE = 2;

        private AutoResetEvent exitEvent;
        private Thread m_thread;

        //导入动态链接库
        [DllImport("HoughCircles_DLL.dll")]
        //检测圆
        public static extern System.UIntPtr HoughCircles([MarshalAs(UnmanagedType.LPStr)]string address, int detect_mode);
        [DllImport("SquareDetect_DLL.dll")]
        //检测矩形
        public static extern void SquareDetector([MarshalAs(UnmanagedType.LPStr)]string address, int detect_mode);

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            GetIni();
            imgCheckBtn.IsChecked = true;
            circleCheckBtn.IsChecked = true;
        }

        //获取ini配置文件信息
        private void GetIni()
        {
            ini_RW.FileName = System.Windows.Forms.Application.StartupPath + "\\Config.ini";
            this.videoAddress.Text = ini_RW.ReadIni("VideoUrl", "videourl", "");
            this.ipAddress.Text = ini_RW.ReadIni("ControlUrl", "controlUrl", "");
            this.portBox.Text = ini_RW.ReadIni("ControlPort", "controlPort", "");
        }

        //修改配置
        private void setBtn_Click(object sender, RoutedEventArgs e)
        {
            ini_RW.WriteIni("VideoUrl", "videourl", this.videoAddress.Text);
            ini_RW.WriteIni("ControlUrl", "controlUrl", this.ipAddress.Text);
            ini_RW.WriteIni("ControlPort", "controlPort", this.portBox.Text);

            System.Windows.MessageBox.Show("配置成功！请重启程序以使配置生效。", "配置信息", MessageBoxButton.OK, MessageBoxImage.Information);
            //this.Close();
        }

        //计数清零
        private void BoxClean()
        {
            circleTextBox.Text = "0";
            recTextBox.Text = "0";
        }

        //打开图片地址
        private void imgBtn_Click(object sender, RoutedEventArgs e)
        {
            try
            {

                BoxClean();
                //WPF中，OpenFileDialog位于Microsoft.Win32名称空间
                Microsoft.Win32.OpenFileDialog dialog = new Microsoft.Win32.OpenFileDialog();
                dialog.Filter = "All files (*.*)|*.*|jpg files (*.jpg)|*.jpg|png files(*.png)|*.png";

                if (dialog.ShowDialog() == true)
                {

                    string path = dialog.FileName;
                    imgAddressBox.Text = path;
                }
            }
            catch { };
        }

        //检测形状判断
        private void ShapeDetect(string address, int mode)
        {
            if (circleCheckBtn.IsChecked == true)
            {
                //System.Windows.MessageBox.Show("检测圆形");
                circleTextBox.Text = HoughCircles(address, mode).ToString();
            }
            else if (recCheckBtn.IsChecked == true)
            {
                //System.Windows.MessageBox.Show("检测矩形");
                SquareDetector(address, mode);
            }
        }

        //图片检测
        private void imgDetect()
        {

            if (imgAddressBox.Text == string.Empty)
            {
                System.Windows.MessageBox.Show(
                    "图片地址为空，请选择一张图片", "警告",
                    MessageBoxButton.OK,
                    MessageBoxImage.Information
                    );
                return;
            }
            else
            {
                ShapeDetect(imgAddressBox.Text, IMAGE_MODE);
            }
        }

        //视频检测
        private void videoDetect()
        {
            try
            {
                while (true)
                {
                    this.Dispatcher.Invoke(
                        new Action(
                            delegate
                            {
                                string ip = this.videoAddress.Text;
                                ShapeDetect(ip, VIDEO_MODE);
                            }
                            ));
                }

            }
            catch { };
        }

        //判断检测为图片还是视频，开启形状检测
        private void detectBtn_Click(object sender, RoutedEventArgs e)
        {
            BoxClean();
            if (imgCheckBtn.IsChecked == true)
            {
                imgDetect();
            }
            else if (videoCheckBtn.IsChecked == true)
            {
                try
                {
                    m_thread = new Thread(new ThreadStart(videoDetect));
                    m_thread.Start();
                }
                catch { };
            }
        }

        //按esc键退出视频检测，结束线程
        private void Window_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                exitEvent.Set();
                m_thread.Join();
            }
        }

    }
}
