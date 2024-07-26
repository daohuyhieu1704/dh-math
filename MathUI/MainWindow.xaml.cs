﻿using MathDX;
using MathGL;
using MathUI.Utils.GLHost;
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
        public static List<GLHost> EngineHost = [];
        public MainWindow()
        {
            InitializeComponent();
            this.Loaded += MainWindow_Loaded;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            EngineHost.Add(new(typeof(GLEngine)));
            //EngineHost.Add(new(typeof(DXEngine)));
            hostContainer.Child = EngineHost[0];
        }
    }
}