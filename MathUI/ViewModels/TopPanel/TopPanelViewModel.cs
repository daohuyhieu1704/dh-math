using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace MathUI.ViewModels.TopPanel
{
    public class TopPanelViewModel : ViewModelBase
    {
        private string _selectedEngine;
        public string SelectedEngine
        {
            get => _selectedEngine;
            set
            {
                _selectedEngine = value;
                OnPropertyChanged(nameof(_selectedEngine));
            }
        }

        private ObservableCollection<string> _engineNames;
        public ObservableCollection<string> EngineNames
        {
            get => _engineNames;
            set
            {
                _engineNames = value;
                OnPropertyChanged(nameof(_engineNames));
            }
        }
        public TopPanelViewModel()
        {
            if (MainWindow.EngineHost.Count > 0)
            {
                EngineNames = new ObservableCollection<string>(MainWindow.EngineHost.Select(x => x.getName()));
                SelectedEngine = EngineNames[0];
            }
        }
    }
}
