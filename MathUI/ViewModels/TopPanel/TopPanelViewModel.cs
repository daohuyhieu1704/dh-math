using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using MathCore.DatabaseServices;
using MathCore.Geom;

namespace MathUI.ViewModels.TopPanel
{
    public class TopPanelViewModel : ViewModelBase
    {
        public TopPanelViewModel()
        {
        }

        public void DrawLine()
        {
            Trans trans = new();
            trans.StartTransaction();
            Line line = new(new Point3d(0, 0, 0), new Point3d(100, 100, 0));
            trans.AddNewlyObject(line);
            trans.Commit();
        }
    }
}
