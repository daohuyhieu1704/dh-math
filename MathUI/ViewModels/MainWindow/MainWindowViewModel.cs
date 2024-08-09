using MathDX;
using MathGL;
using MathUI.Utils.EngineHost;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using MathCore;
using MathCore.Geom;
using System.Windows.Threading;
using System.Windows.Input;
using MathUI.Utils;

namespace MathUI.ViewModels.MainWindow
{
    public class MainWindowViewModel : ViewModelBase
    {
        private DispatcherTimer _timer;
        public Presenters.MainWindow context;
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

        private string _historyWindow;
        public string HistoryWindow
        {
            get => _historyWindow;
            set
            {
                _historyWindow = value;
                OnPropertyChanged("HistoryWindow");
            }
        }

        private string commandWindow;

        public string CommandWindow 
        { 
            get => commandWindow;
            set
            {
                commandWindow = value;
                OnPropertyChanged("CommandWindow");
            }
        }

        private TextBox _InputCommandWindow;
        public TextBox InputCommandWindow
        {
            get => _InputCommandWindow;
            set
            {
                _InputCommandWindow = value;
                OnPropertyChanged("InputCommandWindow");
            }
        }

        public MainWindowViewModel(Presenters.MainWindow mainWindow)
        {
            EngineName = "OpenGL";
            HistoryWindow = "";
            context = mainWindow;
        }

        public void LoadEngine(MathUI.Presenters.MainWindow mainWindow)
        {
            var grid = mainWindow.FindName("EngineContainer");
            EngineName = "OpenGL";
            if (grid is Grid engineContainer)
            {
                engineContainer.Children.Add(new EngineHost(typeof(GLEngine)));
                // engineContainer.Children.Add(new EngineHost(typeof(DXEngine)));

                HistoryWindow += "Engine started\n";
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

        public void RealtimeHandle()
        {
            List<Point3d> point3Ds = GLEngine.Instance.Points;
            if (point3Ds.Count == 0)
            {
                return;
            }
            MouseX = point3Ds.Last().X.ToString();
            MouseY = point3Ds.Last().Y.ToString();
        }

        public void ZoomViewport(MouseWheelEventArgs e)
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

        public async void DrawLine()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick 2 points:" + "\n";
            List<Point3d> pnt1 = await pointSelection.getPoints(1);
            LineJig lineJig = new(pnt1[0]);
            lineJig.Commit();
            List<Point3d> pnt2 = await pointSelection.getPoints(1);
            Line line = new(pnt1[0], pnt2[0]);
            line.Draw();
            HistoryWindow += line.GetCommand() + "\n";
        }

        public async void DrawCircle()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick 2 points:" + "\n";
            List<Point3d> pnt = await pointSelection.getPoints(2);
            Circle circle = new(pnt[0], pnt[0].DistanceTo(pnt[1]));
            circle.Draw();
            HistoryWindow += circle.GetCommand() + "\n";
        }
        internal async void DrawRect()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick 2 points:" + "\n";
            List<Point3d> pnt = await pointSelection.getPoints(2);
            Line line1 = new(new Point3d(pnt[0].X, pnt[1].Y, 0), pnt[1]);
            line1.Draw();

            Line line2 = new(pnt[1], new Point3d(pnt[1].X, pnt[0].Y, 0));
            line2.Draw();

            Line line3 = new(new Point3d(pnt[1].X, pnt[0].Y, 0), pnt[0]);
            line3.Draw();

            Line line4 = new(pnt[0], new Point3d(pnt[0].X, pnt[1].Y, 0));
            line4.Draw();

            HistoryWindow += line1.GetCommand() + "\n";
            HistoryWindow += line2.GetCommand() + "\n";
            HistoryWindow += line3.GetCommand() + "\n";
            HistoryWindow += line4.GetCommand() + "\n";
        }

        public async void DrawSquare()
        {
            PointSelection pointSelection = new();
            HistoryWindow += "Pick 2 points:" + "\n";
            List<Point3d> pnt = await pointSelection.getPoints(2);
            TextInput textInp = new(this);
            string text = await textInp.GetText();
            if (double.TryParse(text, out var z))
            {
                Square square = new(pnt[0].ConvertTo2d(), pnt[1].ConvertTo2d(), z);
                square.Draw();
                HistoryWindow += square.GetCommand() + "\n";
            }
        }

        internal void AppendCommand()
        {
            GLEngine.Instance.AppendCommand(CommandWindow);
            CommandWindow = "";
            HistoryWindow += CommandWindow + "\n";
        }

        internal void Undo()
        {
            throw new NotImplementedException();
        }

        internal void Redo()
        {
            throw new NotImplementedException();
        }

        internal void NewFile()
        {
            throw new NotImplementedException();
        }

        internal void OpenFile()
        {
            throw new NotImplementedException();
        }

        internal void SaveFile()
        {
            throw new NotImplementedException();
        }
    }
}
