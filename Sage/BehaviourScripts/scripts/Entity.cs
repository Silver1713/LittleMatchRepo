using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;


namespace SageEngine
{
    public class Entity
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern string getGameObject_Name();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern bool getGameObject_Active();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setGameObject_Active(bool value);


        public string name
        {
            get => getGameObject_Name(); 

        }

        public bool active
        {
            get => getGameObject_Active();
            set => setGameObject_Active(value);

        }
    }
}