using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;
using System.Windows;

namespace MathUI.Utils.GLHost
{
    public class MessageInterceptor
    {
        private readonly Window window;
        private HwndSource? hwndSource;
        public const int WM_MY_MESSAGE = 0x0401;

        public MessageInterceptor(Window window)
        {
            this.window = window;
            this.window.Loaded += Window_Loaded;
            this.window.Closed += Window_Closed;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            hwndSource = (HwndSource)PresentationSource.FromVisual(window);
            if (hwndSource != null)
            {
                hwndSource.AddHook(WndProc);
            }
        }

        private void Window_Closed(object? sender, EventArgs e)
        {
            if (hwndSource != null)
            {
                hwndSource.RemoveHook(WndProc);
                hwndSource = null;
            }
        }

        private IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            if (msg == WM_MY_MESSAGE)
            {
                handled = true;
            }
            return IntPtr.Zero;
        }
    }
}
