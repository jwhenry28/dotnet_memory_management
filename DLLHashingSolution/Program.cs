using System;
using System.Runtime.InteropServices;

namespace DLLSolution
{
    class DLLSolution
    {
        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLHashing\\x64\\Debug\\DLLHashing")]
        private static extern int createSecret();

        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLHashing\\x64\\Debug\\DLLHashing")]
        private static extern bool addCharToSecret(int id, char c);

        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLHashing\\x64\\Debug\\DLLHashing")]
        private static extern bool clearSecret(int id);

        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLHashing\\x64\\Debug\\DLLHashing")]
        private static extern bool obfuscateSecret(int id);

        [DllImport("C:\\Users\\IEUser\\source\\repos\\DLLHashing\\x64\\Debug\\DLLHashing")]
        private static extern bool compareSecret(int id, char[] input);


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

            Console.WriteLine("\n\nPress enter to obfuscate the secret.");
            Console.ReadLine();

            obfuscateSecret(secretHandle);

            Console.WriteLine("Press enter to compare the secrets.");
            Console.ReadLine();

            char[] input = new char[64];
            Console.Write("Enter input data: ");
            i = 0;
            do
            {
                key = Console.ReadKey(true);

                if (key.Key != ConsoleKey.Enter)
                {
                    input[i] = key.KeyChar;
                    i++;
                    Console.Write(key.KeyChar);
                }
            } while (key.Key != ConsoleKey.Enter);

            bool res = compareSecret(secretHandle, input);
            Console.WriteLine("\nComparison result: " + res);

            Console.WriteLine("Press enter to clear the secret.");
            Console.ReadLine();

            clearSecret(secretHandle);

            Console.WriteLine("The secret is cleared. Press enter to exit.");
            Console.ReadLine();
        }
    }
}