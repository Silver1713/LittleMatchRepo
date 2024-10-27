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
        RigidBody t = gameObject.GetComponent<RigidBody>();

        if (t == null)
        {
            SageDebug.Print("Rigidbody is null");
        }
    }

    void Update()
    {
        Vector2D position = transform.position;
        

        //SageDebug.Print("[" + position.x + "," + position.y + "]");
        


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
