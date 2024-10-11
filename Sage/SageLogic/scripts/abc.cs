using System;

public class Program
{
    public static int number =1;
    public static void Main(string[] args)
    {
         for (int i =1;i < 10000;i++){
            number += i;
            Console.WriteLine($"Number: {number}");
         }
         Console.WriteLine("Execution Ended");
    }
}

