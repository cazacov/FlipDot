using System;
using System.Text;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class ConsoleRenderer : IRenderer
    {
        private readonly int width;
        private readonly int height;

        public ConsoleRenderer(int width, int height)
        {
            this.width = width;
            this.height = height;
        }

        

        public void Begin()
        {
            
        }

        public void Draw(int x, int y, SnakeObject obj, Direction inDir, Direction outDir)
        {
            Console.SetCursorPosition(x * 3, y);
            switch (obj)
            {
                case SnakeObject.Wall:
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.Write("░░░");
                    break;
                case SnakeObject.Apple:
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Write("(o)");
                    break;
                case SnakeObject.Empty:
                    Console.ForegroundColor = ConsoleColor.Gray;
                    Console.Write(" . ");
                    break;
                case SnakeObject.SnakeHead:
                case SnakeObject.SnakeBody:
                    if (obj == SnakeObject.SnakeHead)
                    {
                        Console.ForegroundColor = ConsoleColor.Yellow;
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.Green;
                    }
                    if (inDir == Direction.Down && outDir == Direction.Up ||
                        inDir == Direction.Up && outDir == Direction.Down ||
                        inDir == Direction.Up && outDir == Direction.None ||
                        inDir == Direction.None && outDir == Direction.Up ||
                        inDir == Direction.Down && outDir == Direction.None ||
                        inDir == Direction.None && outDir == Direction.Down)
                    {
                        Console.Write(" ║ ");
                    }
                    else if (inDir == Direction.Left && outDir == Direction.Right ||
                             inDir == Direction.Right && outDir == Direction.Left)
                    {
                        Console.Write("═══");
                    }
                    else if (inDir == Direction.Left && outDir == Direction.None ||
                             inDir == Direction.None && outDir == Direction.Left)
                    {
                        Console.Write("══ ");
                    }
                    else if (
                        inDir == Direction.Right && outDir == Direction.None ||
                        inDir == Direction.None && outDir == Direction.Right)
                    {
                        Console.Write(" ══");
                    }
                    else if (inDir == Direction.Down && outDir == Direction.Right ||
                             inDir == Direction.Right && outDir == Direction.Down)
                    {
                        Console.Write(" ╔═");
                    }
                    else if (inDir == Direction.Down && outDir == Direction.Left ||
                             inDir == Direction.Left && outDir == Direction.Down)
                    {
                        Console.Write("═╗ ");
                    }
                    else if (inDir == Direction.Up && outDir == Direction.Right ||
                             inDir == Direction.Right && outDir == Direction.Up)
                    {
                        Console.Write(" ╚═");
                    }
                    else if (inDir == Direction.Up && outDir == Direction.Left ||
                             inDir == Direction.Left && outDir == Direction.Up)
                    {
                        Console.Write("═╝ ");
                    }
                    else
                    {
                        Console.Write(" ╬ ");
                    }
                    break;
                case SnakeObject.Hit:
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Write("XXX");
                    break;
                case SnakeObject.Path:
                    Console.ForegroundColor = ConsoleColor.Blue;
                    if (inDir == Direction.Down && outDir == Direction.Up ||
                        inDir == Direction.Up && outDir == Direction.Down ||
                        inDir == Direction.Up && outDir == Direction.None ||
                        inDir == Direction.None && outDir == Direction.Up ||
                        inDir == Direction.Down && outDir == Direction.None ||
                        inDir == Direction.None && outDir == Direction.Down)
                    {
                        Console.Write(" │ ");
                    }
                    else if (inDir == Direction.Left && outDir == Direction.Right ||
                             inDir == Direction.Right && outDir == Direction.Left)
                    {
                        Console.Write("───");
                    }
                    else if (inDir == Direction.Left && outDir == Direction.None ||
                             inDir == Direction.None && outDir == Direction.Left)
                    {
                        Console.Write("── ");
                    }
                    else if (
                        inDir == Direction.Right && outDir == Direction.None ||
                        inDir == Direction.None && outDir == Direction.Right)
                    {
                        Console.Write(" ──");
                    }
                    else if (inDir == Direction.Down && outDir == Direction.Right ||
                             inDir == Direction.Right && outDir == Direction.Down)
                    {
                        Console.Write(" ┌─");
                    }
                    else if (inDir == Direction.Down && outDir == Direction.Left ||
                             inDir == Direction.Left && outDir == Direction.Down)
                    {
                        Console.Write("─┐ ");
                    }
                    else if (inDir == Direction.Up && outDir == Direction.Right ||
                             inDir == Direction.Right && outDir == Direction.Up)
                    {
                        Console.Write(" └─");
                    }
                    else if (inDir == Direction.Up && outDir == Direction.Left ||
                             inDir == Direction.Left && outDir == Direction.Up)
                    {
                        Console.Write("─┘ ");
                    }
                    else
                    {
                        Console.Write("─┼─");
                    }
                    break;
            }
        }

        public async Task End()
        {
            
        }

        public int GetWidth()
        {
            return width;
        }

        public int GetHeight()
        {
            return height;
        }

        public void Dispose()
        {
            Console.ResetColor();
        }

        public async Task GameOver(int x, int y)
        {
            Draw(x, y, SnakeObject.Hit, Direction.None, Direction.None);
            Console.SetCursorPosition(0, height);
            Console.WriteLine("GAME OVER");
        }

        public async Task GameWon()
        {
            Console.SetCursorPosition(0, height);
            Console.WriteLine("YOU ARE WINNER!");
        }

        public async Task ShowScore(int score)
        {
            Console.SetCursorPosition(width * 3 + 3, height/2);
            Console.Write($"Score {score}");
        }

        public async Task Clear()
        {
            Console.Clear();
            Console.OutputEncoding = Encoding.UTF8; // System.Text.Encoding.GetEncoding(28591);
        }
    }
}
