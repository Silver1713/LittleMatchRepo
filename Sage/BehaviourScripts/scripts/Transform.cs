using System;
using System.Runtime.CompilerServices;
using SageEngine.Math;
namespace SageEngine
{
    public class Transform : Component
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getPosition(out Vector2D output);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setPosition(in Vector2D value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern Vector2D getScale();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setScale(Vector2D value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern float getRotation();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setRotation(float value);





        public Vector2D position
        {
            get
            {
                getPosition(out Vector2D output);
                return output;
            }
            set
            {
                
                Vector2D position = value;
                setPosition(in position);
            }
        }

        public Vector2D scale
        {
            get => getScale();
            set => setScale(value);
        }

        public float rotation
        {
            get => getRotation();
            set => setRotation(value);
        }

        public Transform()
        {
           // position = new Vector2D(0, 0);
        }




    }
}