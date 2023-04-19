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

namespace Command_Text
{
    /// <summary>
    /// CommandText.xaml 的交互逻辑
    /// </summary>
    public partial class CommandText : UserControl
    {
        public CommandText(double n, string data)
        {
            InitializeComponent();
            this.Name = "cmdPanel_" + n;
            this.cmdBtn.Name = "cmdBtn_" + n;
            this.cmdLabel.Name = "cmdLabel_" + n;

            this.cmdBtn.Content = n;
            this.cmdLabel.Content = data;
        }
    }
}
