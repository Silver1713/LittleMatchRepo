using System;
using System.Runtime.CompilerServices;

namespace SageEngine
{
    public static class Input
    {   
        // Mono to call cpp
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static bool Get_Key(int keycode);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static bool Get_Key_Pressed(int keycode);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void Get_Mouse_Pos(out double mouse_x, out double mouse_y);
    }

    
}


public class Program {
    public static void Main(string[] args) {
        // This is a test harness for the Input class
        double x = 0, y =0;
        SageEngine.Input.Get_Mouse_Pos(out x, out y);
        SageEngine.Input.Get_Key(100);
        Console.WriteLine("Mouse position: " + x + ", " + y);

        
    }
}