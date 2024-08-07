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

        public async void DrawLine()
        {
            PointSelection pointSelection = new();
            List<Point3d> pnt = await pointSelection.getPoints(2);
            Line line = new(pnt[0], pnt[1]);
            line.Draw();
        }
    }
}
