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
        private extern void setGameObject_Name(string value);



        protected string name
        {
            get => getGameObject_Name(); 
            set => setGameObject_Name(value);

        }
    }
}