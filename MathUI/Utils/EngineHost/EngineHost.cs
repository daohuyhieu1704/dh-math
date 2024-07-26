using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;
using MathDX;
using MathGL;

namespace MathUI.Utils.EngineHost
{
    public class EngineHost(Type type) : HwndHost
    {
        private IntPtr hwndHost;
        private Type type = type;

        public string GetName()
        {
            return type.Name;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            switch (type)
            {
                case Type t when t == typeof(GLEngine):
                    {
                        GLEngine eng = GLEngine.Instance;
                        hwndHost = eng.InitializeWindow(hwndParent.Handle);
                        if (hwndHost == IntPtr.Zero)
                        {
                            throw new InvalidOperationException("Failed to create OpenGL window.");
                        }
                        break;
                    }
                case Type t when t == typeof(DXEngine):
                    {
                        DXEngine eng = DXEngine.Instance;
                        hwndHost = eng.InitializeWindow(hwndParent.Handle);
                        if (hwndHost == IntPtr.Zero)
                        {
                            throw new InvalidOperationException("Failed to create DirectX window.");
                        }
                        break;
                    }
            }
            return new HandleRef(this, hwndHost);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
        }
    }
}
