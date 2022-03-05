using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SnakeRunnerApp
{
    internal class Field : IDisposable
    {
        private int width;
        private int height;
        private List<Pos> path = new List<Pos>();

        public Field(int width, int height)
        {
            this.width = width;
            this.height = height;
        }

        public void Show(List<Pos> snake, Pos apple)
        {
            Console.Clear();
            Console.OutputEncoding = Encoding.UTF8; // System.Text.Encoding.GetEncoding(28591);
            for (var i = 0; i < width + 2; i++)
            {
                Console.SetCursorPosition(i * 3, 0);
                ShowWall();
                Console.SetCursorPosition(i * 3, height +1);
                ShowWall();
            }
            for (var y = 0; y < height; y++)
            {
                Console.SetCursorPosition(0, y + 1);
                ShowWall();
                for (var x = 0; x < width; x++)
                {
                    GoTo(x, y);
                    if (snake.Contains(new Pos(x, y)))
                    {
                        ShowSnake();
                    }
                    else if (path.Contains(new Pos(x,y)))
                    {
                        ShowPath();
                    }
                    else if (apple.X == x && apple.Y == y)
                    {
                        GoTo(x, y);
                        ShowApple();
                    }
                    else
                    {
                        ShowEmpty();
                    }
                }
                Console.SetCursorPosition((width + 1) * 3, y + 1);
                ShowWall();
            }
        }

        private void GoTo(int x, int y)
        {
            Console.SetCursorPosition(x * 3 + 3, y + 1);
        }

        private void ShowEmpty()
        {
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" . ");
        }

        private void ShowApple()
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("(o)");
        }

        private void ShowSnake()
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write("▓▓▓");
        }

        private void ShowWall()
        {
            Console.ForegroundColor = ConsoleColor.White;
            Console.Write("░░░");
        }

        private void ShowHit()
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("XXX");
        }

        private void ShowPath()
        {
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.Write("─┼─");
        }

        public void Dispose()
        {
            Console.ResetColor();
        }

        public void ShowGameOver(List<Pos> snake)
        {
            var head = snake.Last();
            Console.SetCursorPosition((head.X + 1) * 3, head.Y + 1);
            ShowHit();
        }


        public void ShowGameWon(List<Pos> snake)
        {
            throw new NotImplementedException();
        }

        public void SetPath(List<Pos> newPath)
        {
            this.path.Clear();
            if (newPath != null)
            {
                this.path.AddRange(newPath.Take(newPath.Count - 1));
            }
        }
    }
}
