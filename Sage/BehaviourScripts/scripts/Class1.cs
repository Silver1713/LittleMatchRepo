using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SageEngine;
namespace SageEngineRT
{
    public class ExampleClass
    {
        public static void Main(string[] args)
        {
            SageBehaviour sage_behaviour = new SageBehaviour();
            sage_behaviour.Init();
            sage_behaviour.Update();
            sage_behaviour.FixedUpdate();
            sage_behaviour.Exit();
            
        }
    }

}
