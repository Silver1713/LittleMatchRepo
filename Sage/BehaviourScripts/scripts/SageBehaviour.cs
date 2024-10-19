using System;
using System.Collections.Generic;
using SageEngine.Debug;


namespace SageEngine
{
    public class SageBehaviour
    {
        void Init()
        {
            Console.WriteLine("SageBehaviour Init");
        }

        void Update()
        {
            SageDebug.Print("SageBehaviour Update.");

        }

        void FixedUpdate()
        {
            Console.WriteLine("SageBehaviour Fixed Update.");
        } // Do we need this?

        void Exit()
        {
            Console.WriteLine("SageBehaviour Exit");
        }


        // Collision Messages
        // ...


        // Component Properties
        public bool enabled {get; set; }
        

    }
}