using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using SageEngine;
using SageEngine.Debug;
using SageEngine.Math;


public class GamePlayBehaviour : SageBehaviour
{
    void Init()
    {
        Console.WriteLine("SageBehaviour Init");
    }

    void Update()
    {
        Vector2D position = transform.position;
        transform.position = new Vector2D(0, 0);

        SageDebug.Print("[" + position.x + "," + position.y + "]");
        


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
