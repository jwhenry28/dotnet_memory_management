using System;
using System.Runtime.InteropServices;

namespace DLLSolution
{
    class DLLSolution
    {
        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLSimple\\x64\\Debug\\DLLSimple")]
        private static extern int createSecret();

        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLSimple\\x64\\Debug\\DLLSimple")]
        private static extern bool addCharToSecret(int id, char c);

        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLSimple\\x64\\Debug\\DLLSimple")]
        private static extern bool clearSecret(int id);


        static void Main(string[] args)
        {
            int secretHandle = createSecret();
            ConsoleKeyInfo key;

            Console.Write("Enter secret data: ");
            int i = 0;
            do
            {
                key = Console.ReadKey(true);

                if (key.Key != ConsoleKey.Enter)
                {
                    addCharToSecret(secretHandle, key.KeyChar);
                    i++;
                    Console.Write("*");
                }
            } while (key.Key != ConsoleKey.Enter);

            Console.WriteLine("\n\nPress enter to \"do\" the application work and clear the secret.");
            Console.ReadLine();

            clearSecret(secretHandle);

            Console.WriteLine("The secret is cleared. Press enter to exit.");
            Console.ReadLine();
        }
    }
}