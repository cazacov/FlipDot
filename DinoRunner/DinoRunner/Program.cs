using System;
using System.Threading;
using System.Threading.Tasks;

namespace DinoRunner
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            Console.WriteLine("Dino run. Press Esc to exit");
            var canvas = new Canvas();

            State state = State.Step1;

            do
            {
                canvas.Cls();
                canvas.DrawBaseLine();

                var x = 60;
                var y = 10;

                Console.WriteLine($"{x},{y}\t{state}");
                canvas.PutDino(60, 10, state);

                switch (state)
                {
                    case State.Step1:
                        state = State.Step2;
                        break;
                    case State.Step2:
                        state = State.Step1;
                        break;
                }

                canvas.Display("http:://localhost:5000/");
                await Task.Delay(100);
            } while (!Console.KeyAvailable  || Console.ReadKey(true).Key != ConsoleKey.Escape);
        }
    }
}