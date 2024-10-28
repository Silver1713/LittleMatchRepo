using System;
using System.Runtime.CompilerServices;
using SageEngine.Math;
namespace SageEngine {
   public  class RigidBody : Component
    {
        private bool is_gravity_on;

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Get_Gravity_Internal(out Vector2D output);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Set_Gravity_Internal(in Vector2D value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Get_Velocity_Internal(out Vector2D output);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Set_Velocity_Internal(in Vector2D value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Set_Enable_Gravity(bool value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Add_Force_Internal(in Vector2D force, ForceMode mode);




        public Vector2D gravity
        {
            get
            {
                Get_Gravity_Internal(out Vector2D gravity);
                return gravity;
            }
            set
            {
                Vector2D gravity = value;
                Set_Gravity_Internal(in gravity);
            }

        }

        public Vector2D initial_velocity;
        public Vector2D velocity
        {
            get
            {
                Get_Velocity_Internal(out Vector2D velocity);
                return velocity;
            }
            set
            {
                Vector2D velocity = value;
                Set_Velocity_Internal(in velocity);
            }
        }

        public enum ForceMode : int
        {
            Force,
            Impulse,
            VelocityChange,
            Acceleration
        }


        public bool Enable_Gravity
        {
            get
            {
                return is_gravity_on;
            }
            set
            {
                is_gravity_on = value;
                Set_Enable_Gravity(value);
            }
        }


        public void AddForce(Vector2D force, ForceMode mode)
        {
            Add_Force_Internal(in force, mode);
        }

        public RigidBody()
        {
            is_gravity_on = true;
            gravity = new Vector2D(0, -9.8f);
            initial_velocity = new Vector2D(0, 0);
            velocity = initial_velocity;
        }
    }
}