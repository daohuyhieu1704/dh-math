using MathDX;
using MathGL;
using MathUI.Utils.EngineHost;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using MathCore;
using MathCore.Geom;
using System.Windows.Threading;
using System.Windows.Input;

namespace MathUI.ViewModels.MainWindow
{
    class MainWindowViewModel : ViewModelBase
    {
        private DispatcherTimer _timer;

        string _MouseX;
        public string MouseX
        {
            get => _MouseX;
            set
            {
                _MouseX = value;
                OnPropertyChanged("MouseX");
            }
        }

        string _MouseY;
        public string MouseY
        {
            get => _MouseY;
            set
            {
                _MouseY = value;
                OnPropertyChanged("MouseY");
            }
        }

        private string _engineName;
        public string EngineName
        {
            get => _engineName;
            set
            {
                _engineName = value;
                OnPropertyChanged("EngineName");
            }
        }

        public MainWindowViewModel()
        {
            EngineName = "OpenGL";
        }

        public void LoadEngine(MathUI.Presenters.MainWindow mainWindow)
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

        internal void RealtimeHandle()
        {
            List<Point3d> point3Ds = GLEngine.Instance.Points;
            if (point3Ds.Count == 0)
            {
                return;
            }
            MouseX = point3Ds.Last().X.ToString();
            MouseY = point3Ds.Last().Y.ToString();
        }

        internal void ZoomViewport(MouseWheelEventArgs e)
        {
            if (e.Delta > 0)
            {
                GLEngine.Instance.ZoomFactor -= 1.0f;
            }
            else
            {
                // Zoom out
                GLEngine.Instance.ZoomFactor += 1.0f;
            }

        }
    }
}
