using System;

public class Program
{
    // Function to calculate the minimum number of bubble swaps needed to sort the array
    public static int MinimumBubbleSwaps(int[] arr)
    {
        int n = arr.Length;
        int swapCount = 0;
        bool swapped;

        for (int i = 0; i < n - 1; i++)
        {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    // Swap arr[j] and arr[j+1]
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapCount++;
                    swapped = true;
                }
            }
            // If no two elements were swapped, the array is sorted
            if (!swapped)
                break;
        }
        return swapCount;
    }

    // Function to implement a simple Caesar Cipher
    public static string CaesarCipher(string text, int shift)
    {
        char[] buffer = text.ToCharArray();

        for (int i = 0; i < buffer.Length; i++)
        {
            char letter = buffer[i];

            if (char.IsLetter(letter))
            {
                char offset = char.IsUpper(letter) ? 'A' : 'a';
                letter = (char)(((letter + shift - offset) % 26) + offset);
            }

            buffer[i] = letter;
        }

        return new string(buffer);
    }

    // Main function to test both algorithms
    public static void Main(string[] args)
    {
        // Hardcoded test case for MinimumBubbleSwaps
        int[] arr = {1,8,2,7,3,6,4,10,5,11,6,12,0,100};  // Change this array to test different cases
        int swaps = MinimumBubbleSwaps(arr);
        Console.WriteLine($"Minimum bubble swaps to sort the array: {swaps}");

        // Hardcoded test case for CaesarCipher
        string text = "Hello World";   // Change this text to test different strings
        int shift = 3;                 // Change this shift value to test different shifts
        string cipherText = CaesarCipher(text, shift);
        Console.WriteLine($"Cipher text: {cipherText}");
    }
}
