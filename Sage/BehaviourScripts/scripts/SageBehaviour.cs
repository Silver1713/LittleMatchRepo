using System;
using System.Collections.Generic;
using SageEngine.Debug;


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
            SageDebug.Print("SageBehaviour Update.");

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