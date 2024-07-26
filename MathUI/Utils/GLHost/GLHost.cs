using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;
using MathGL;

namespace MathUI.Utils.GLHost
{
    public class GLHost : HwndHost
    {
        private IntPtr hwndHost;
        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            GLEngine eng = new();
            hwndHost = eng.InitializeWindow(hwndParent.Handle);
            if (hwndHost == IntPtr.Zero)
            {
                throw new InvalidOperationException("Failed to create OpenGL window.");
            }
            return new HandleRef(this, hwndHost);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            throw new NotImplementedException();
        }
    }
}
