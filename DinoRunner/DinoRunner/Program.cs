using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace DinoRunner
{
    internal class Program
    {
        static Random random = new Random();

        static async Task Main(string[] args)
        {

            var url = "http://192.168.178.61/";

            Console.WriteLine("Dino run. Press Esc to exit");
            var canvas = new Canvas();

            var state = State.Step1;
            var jump = 0;

            var stones = new List<Pos>();
            var cacti = new List<Cactus>();

            canvas.Cls();
            canvas.DrawBaseLine();
            await canvas.Display(url);
            await Task.Delay(3000);

            canvas.PutDino(60, 10, State.Step1);
            await canvas.Display(url);
            await Task.Delay(300);

            do
            {
                canvas.Cls();
                canvas.DrawBaseLine();
                canvas.DrawStones(stones);
                canvas.DrawCacti(cacti);

                var x = 60;
                var y = 10;

                var mustJump = state != State.Jump && cacti.Any(c => c.X == x + 14);
                if (mustJump)
                {
                    state = State.Jump;
                    jump = 26;
                }

                switch (state)
                {
                    case State.Step1:
                        state = State.Step2;
                        break;
                    case State.Step2:
                        state = State.Step1;
                        break;
                    case State.Jump:
                        jump--;
                        if (jump == 0)
                        {
                            state = State.Step1;
                            y = 10;
                        }
                        else
                        {
                            if (jump < 11)
                            {
                                y = 10 - jump;
                            }
                            else if (jump < 15)
                            {
                                y = 0;
                            }
                            else
                            {
                                y = jump - 15;
                            }
                        }
                        break;
                }

                Console.WriteLine($"{x},{y}\t{state}");
                canvas.PutDino(x, y, state);

                await canvas.Display(url);

                UpdateStones(stones, canvas);
                UpdateCacti(cacti, canvas);


                await Task.Delay(100);
            } while (!Console.KeyAvailable  || Console.ReadKey(true).Key != ConsoleKey.Escape);
        }

        private static void UpdateCacti(List<Cactus> cacti, Canvas canvas)
        {
            foreach (var cactus in cacti)
            {
                cactus.X = cactus.X - 1;
            }
            cacti.RemoveAll(cactus => cactus.X < -3);

            if (cacti.Any())
            {
                var maxX = cacti.Max(c => c.X);
                if (maxX + 27 >= Canvas.Width)
                {
                    return;
                }
            }

            if (random.Next(20) == 0)
            {
                var type = random.Next(10) < 5 ? CactusType.Type1 : CactusType.Type2;
                cacti.Add(new Cactus(Canvas.Width + 1, Canvas.Height - 9, type));
            }
        }

        private static void UpdateStones(List<Pos> stones, Canvas canvas)
        {
            foreach (var stone in stones)
            {
                stone.X = stone.X - 1;
            }
            stones.RemoveAll(stone => stone.X < 0);

            if (random.Next(10) == 0)
            {
                var y = random.Next(10) < 5 ? Canvas.Height - 1 : Canvas.Height - 2;
                stones.Add(new Pos(Canvas.Width - 1, y));
            }
        }
    }
}