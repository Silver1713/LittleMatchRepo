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
    }
}