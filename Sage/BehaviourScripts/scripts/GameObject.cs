using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System;
namespace SageEngine
{
    public class GameObject : Entity
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern T AddComponentInternal<T>() where T : Component;
        
        [MethodImpl(MethodImplOptions.InternalCall)] 
        private extern object GetComponentInternal(Type type);
        
        private Dictionary<Type, List<Component>> components;

        public GameObject()
        {
            components = new Dictionary<Type, List<Component>>();

        }


        public T GetComponent<T>() where T : Component
        {
            T comp = GetComponentInternal(typeof(T)) as T;

            return comp;

        }

        public void AddComponent<T>() where T : Component
        {
            T Component = AddComponentInternal<T>();

            Type type = typeof(T);

            if (components.TryGetValue(type, out List<Component> component))
            {
                component.Add(Component);
            }
            else
            {
                List<Component> newComponent = new List<Component>();
                newComponent.Add(Component);
                components.Add(type, newComponent);
            }

        }



    }

}