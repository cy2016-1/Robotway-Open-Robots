/*******************************************************************************************
版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-02 https://www.robotway.com/
---------------------------------------------------------------------------------------
using System;
using System.IO;
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
using System.Windows.Media.Animation;
using System.Threading;
using OpenCvSharp;
using System.Drawing;
using System.Drawing.Imaging;
using System.Net;
using System.Net.Sockets;

namespace Tracking_Car
{
    /// <summary>
    /// Tracking_Car
    /// </summary>
    public partial class MainWindow : System.Windows.Window
    {
        //定义视频，控制地址以及控制端口变量
        static string CameraIp = "http://192.168.8.1:8083/?action=stream";
        static string ControlIp = "192.168.8.1";
        static string Port = "2001";

        //定义上位机发送的控制命令变量
        //定义命令变量
        string CMD_FORWARD = "", CMD_TURN_LEFT = "", CMD_TURN_RIGHT = "", CMD_STOP = "";

        /*
         * 指针角度对应各颜色
         * 25 -> 红色
         * 90 -> 绿色
         * 150 -> 蓝色
         */
        int ANGLE_LEFT = 0;
        int ANGLE_GO = 0;
        int ANGLE_RIGHT = 0;

        //黑色像素在左右两侧所占比例
        double numOfleft = 0.0;
        double numOfright = 0.0;

        //创建视频图像实例
        VideoCapture capture = new VideoCapture(CameraIp); //图像大小：宽度 X 长度 = 160 X 120;
        Mat frame = new Mat();  //存储视频每一帧图像像素
        Mat result = new Mat(); //存储二值化图像

        static byte[] kernelValues = { 0, 1, 0, 1, 1, 1, 0, 1, 0 }; // cross (+)
        Mat kernel = new Mat(3, 3, MatType.CV_8UC1, kernelValues);

        //图像中心线坐标
        int x1, y1, x2, y2;
        //窗口面积
        float area;

        //视频显示切换变量
        Boolean isChange = false;
        //循迹开始开关变量
        Boolean isBegin = false;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Assignment();
        }

        //变量赋值函数
        private void Assignment()
        {
            ANGLE_LEFT = 25;
            ANGLE_GO = 90;
            ANGLE_RIGHT = 150;

            rateLeft.Height = 10;
            rateRight.Height = 10;

            x1 = 80;
            y1 = 0;
            x2 = x1;
            y2 = 120;
            area = 160 * 120 / 2;

            CMD_FORWARD = "F";
            CMD_TURN_LEFT = "L";
            CMD_TURN_RIGHT = "R";
            CMD_STOP = "S";
        }

        /// <summary>
        /// MatToBitmap(Mat image)
        /// </summary>
        public static Bitmap MatToBitmap(Mat image)
        {
            return OpenCvSharp.Extensions.BitmapConverter.ToBitmap(image);
        }

        /// <summary>
        /// BitmapToBitmapImage(System.Drawing.Bitmap bitmap)
        /// </summary>
        public static BitmapImage BitmapToBitmapImage(Bitmap bitmap)
        {
            using (MemoryStream stream = new MemoryStream())
            {
                bitmap.Save(stream, ImageFormat.Png); //格式选Bmp时，不带透明度

                stream.Position = 0;
                BitmapImage result = new BitmapImage();
                result.BeginInit();
                // According to MSDN, "The default OnDemand cache option retains access to the stream until the image is needed."
                // Force the bitmap to load right now so we can dispose the stream.
                result.CacheOption = BitmapCacheOption.OnLoad;
                result.StreamSource = stream;
                result.EndInit();
                result.Freeze();
                return result;
            }
        }

        //颜色指示动画函数
        int angelCurrent = 0;
        private void ColorIndicate(int where)
        {
            RotateTransform rt = new RotateTransform();
            rt.CenterX = 130;
            rt.CenterY = 200;

            this.indicatorPin.RenderTransform = rt;

            double timeAnimation = Math.Abs(angelCurrent - where) * 5;
            DoubleAnimation da = new DoubleAnimation(angelCurrent, where, new Duration(TimeSpan.FromMilliseconds(timeAnimation)));
            da.AccelerationRatio = 0.8;
            rt.BeginAnimation(RotateTransform.AngleProperty, da);

            switch (where)
            {
                case 25:
                    dirDisplay.Content = "左转";
                    break;
                case 90:
                    dirDisplay.Content = "前进";
                    break;
                case 150:
                    dirDisplay.Content = "右转";
                    break;
                default:
                    dirDisplay.Content = "方向指示";
                    break;
            }

            angelCurrent = where;
        }

        //检测函数
        private void ColorDetect() {
            //将摄像头RGB图像转化为灰度图，便于后续算法处理
            Mat gray = frame.CvtColor(ColorConversionCodes.BGR2GRAY);
            //进行高斯滤波
            Mat binary = gray.Threshold(0, 255, ThresholdTypes.Otsu | ThresholdTypes.Binary);
            //闭运算，先膨胀后腐蚀，消除小型黑洞
            Cv2.Dilate(binary, binary, null);
            Cv2.Erode(binary, binary, kernel);

            result = binary.Clone();
            result.Line(new OpenCvSharp.Point(x1, y1), new OpenCvSharp.Point(x2, y2), new Scalar(255, 255, 255), 1);

            float rateOfleft = 0, rateOfRight = 0;
            var indexer = result.GetGenericIndexer<Vec3b>();
            for (int i = 0; i < result.Rows; i++) {
                for (int j = 0; j < result.Cols; j++) {
                    int B = indexer[i, j][0];
                    int G = indexer[i, j][1];
                    int R = indexer[i, j][2];

                    if (B == 0 && G == 0 && R == 0) {
                        if (j <= x1) {
                            numOfleft++;
                        }
                        else
                        {
                            numOfright++;
                        }
                    }
                }
            }

            rateOfleft = (float)(numOfleft) / area * 100;
            rateOfRight = (float)(numOfright) / area * 100;
            rateLeft.Height = rateOfleft;
            rateRight.Height = rateOfRight;
            numOfleft = 0;
            numOfright = 0;
        }

        //命令发送函数
        void SendData(string data)
        {
            try
            {
                IPAddress ips = IPAddress.Parse(ControlIp.ToString());//("192.168.8.1");
                IPEndPoint ipe = new IPEndPoint(ips, Convert.ToInt32(Port.ToString()));//把ip和端口转化为IPEndPoint实例
                Socket c = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);//创建一个Socket

                c.Connect(ipe);//连接到服务器

                byte[] bs = Encoding.ASCII.GetBytes(data);
                c.Send(bs, bs.Length, 0);//发送测试信息
                c.Close();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        //方向指示更新及命令发送
        private void CommandSend() {
            double l = rateLeft.Height;
            double r = rateRight.Height;

            if (isBegin) {
                if (Math.Abs(l - r) < 20)   //两侧黑色轨迹基本相同，前进
                {
                    ColorIndicate(ANGLE_GO);
                    SendData(CMD_FORWARD);
                }
                else if ((l - r) < -50)     //左侧黑色轨迹小于右侧，右转
                {
                    ColorIndicate(ANGLE_RIGHT);
                    SendData(CMD_TURN_RIGHT);

                }
                else if ((l - r) > 50)      //右侧黑色轨迹小于左侧，左转
                {
                    ColorIndicate(ANGLE_LEFT);
                    SendData(CMD_TURN_LEFT);
                }
            }
        }

        //视频显示函数
        private void ThreadCapShow()
        {

            while (true)
            {
                try
                {
                    capture.Read(frame); // same as cvQueryFrame
                    if (frame.Empty())
                        break;

                    this.Dispatcher.Invoke(
                        new Action(
                            delegate
                            {
                                if (isChange)
                                {
                                    //检测图像左右两侧黑色像素所占的比例，并显示图像
                                    ColorDetect();
                                    originImage.Source = BitmapToBitmapImage(MatToBitmap(result));
                                    CommandSend();
                                    result = null;
                                }
                                else
                                {
                                    originImage.Source = BitmapToBitmapImage(MatToBitmap(frame));
                                }
                            }
                            ));
                    //Cv2.WaitKey(100);
                    //bitimg = null;
                }
                catch { }
            }
        }

        //加载视频
        private void loadBtn_Click(object sender, RoutedEventArgs e)
        {
            if (originImage.Source != null) return;
            Thread m_thread = new Thread(ThreadCapShow);
            m_thread.IsBackground = true;
            m_thread.Start();
        }

        //切换视频显示，显示检测结果
        private void changeBtn_Click(object sender, RoutedEventArgs e)
        {
            if (!isChange)
            {
                isChange = true;
                changeBtn.Content = "返回";
            }
            else
            {
                isChange = false;
                changeBtn.Content = "切换";

                //指针角度归零
                ColorIndicate(0);
                rateLeft.Height = 10;
                rateRight.Height = 10;
                result = null;
            }
        }

        //循迹开始
        private void bgeinBtn_Click(object sender, RoutedEventArgs e)
        {
            isBegin = true;
        }

        //循迹停止
        private void stopBtn_Click(object sender, RoutedEventArgs e)
        {
            isBegin = false;
            SendData(CMD_STOP);
        }

    }
}
