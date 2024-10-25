using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using SageEngine;
using SageEngine.Debug;
using SageEngine.Math;


public class PlayerBehaviour : SageBehaviour
{
    void Init()
    {
        Console.WriteLine("SageBehaviour Init");
    }

    void Update()
    {
        string g_name = gameObject.name;
        SageDebug.Print(g_name);
        


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
