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
        private extern T GetComponentInternal<T>() where T : Component;
        
        private Dictionary<Type, List<Component>> components;

        public GameObject()
        {
            components = new Dictionary<Type, List<Component>>();

        }


        public T GetComponent<T>() where T : Component
        {
            Type type = typeof(T);

            // Internal Check(C++) to see if Entity has that component if not throw err
            // Check if type is derived from SageBehaviour
            bool isLogicalComponent = typeof(SageBehaviour).IsAssignableFrom(type);

            if (isLogicalComponent)
            {
                if (components.TryGetValue(typeof(SageBehaviour), out List<Component> logic_components))
                {
                    string name = type.FullName;

                    foreach (Component s in logic_components)
                    {
                        Type logic_type = s.GetType();

                        if (logic_type.FullName.Equals(name))
                        {
                            return s as T;
                        }
                    }
                } 
            }
            else
            {
                if (components.TryGetValue(typeof(T), out List<Component> component))
                {
                    return component[0] as T;
                }
            }


            return null;

        }
        public extern T AddComponent<T>() where T : Component;



    }

}