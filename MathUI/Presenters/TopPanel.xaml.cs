using MathUI.ViewModels.MainWindow;
using MathUI.ViewModels.TopPanel;
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

namespace MathUI.Presenters
{
    /// <summary>
    /// Interaction logic for TopPanel.xaml
    /// </summary>
    public partial class TopPanel : UserControl
    {
        public TopPanel()
        {
            InitializeComponent();
            DataContext = new TopPanelViewModel();
        }
        private void CommandAction(Action<TopPanelViewModel> callback)
        {
            try
            {
                if (DataContext is not TopPanelViewModel model)
                {
                    return;
                }

                callback(model);
            }
            catch (Exception)
            {

            }
        }

        private void DrawLine_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.DrawLine());
        }

        private void DrawCircle_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.DrawCircle());
        }

        private void DrawSquare_Click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.DrawSquare());
        }
    }
}
