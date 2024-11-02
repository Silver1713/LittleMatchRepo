using System;
using System.Runtime.CompilerServices;

namespace SageEngine.Debug
{
    
    public static class SageDebug
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void PrintInternal(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void ErrorInternal(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void WarnInternal(string message);
        public static void Print(string message)
        {
            PrintInternal(message);
        }

        public static void Error(string message)
        {
           ErrorInternal(message);
        }

        public static void Warn(string message)
        {
            WarnInternal(message);
        }
    }
}