using System;
using SageEngine;
public class Program
{ 
    public static void Main(string[] args)
    {
        SageBehaviour sage_behaviour = new SageBehaviour();

        sage_behaviour.Init();
        sage_behaviour.Update();
        sage_behaviour.FixedUpdate();
        sage_behaviour.Exit();

        Console.WriteLine("Finished");

    }
}
