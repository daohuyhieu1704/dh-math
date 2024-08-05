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

        public void DrawLine()
        {
            PointSelection pointSelection = new();
            Point3d pnt = pointSelection.getPoints(2);
            //Trans trans = new();
            //trans.StartTransaction();
            //Line line = new(new Point3d(0, 0, 0), new Point3d(100, 100, 0));
            //trans.AddNewlyObject(line);
            //trans.Commit();
            GLEngine.Instance.AddLine(new Point3d(0, 0, 0), new Point3d(1, 1, 0));
            GLEngine.Instance.AddLine(new Point3d(1, 1, 0), new Point3d(-1, -1, 0));
            GLEngine.Instance.AddLine(new Point3d(1, 1, 0), new Point3d(1, 1, 1));
        }
    }
}
