using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Interop;
using MathDX;
using MathGL;

namespace MathUI.Utils.EngineHost
{
    public class EngineHost(Type type) : HwndHost
    {
        public IntPtr hwndHost;
        private Type type = type;
        const int WM_MY_MESSAGE = 0x0401;

        public string GetName()
        {
            return type.Name;
        }

        protected override bool TranslateAcceleratorCore(ref MSG msg, ModifierKeys modifiers)
        {
            if (msg.message == WM_MY_MESSAGE)
            {
                return false;
            }

            return base.TranslateAcceleratorCore(ref msg, modifiers);
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            if (msg == WM_MY_MESSAGE)
            {
                handled = true;
            }

            return base.WndProc(hwnd, msg, wParam, lParam, ref handled);
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            switch (type)
            {
                case Type t when t == typeof(GLEngine):
                    {
                        hwndHost = GLEngine.Instance.InitializeWindow(hwndParent.Handle);
                        if (hwndHost == IntPtr.Zero)
                        {
                            throw new InvalidOperationException("Failed to create OpenGL window.");
                        }
                        break;
                    }
                case Type t when t == typeof(DXEngine):
                    {
                        hwndHost = DXEngine.Instance.InitializeWindow(hwndParent.Handle);
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
