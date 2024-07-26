using MathDX;
using MathGL;
using MathUI.Utils.GLHost;
using MathUI.ViewModels.MainWindow;
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

namespace MathUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainWindowViewModel();
            this.Loaded += MainWindow_Loaded;
        }

        private void CommandAction(Action<MainWindowViewModel> callback)
        {
            try
            {
                if (DataContext is not MainWindowViewModel model)
                {
                    return;
                }

                callback(model);
            }
            catch (Exception)
            {

            }
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.LoadEngine(this));
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void TL_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TL());
        }

        private void TM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TM());
        }

        private void TR_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TR());
        }

        private void ML_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.ML());
        }

        private void TMM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.TMM());
        }

        private void BMM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BMM());
        }

        private void MR_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.MR());
        }

        private void BL_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BL());
        }

        private void BM_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BM());
        }

        private void BR_click(object sender, RoutedEventArgs e)
        {
            CommandAction((model) => model.BR());
        }
    }
}