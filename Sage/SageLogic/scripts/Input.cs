using System;
using System.Runtime.CompilerServices;

namespace SageEngine
{
    public static class Input
    {   
        // Mono to call cpp
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Get_Key();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Get_Key_Pressed();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Get_Mouse_Pos(out float mouse_x, out float mouse_y);
    }
}