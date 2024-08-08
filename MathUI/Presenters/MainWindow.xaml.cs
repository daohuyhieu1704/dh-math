using MathDX;
using MathGL;
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
using System.Windows.Threading;

namespace MathUI.Presenters
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
            //StartBackgroundCheck();
        }

        //private async void StartBackgroundCheck()
        private void StartBackgroundCheck()
        {
            UpdateUI();
            //await Task.Run(async () =>
            //{
            //    while (true)
            //    {
            //        bool hasUpdates = CheckForUpdatesFromCppCli();

            //        if (hasUpdates)
            //        {
            //            await Dispatcher.InvokeAsync(() => UpdateUI());
            //        }

            //        await Task.Delay(500);
            //    }
            //});
        }

        private void UpdateUI()
        {
            CommandAction((model) => model.RealtimeHandle());
        }

        private bool CheckForUpdatesFromCppCli()
        {
            if (GLEngine.Instance == null)
            {
                return false;
            }
            return true;
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
            if (e.MiddleButton == MouseButtonState.Pressed)
            {
            }
        }

        private void Window_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            CommandAction((model) => model.ZoomViewport(e));
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

        private void CommandTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                string command = CommandWindow.Text;
                CommandAction((model) => model.AppendCommand(command));
                CommandWindow.Clear();
            }
        }
    }
}