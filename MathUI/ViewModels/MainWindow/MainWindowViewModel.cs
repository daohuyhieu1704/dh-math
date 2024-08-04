using MathDX;
using MathGL;
using MathUI.Utils.EngineHost;
using MathUI.Utils.GLHost;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using MathCore;

namespace MathUI.ViewModels.MainWindow
{
    class MainWindowViewModel : ViewModelBase
    {
        int _MouseX;
        public int MouseX
        {
            get => _MouseX;
            set
            {
                _MouseX = value;
                OnPropertyChanged(nameof(_MouseX));
            }
        }

        int _MouseY;
        public int MouseY
        {
            get => _MouseY;
            set
            {
                _MouseY = value;
                OnPropertyChanged(nameof(_MouseY));
            }
        }

        private string _engineName;
        public string EngineName
        {
            get => _engineName;
            set
            {
                _engineName = value;
                OnPropertyChanged(nameof(_engineName));
            }
        }

        public MainWindowViewModel()
        {
            EngineName = "OpenGL";
        }

        public void LoadEngine(MathUI.MainWindow mainWindow)
        {
            var grid = mainWindow.FindName("EngineContainer");
            EngineName = "OpenGL";
            if (grid is Grid engineContainer)
            {
                engineContainer.Children.Add(new EngineHost(typeof(GLEngine)));
                // engineContainer.Children.Add(new EngineHost(typeof(DXEngine)));
            }
        }

        public void TL()
        {
            GLEngine.Instance.TLViewport();
        }

        public void TM()
        {
            GLEngine.Instance.TMViewport();
        }

        public void TR()
        {
            GLEngine.Instance.TRViewport();
        }

        public void ML()
        {
            GLEngine.Instance.MLViewport();
        }

        public void TMM()
        {
            GLEngine.Instance.TMMViewport();
        }

        public void BMM()
        {
            GLEngine.Instance.BMMViewport();
        }

        public void MR()
        {
            GLEngine.Instance.MRViewport();
        }

        public void BL()
        {
            GLEngine.Instance.BLViewport();
        }

        public void BM()
        {
            GLEngine.Instance.BMViewport();
        }

        public void BR()
        {
            GLEngine.Instance.BRViewport();
        }
    }
}
