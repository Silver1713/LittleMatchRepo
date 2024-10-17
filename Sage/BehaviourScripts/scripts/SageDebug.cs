using System;

namespace SageEngine.Debug
{
    public static class SageDebug
    {
        public static void Print(string message)
        {
            Console.WriteLine($"[INFO] {message}");
        }

        public static void Error(string message)
        {
            Console.Error.WriteLine($"[ERROR] {message}");
        }

        public static void Warn(string message)
        {
            Console.WriteLine($"[WARN] {message}");
        }
    }
}