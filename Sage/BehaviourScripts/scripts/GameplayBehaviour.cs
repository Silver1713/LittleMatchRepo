using System;
using System.Collections.Generic;
using SageEngine;
using SageEngine.Debug;



public class GamePlayBehaviour : SageBehaviour
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
}
