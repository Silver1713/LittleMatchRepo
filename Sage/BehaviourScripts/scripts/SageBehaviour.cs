using System;
using System.Collections.Generic;


namespace SageEngine
{
    public class SageBehaviour
    {
        public void Init()
        {
            Console.WriteLine("SageBehaviour Init");
        }

        public void Update()
        {
            Console.WriteLine("C#: Hello World From CSHARP!!");
            int a = new int();
        }

        public void FixedUpdate()
        {
            Console.WriteLine("SageBehaviour Fixed Update.");
        } // Do we need this?

        public virtual void Exit()
        {
            Console.WriteLine("SageBehaviour Exit");
        }


        // Collision Messages
        // ...


        // Component Properties
        public bool enabled {get; set; }
        

    }
}