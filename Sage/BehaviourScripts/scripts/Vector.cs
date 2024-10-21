
using System;
using System.Runtime.InteropServices;

namespace SageEngine.Math
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Vector2D
    {
        public float x;
        public float y;

        //Vector2D()
        //{
        //    x = 0;
        //    y = 0;
        //}

        public float magnitude
        {
            get => Magnitude();
        }
        public float magnitudeSqr
        {
            get => MagnitudeSqr();
        }

        public Vector2D(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public static Vector2D operator +(Vector2D a, Vector2D b)
        {
            return new Vector2D(a.x + b.x, a.y + b.y);
        }

        public static Vector2D operator -(Vector2D a, Vector2D b)
        {
            return new Vector2D(a.x - b.x, a.y - b.y);
        }

        public static Vector2D operator *(Vector2D a, float b)
        {
            return new Vector2D(a.x * b, a.y * b);
        }

        public static Vector2D operator *(float a, Vector2D b)
        {
            return new Vector2D(a * b.x, a * b.y);
        }

        

        public static Vector2D operator /(Vector2D a, float b)
        {
            return new Vector2D(a.x / b, a.y / b);
        }

        public static float operator*(Vector2D a, Vector2D b)
        {
            return Dot(a, b);
        }
        public static float Dot(Vector2D a, Vector2D b)
        {
            return a.x * b.x + a.y * b.y;
        }

        public static float Cross(Vector2D a, Vector2D b)
        {
            return a.x * b.y - a.y * b.x;
        }

        public float Magnitude()
        {
            return (float)System.Math.Sqrt(x * x + y * y);
        }

        public float MagnitudeSqr()
        {
            return x * x + y * y;
        }

        public Vector2D Normalize()
        {
            return this / Magnitude();
        }
    }
}