using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using MathCore.Geom;
using MathGL;

namespace MathUI.ViewModels.TopPanel
{
    public class TopPanelViewModel : ViewModelBase
    {
        public TopPanelViewModel()
        {
        }

        internal async void DrawLine()
        {
            PointSelection pointSelection = new();
            List<Point3d> pnt = await pointSelection.getPoints(2);
            Line line = new(pnt[0], pnt[1]);
            line.Draw();
        }

        internal async void DrawCircle()
        {
            PointSelection pointSelection = new();
            List<Point3d> pnt = await pointSelection.getPoints(1);
            Circle circle = new(pnt[0], 6);
            circle.Draw();
        }

        internal async void DrawSquare()
        {
            PointSelection pointSelection = new();
            List<Point3d> pnt = await pointSelection.getPoints(2);
            Square square = new(pnt[0].ConvertTo2d(), pnt[1].ConvertTo2d(), 10);
            square.Draw();
        }
    }
}
