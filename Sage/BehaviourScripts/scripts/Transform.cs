using System.Runtime.CompilerServices;
using SageEngine.Math;
namespace SageEngine
{
    public class Transform : Component
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern Vector2D getPosition();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setPosition(Vector2D value);
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
            get => getPosition();
            set => setPosition(value);
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
            position = new Vector2D(0, 0);
            scale = new Vector2D(1, 1);
            rotation = 0;
        }




    }
}