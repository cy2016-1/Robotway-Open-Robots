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
using System.IO;
using System.IO.Ports;
using System.Xml;
using System.Windows.Markup;
using Controler_Panel;
using Command_Text;
using Check_Lable;
using AboutWindow;

namespace Controler_1._0
{
    /// <summary>
    /// 32路舵机控制上位机软件
    /// 编写时间：2018/2/11-2018/2/16
    /// 编写人：aries.hu <noob>
    /// 😀//////😀
    /// </summary>
    public partial class MainWindow : Window
    {
        /***************命令行选择删除开关**********/
        Boolean selected = false;
        /***************存储面板控件值**************/
        string cmdData = "";
        string pwmData = "";
        /***************编号**************/
        double num = 0;     //添加命令编号
        double numSelect = 0; //记录选择命令行编号
        /***************自定义控件行数及列数********/
        double rows = 4;
        double cols = 9;

        /****************拖动事件变量***************/
        bool enableMove = false;
        double distanceLeft = 0;
        double distanceTop = 0;

        public static SerialPort serialPort;   //串口对象类

        public MainWindow()
        {
            InitializeComponent();
            this.ResizeMode = System.Windows.ResizeMode.CanMinimize;

        }
        
        public void Window_Loaded(object sender, RoutedEventArgs e)
        {
            string[] baud = { "9600", "19200", "38400", "57600", "115200", "128000" }; //定义波特率数组
            canvas.Children.Clear();
            ListBaud.Items.Clear();

            /********************添加自定义调节控件**********************************/
            UserControlAdd(rows, cols);


            /*******************添加波特率到列表项*******************************************/
            foreach (string BaudStr in baud)
            {
                ListBaud.Items.Add(BaudStr);
            }
            
        }

        //自定义控件位置初始化
        public void UserControlAdd(double _rows, double _cols) {
            double pins = 0; 

            for (int i = 0; i < _rows; i++)
            {
                for (int j = 0; j < _cols; j++)
                {
                    if (pins < 32)
                    {
                        ControlPanel panel = new ControlPanel(pins);
                        CheckLable check = new CheckLable(pins);

                        Canvas.SetLeft(panel, 10 + 105 * j);
                        Canvas.SetTop(panel, 10 + 75 * i);
                        Canvas.SetLeft(check, 50 + 45 * j);
                        Canvas.SetTop(check, 20 + 25 * i);

                        //注册事件
                        panel.text.KeyDown += Text_KeyDown;
                        panel.slider.ValueChanged += slider_ValueChanged;
                        panel.label.MouseLeftButtonDown += Label_MouseLeftButtonDown;
                        panel.label.MouseLeftButtonUp += Label_MouseLeftButtonUp;
                        panel.label.MouseMove += Label_MouseMove;

                        check.checkBox.Checked += CheckBox_Checked;
                        check.checkBox.Unchecked += CheckBox_Unchecked;

                        canvas.Children.Add(panel);
                        setCanvas.Children.Add(check);
                        pins++;
                    }
                }
            }
        }

        //查找父控件
        public static T GetParentObject<T>(DependencyObject obj) where T : FrameworkElement
        {
            DependencyObject parent = VisualTreeHelper.GetParent(obj);

            while (parent != null)
            {
                if (parent is T)
                {
                    return (T)parent;
                }

                // 在上一级父控件中没有找到指定名字的控件，就再往上一级找
                parent = VisualTreeHelper.GetParent(parent);
            }

            return null;
        }

        /******************+++++++++++++++-----------串口部分-----------+++++++++++++++++++++**************/
        //查找串口并添加到列表项
        private void ListCom_DropDownOpened(object sender, EventArgs e)
        {
            //Get the Serial Ports
            string[] sCom = SerialPort.GetPortNames();
            if (sCom != null)
            {
                ListCom.Items.Clear();
                foreach (string sComNumber in sCom)
                {
                    ListCom.Items.Add(sComNumber);
                }
            }
        }

        //打开串口
        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                try
                {
                    serialPort = new SerialPort();
                    //更改参数
                    serialPort.PortName = ListCom.Text;
                    serialPort.BaudRate = Convert.ToInt32(ListBaud.Text);
                    serialPort.Parity = Parity.None;
                    serialPort.StopBits = StopBits.One;
                }
                catch
                {
                    MessageBox.Show("未选择端口，请至少添加一个？", "无端口", MessageBoxButton.OK, MessageBoxImage.Information);
                }

