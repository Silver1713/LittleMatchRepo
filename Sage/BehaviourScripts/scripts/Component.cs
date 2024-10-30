using System.Runtime.CompilerServices;
using SageEngine;

namespace SageEngine
{
    
    public class Component
    {
        public GameObject gameObject;
        public Transform transform;


        public T GetComponent<T>() where T : Component
        {
            return gameObject.GetComponent<T>();
        }

        public void AddComponent<T>() where T : Component
        {
            gameObject.AddComponent<T>();
        }


    }
}