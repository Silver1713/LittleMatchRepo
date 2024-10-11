
	using System;

class Program
{
	public static int number =1;
    static void Main(string[] args)
    {
       for (int i =1;i < 1000;i++){
		   number += i;
		   Console.WriteLine($"Number: {number}");
		}
    }
}