                serialPort.Open();
                ListCom.IsEnabled = false;
                ListBaud.IsEnabled = false;
                btnOpen.IsEnabled = false;
            }
            catch { };

        }

        //关闭串口
        private void btnClose_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                serialPort.Close();
                ListCom.IsEnabled = true;
                ListBaud.IsEnabled = true;
                btnOpen.IsEnabled = true;
            }
            catch { }
        }

        //串口发送数据
        private void sendCommand(string CommandString)
        {
            byte[] WriteBuffer = Encoding.ASCII.GetBytes(CommandString);
            serialPort.Write(WriteBuffer, 0, WriteBuffer.Length);
        }

        /******************+++++++++++++++---------------自定义调节控件部分--------------+++++++++++++++++++++**************/
        //鼠标移动
        private void Label_MouseMove(object sender, MouseEventArgs e)
        {

            if (enableMove)
            {
                Label label = sender as Label;

                //查找父控件
                var parent = GetParentObject<ControlPanel>((DependencyObject)label);
                var cLeft = 0.00;
                var cTop = 0.00;
                var minLeft = 0.00;
                var maxLeft = canvas.ActualWidth - parent.ActualWidth;
                var minTop = 0.00;
                var maxTop = canvas.ActualHeight-270;

                cLeft = e.GetPosition(canvas).X - distanceLeft;
                cTop = e.GetPosition(canvas).Y - distanceTop;

                //边界判断
                if (cLeft < minLeft)
                {
                    cLeft = minLeft;
                }
                else if (cLeft > maxLeft)
                {
                    cLeft = maxLeft;
                }

                if (cTop < minTop)
                {
                    cTop = minTop;
                }
                else if (cTop > maxTop)
                {
                    cTop = maxTop;
                }

                //设置要拖动控件的位置
                Canvas.SetLeft((UIElement)parent, cLeft);
                Canvas.SetTop((UIElement)parent, cTop);
            }
            
        }

        //鼠标释放
        private void Label_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Label label = sender as Label;

            //释放鼠标捕获
            label.ReleaseMouseCapture();
            enableMove = false;
            distanceLeft = 0;
            distanceTop = 0;
        }

        //鼠标按下
        private void Label_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Label label = sender as Label;

            //查找父控件
            var parent = GetParentObject<ControlPanel>((DependencyObject)label);

            //创建鼠标捕获
            Mouse.Capture(label);
            enableMove = true;

            //计算鼠标相对于要拖动的控件的位置
            distanceLeft = e.GetPosition(canvas).X - Canvas.GetLeft((UIElement)parent);
            distanceTop = e.GetPosition(canvas).Y - Canvas.GetTop((UIElement)parent);
            
        }

        //手动输入文本框数据按回车发送数据
        private void Text_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                TextBox text = sender as TextBox;

                if (e.Key == Key.Enter)
                {
                    double pwmData = Convert.ToInt32(text.Text);
                    if (pwmData >= 500 && pwmData <= 2500)
                    {
                        sendCommand("#" + text.Name.Split('_')[1] + "P" + text.Text + "T0\n");
                    }
                    else
                        MessageBox.Show("请输入正确的数值！\n(500-2500)", "数值错误", MessageBoxButton.OK, MessageBoxImage.Information);

                }
            }
            catch { }
        }

        //拖动slider控件发送数据,数据格式如：#2P2333T0\n
        private void slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            try
            {
                Slider slider = sender as Slider;
                sendCommand("#"+slider.Name.Split('_')[1]+"P"+slider.Value.ToString()+"T0\n");
            }
            catch { }
        }

        /******************+++++++++++++++-------------About窗口部分----------------+++++++++++++++++++++**************/
        //打开About窗口
        private void about_Click(object sender, RoutedEventArgs e)
        {
            //NavigationWindow window = new NavigationWindow();
            //window.Source = new Uri("About.xaml", UriKind.Relative);
            //window.Show();

            About aboutWin = new About();
            aboutWin.ShowDialog();
        }

        /******************+++++++++++++++-------------设置面板部分----------------+++++++++++++++++++++**************/
        public void SettingPanel()
        {
            if (setCanvas.Visibility == Visibility.Hidden)
            {
                setCanvas.Visibility = Visibility.Visible;
            }
            else
                setCanvas.Visibility = Visibility.Hidden;
        }

        //打开Setting面板
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            SettingPanel();
        }

        //快捷键打开Setting面板，P键
        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.P)
            {
                SettingPanel();
            }
        }

        //设置面板设置主窗口调节控件的显示和隐藏
        public void HideShow(string _pin, Boolean _static)
        {
            foreach (var c in canvas.Children)
            {
                if (c is ControlPanel)
                {
                    ControlPanel sp = (ControlPanel)c;
                    if (sp.Name.Split('_')[1] == _pin)
                    {
                        if (_static) {
                            sp.Visibility = Visibility.Hidden;
                        }
                        else
                            sp.Visibility = Visibility.Visible;
                    }
                }
            }
        }

        //设置面板设置主窗口调节控件的显示和隐藏全部
        public void HideShowAll(Boolean _static)
        {
            foreach (var c in canvas.Children)
            {
                if (c is ControlPanel)
                {
                    ControlPanel sp = (ControlPanel)c;
                    if (_static)
                    {
                        sp.Visibility = Visibility.Hidden;
                    }
                    else
                        sp.Visibility = Visibility.Visible;
                    
                }
            }
            foreach (var c in setCanvas.Children)
            {
                if (c is CheckLable)
                {
                    CheckLable sc = (CheckLable)c;
                    if (_static)
                    {
                        sc.checkBox.IsChecked = true;
                    }
                    else
                        sc.checkBox.IsChecked = false;
                }
            }
        }

        //显示控件
        private void CheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            CheckBox check = sender as CheckBox;
            HideShow(check.Name.Split('_')[1], (bool)check.IsChecked);
        }

        //隐藏控件
        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox check = sender as CheckBox;
            HideShow(check.Name.Split('_')[1], (bool)check.IsChecked);
        }

        //隐藏全部自定义调节控件
        private void checkAll_Checked(object sender, RoutedEventArgs e)
        {
            HideShowAll((bool)checkAll.IsChecked);
            checkStatic.Content = "显示";
        }

        //显示全部自定义控件
        private void checkAll_Unchecked(object sender, RoutedEventArgs e)
        {
            HideShowAll((bool)checkAll.IsChecked);
            checkStatic.Content = "隐藏";
        }

        //重置全部自定义控件位置
        private void initBtn_Click(object sender, RoutedEventArgs e)
        {
            double _r = 0; //定义行
            double _c = 0; //定义列
            double count = 9; //定义每行最大列数
            foreach (var c in canvas.Children)
            {
                if (c is ControlPanel)
                {
                    ControlPanel sp = (ControlPanel)c;
                    sp.slider.Value = 1500;
                    double pin = Convert.ToInt32(sp.Name.Split('_')[1]);

                    if ( pin % count == 0 && _c != 0)
                    {
                        _c = 0;
                        _r++;
                        Canvas.SetLeft(sp, 10 + 105 * _c);
                        Canvas.SetTop(sp, 10 + 75 * _r);
                    }
                    else
                    {
                        _c++;
                        Canvas.SetLeft(sp, 10 + 105 * (_c = pin == 0 ? 0 : _c));
                        Canvas.SetTop(sp, 10 + 75 * _r);
                    }
                }
            }
            _r = 0;
            _c = 0;
        }

        //选择结束,关闭面板
        private void setBtn_Click(object sender, RoutedEventArgs e)
        {
            setCanvas.Visibility = Visibility.Hidden;
        }

        /******************+++++++++++++++--------------文件操作部分---------------+++++++++++++++++++++**************/
        //从命令获取数值并更新面板控件
        public void panelUpdate(string command)
        {
            //MessageBox.Show(command);
            //#2P1500#3P1500#4P1500#5P1500#6P1500#7P1500T0
            int countPin = 0;   //计数
            int countValue = 0;
            int[] pin = new int[32];
            int[] value = new int[32];
            
            //字符串拆分
            string[] sArray = command.Split(new char[3] { '#', 'P','T'});
            for (var i = 1; i < sArray.Length-1; i++)
            {
                if (i % 2 == 0)
                {
                    value[countValue] = Convert.ToInt32(sArray[i]);
                    //MessageBox.Show(value[countValue] + "");
                    pwmData += value[countValue] + ",";
                    countValue++;
                }
                else
                {
                    pin[countPin] = Convert.ToInt32(sArray[i]);
                    //MessageBox.Show(pin[countPin] + "");
                    countPin++;
                }
            }
            pwmData += "\r\n";
            countPin = 0;
            countValue = 0;

            //更新控件数值
            foreach (var c in canvas.Children)
            {
                if (c is ControlPanel)
                {
                    ControlPanel sp = (ControlPanel)c;
                    if (Convert.ToInt32(sp.label.Name.Split('_')[1]) == pin[countPin])
                    {
                        //sp.text.Text =value[countValue].ToString();
                        sp.slider.Value = value[countValue];
                        countPin++;
                        countValue++;
                    }
                }
            }

            
        }

        //清空命令数据
        public void cmdClear()
        {
            cmdwrapper.Children.Clear();
            num = 0;
            cmdData = "";
            pwmData = "";
            fileAddress.Content = "";
        }

        //打开数据文件，并更新控件
        private void openFiles_Click(object sender, RoutedEventArgs e)
        {
            //WPF中，OpenFileDialog位于Microsoft.Win32名称空间
            Microsoft.Win32.OpenFileDialog dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.Filter = "文本文件|*.txt";

            if (dialog.ShowDialog() == true)
            {
                //清空命令行数据
                cmdClear();
                fileAddress.Content = dialog.FileName;

                FileStream fs = new FileStream(fileAddress.Content+"", FileMode.Open, FileAccess.Read);
                StreamReader cmdData = new StreamReader(fs);
                cmdData.BaseStream.Seek(0, SeekOrigin.Begin);
                string strLine = cmdData.ReadLine();

                while (strLine != null)
                {
                    //MessageBox.Show(strLine);
                    panelUpdate(strLine);   //更新调节控件数值

                    //添加命令行数据
                    CommandText panel = new CommandText(num, strLine);
                    panel.cmdBtn.Click += CmdBtn_Click;
                    panel.cmdLabel.MouseDown += CmdLabel_MouseDown;
                    cmdwrapper.Children.Add(panel);

                    strLine = cmdData.ReadLine();
                    num++;
                }

                //关闭StreamReader对象
                cmdData.Close();
                pwmData = "";
            }
        }

        //保存数据文件
        private void saveFiles_Click(object sender, RoutedEventArgs e)
        {
            //获取数据并保存为.txt文本文件
            string output = "";

            //遍历命令行
            foreach (var c in cmdwrapper.Children)
            {
                if (c is CommandText)
                {
                    CommandText cm = (CommandText)c;
                    output += cm.cmdLabel.Content + "\r\n";
                }
            }

            //创建文件对象并写入
            var saveFileDialog = new Microsoft.Win32.SaveFileDialog();
            saveFileDialog.Filter = "TXT File(*.txt)|*.txt";
            var result = saveFileDialog.ShowDialog();
            if (result == true)
            {
                FileStream savefs = new FileStream(saveFileDialog.FileName, FileMode.Create);
                StreamWriter savesw = new StreamWriter(savefs);
                savesw.Flush();

                foreach (var s in output)
                {
                    savesw.Write(s);
                }

                savesw.Close();
            }
        }

        /******************+++++++++++++++--------------命令添加面板部分---------------+++++++++++++++++++++**************/
        //添加命令数据
        private void addBtn_Click(object sender, RoutedEventArgs e)
        {
            //显示区舵机数量判断以及数据获取,判断显示区是否有调节控件，添加数据需要至少一个调节控件，即一个舵机

            var i = 0; //统计显示区全部控件数量
            var pins = 32;

            foreach (var c in canvas.Children)
            {
                if (c is ControlPanel)
                {
                    ControlPanel sp = (ControlPanel)c;

                    if (sp.Visibility.ToString().ToLower() == "visible")
                    {
                        cmdData += "#" + sp.label.Name.Split('_')[1] + "P" + sp.text.Text;
                    }
                    else if (sp.Visibility.ToString().ToLower() == "hidden")
                    {
                        i++;
                        if (i == pins)
                        {
                            i = 0;
                            cmdData = "";
                            MessageBox.Show("没有舵机，请至少添加一个？", "未添加舵机", MessageBoxButton.OK, MessageBoxImage.Information);
                            return;
                        }
                    }
                }
            }

            
            //判断要添加的行数据与上一行数据是否重复
            foreach (var c in cmdwrapper.Children)
            {
                if (c is CommandText)
                {
                    CommandText cm = (CommandText)c;
                    if (Convert.ToInt32(cm.cmdLabel.Name.Split('_')[1]) == num - 1)
                    {
                        if (cm.cmdLabel.Content.ToString() == cmdData + "T0")
                        {
                            if (MessageBox.Show("数据没有变化，是否添加？", "重复", MessageBoxButton.YesNo, MessageBoxImage.Information) == MessageBoxResult.No)
                            {
                                cmdData = "";
                                return;
                            }
                        }
                    }

                }
            }
            

            cmdData += "T0";  //此处定义一个时间字符串，时间为0
            CommandText panel = new CommandText(num, cmdData);
            panel.cmdBtn.Click += CmdBtn_Click;
            panel.cmdLabel.MouseDown += CmdLabel_MouseDown;
            cmdwrapper.Children.Add(panel);
            num++;
            cmdData = "";
        }

        //选择命令数据行
        private void CmdLabel_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Label selectLable = sender as Label;
            numSelect =Convert.ToDouble(selectLable.Name.Split('_')[1]);

            //MessageBox.Show(numSelect+"");

            foreach (var c in cmdwrapper.Children)
            {
                if (c is CommandText)
                {
                    //#FFACAAAA
                    CommandText cm = (CommandText)c;
                    cm.cmdLabel.Background = null;
                    if (selectLable.Name.Split('_')[1] == cm.cmdLabel.Name.Split('_')[1])
                    {
                        selectLable.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FFACAAAA"));
                        selected = true;
                    }
                }
            }
        }

        //删除命令数据行
        private void delBtn_Click(object sender, RoutedEventArgs e)
        {
            //行选择开关判断
            if (selected)
            {
                //遍历查询所选择的行，删除
                for (int i = 0; i < VisualTreeHelper.GetChildrenCount(cmdwrapper); i++)
                {
                    var child = VisualTreeHelper.GetChild(cmdwrapper, i);
                    if (child is CommandText)
                    {
                        CommandText cmd = (CommandText)child;
                        if (cmd.Name.Split('_')[1] == (numSelect + ""))
                        {
                            cmdwrapper.Children.Remove((CommandText)cmd);
                        }
                    }
                }

                //行选择记录器归零
                numSelect = 0;
                //将下次添加的行号记录为当前末行值+1
                num = VisualTreeHelper.GetChildrenCount(cmdwrapper);

                //更新编号及控件名
                for (int i = 0; i < num; i++)
                {
                    var child = VisualTreeHelper.GetChild(cmdwrapper, i);
                    if (child is CommandText)
                    {
                        CommandText cmd = (CommandText)child;
                        cmd.cmdBtn.Content = i;

                        cmd.Name = "cmdPanel_" + i;
                        cmd.cmdBtn.Name = "cmBtn_" + i;
                        cmd.cmdLabel.Name = "cmLabel_" + i;
                    }
                }

                selected = false;
            }

        }

        //清空命令数据
        private void cleBtn_Click(object sender, RoutedEventArgs e)
        {
            cmdClear();
        }

        //点击行按钮更新调节控件数据
        private void CmdBtn_Click(object sender, RoutedEventArgs e)
        {
            Button cmbtn = sender as Button;
            foreach (var c in cmdwrapper.Children)
            {
                if (c is CommandText)
                {
                    CommandText cm = (CommandText)c;
                    if (cmbtn.Name.Split('_')[1] == cm.cmdLabel.Name.Split('_')[1])
                    {
                        //MessageBox.Show(cm.cmdLabel.Content + "");
                        panelUpdate(cm.cmdLabel.Content+"");
                        pwmData = "";
                    }
                }
            }
        }

        //数据转化
        private void tranBtn_Click(object sender, RoutedEventArgs e)
        {
            foreach (var c in cmdwrapper.Children)
            {
                if (c is CommandText)
                {
                    CommandText cm = (CommandText)c;
                    panelUpdate(cm.cmdLabel.Content + "");
                }
            }

            if (pwmWrapper.Visibility.ToString().ToLower() == "hidden")
            {
                pwmWrapper.Visibility = Visibility.Visible;
            }
            else pwmWrapper.Visibility = Visibility.Hidden;

            pwmValue.Text = pwmData;
            //MessageBox.Show(pwmData);
            pwmData = "";
        }

        //复制数据
        private void copyBtn_Click(object sender, RoutedEventArgs e)
        {     
            Clipboard.SetDataObject(pwmValue.Text, true);
            pwmWrapper.Visibility = Visibility.Hidden;
        }
    }

}

