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
using Controler_1._0;

namespace Controler_Panel
{
    /// <summary>
    /// ControlPanel.xaml 的交互逻辑
    /// </summary>
    public partial class ControlPanel : UserControl
    {
        public ControlPanel(double p)
        {
            InitializeComponent();
            this.Name = "panel_" + p;
            this.label.Content = "P" + p;
            this.text.Name = "text_" + p;
            this.slider.Name = "slider_" + p;
            this.label.Name = "label_" + p;
        }

        private void slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            text.Text = this.slider.Value + "";        
        }

        private void text_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                double pwmData = Convert.ToInt32(text.Text);
                slider.Value = pwmData;
            }
        }
    }

}
