using System;

namespace CharacterArraySolution
{
    class CharacterArraySolution
    {
        static void Main(string[] args)
        {
            char[] applicationSecret = new char[64];
            ConsoleKeyInfo key;

            Console.Write("Enter secret data: ");
            int i = 0;
            do
            {
                key = Console.ReadKey(true);

                if (((int)key.Key) != 10)
                {
                    applicationSecret[i] = key.KeyChar;
                    i++;
                    Console.Write("*");
                }
            } while (key.Key != ConsoleKey.Enter);

            Console.WriteLine("\n\nPress enter to \"do\" the application work and clear the secret.");
            Console.ReadLine();

            for (int j = 0; j < applicationSecret.Length; j++)
            {
                applicationSecret[j] = '\0';
            }

            Console.WriteLine("The secret is cleared. Press enter to exit.");
            Console.ReadLine();
        }
    }
}