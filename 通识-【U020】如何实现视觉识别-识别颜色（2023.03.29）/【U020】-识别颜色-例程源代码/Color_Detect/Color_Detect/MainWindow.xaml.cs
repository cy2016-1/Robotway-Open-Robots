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

namespace Color_Detect
{
    /// <summary>
    /// Color_Detect
    /// </summary>
    public partial class MainWindow : System.Windows.Window
    {
        /*
         * 指针角度对应各颜色
         * 25 -> 红色
         * 90 -> 绿色
         * 150 -> 蓝色
         */
        int ANGLE_RED = 0;
        int ANGLE_GREEN = 0;
        int ANGLE_BLUE = 0;

        //各颜色像素所占窗口的比例
        double numOfred = 0.0;
        double numOfgreen = 0.0;
        double numOfblue = 0.0;

        //创建视频图像实例
        VideoCapture capture = new VideoCapture("http://192.168.8.1:8083/?action=stream");
        Mat frame = new Mat();  //存储视频每一帧图像像素
        Mat resultColor = new Mat(); //存储检测后的颜色像素

        //视频显示切换变量
        Boolean isChange = false;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            ANGLE_RED = 25;
            ANGLE_GREEN = 90;
            ANGLE_BLUE = 150;
        }

        //颜色指示动画函数
        int angelCurrent = 0;

        private void ColorIndicate(int where) {
            RotateTransform rt = new RotateTransform();
            rt.CenterX = 150;
            rt.CenterY = 185;

            this.indicatorPin.RenderTransform = rt;

            double timeAnimation = Math.Abs(angelCurrent - where) * 5;
            DoubleAnimation da = new DoubleAnimation(angelCurrent, where, new Duration(TimeSpan.FromMilliseconds(timeAnimation)));
            da.AccelerationRatio = 0.8;
            rt.BeginAnimation(RotateTransform.AngleProperty, da);

            switch (where) {
                case 25:
                    colorDisplay.Content = "红色";
                    break;
                case 90:
                    colorDisplay.Content = "绿色";
                    break;
                case 150:
                    colorDisplay.Content = "蓝色";
                    break;
                default:
                    colorDisplay.Content = "颜色指示";
                    break;
            }

            angelCurrent = where;
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

        //颜色检测函数
        private void filterColor() {
            Mat hsvImage = frame.CvtColor(ColorConversionCodes.BGR2HSV);
            resultColor = new Mat(hsvImage.Rows, hsvImage.Cols, MatType.CV_8UC3, Scalar.All(255));

            double H = 0.0, S = 0.0, V = 0.0;
            float area = (float)(hsvImage.Rows * hsvImage.Cols);
            float rateOfred = 0, rateOfgreen = 0, rateOfblue = 0;

            for (int i = 0; i < hsvImage.Rows; i++) {
                for (int j = 0; j < hsvImage.Cols; j++) {

                    H = hsvImage.Get<Vec3b>(i, j)[0];
                    S = hsvImage.Get<Vec3b>(i, j)[1];
                    V = hsvImage.Get<Vec3b>(i, j)[2];

                    var color = frame.Get<Vec3b>(i, j);

                    if (((H >= 0 && H <= 10) || (H >= 125 && H <= 180)) && S >= 43 && V >= 46) //红色像素所在hsv范围
                    {
                        resultColor.Set<Vec3b>(i, j, color);
                        numOfred++;
                    }
                    else if ((H >= 33 && H <= 83) && S >= 43 && V >= 46) //绿色像素所在hsv范围
                    {
                        resultColor.Set<Vec3b>(i, j, color);
                        numOfgreen++;
                    }
                    else if ((H > 100 && H < 124) && S >= 43 && V >= 46) //蓝色像素所在hsv范围
                    {
                        resultColor.Set<Vec3b>(i, j, color);
                        numOfblue++;
                    }
                }
            }

            rateOfred = (float)(numOfred) / area * 100;
            rateOfgreen = (float)(numOfgreen) / area * 100;
            rateOfblue = (float)(numOfblue) / area * 100;

            if (rateOfred > 85)
            {
                ColorIndicate(ANGLE_RED);
            }
            else if (rateOfgreen > 85)
            {
                ColorIndicate(ANGLE_GREEN);
            }
            else if (rateOfblue > 85) {
                ColorIndicate(ANGLE_BLUE);
            }

            numOfred = 0;
            numOfgreen = 0;
            numOfblue = 0;
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
                                    filterColor();
                                    originImage.Source = BitmapToBitmapImage(MatToBitmap(resultColor));
                                    resultColor = null;
                                }
                                else {
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
            else {
                isChange = false;
                changeBtn.Content = "切换";

                //指针角度归零
                ColorIndicate(0);
            }
        }
    }
}
