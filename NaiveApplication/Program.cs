using System;

namespace NaiveApplication
{
    class NaiveApplication
    {
        static void Main(string[] args)
        {
            string applicationSecret = "";
            ConsoleKeyInfo key;

            Console.Write("Enter secret data: ");
            do
            {
                key = Console.ReadKey(true);

                if (((int)key.Key) != 10)
                {
                    applicationSecret += key.KeyChar;
                    Console.Write("*");
                }
            } while (key.Key != ConsoleKey.Enter);

            Console.WriteLine("\n\nPress enter to \"do\" the application work.");
            Console.ReadLine();
        }
    }
}