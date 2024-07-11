﻿using DHUI.ViewModels;
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

namespace DHUI.Presenters
{
    /// <summary>
    /// Interaction logic for ToolPanel.xaml
    /// </summary>
    public partial class ToolPanel : UserControl
    {
        public ToolPanel()
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

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
        }
    }
}
