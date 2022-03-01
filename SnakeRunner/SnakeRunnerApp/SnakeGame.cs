using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class SnakeGame : BaseService
    {
        private const int width = 20;
        private const int height = 17;
        private readonly Random random = new Random();

        public List<Pos> snake;
        public Pos apple;
        public Direction snakeDirection;

        private Field field = new Field(width, height);

        public SnakeGame()
        {
            this.snake = new List<Pos>()
            {
                new Pos(random.Next(width),random.Next(height))
            };
            this.apple = PlaceApple(snake);
            snakeDirection = snake[0].Y > height / 2 ? Direction.Up : Direction.Down;
        }

        private Pos PlaceApple(List<Pos> snake)
        {
            Pos result;

            do
            {
                result = new Pos(random.Next(width),random.Next(height));
            } while (snake.Contains(result));
            return result;
        }

        protected override async Task DoWorkAsync(CancellationToken cancellationToken)
        {
            bool isLost = false;
            while (!cancellationToken.IsCancellationRequested)
            {
                try
                {
                    var nextDir = ChooseDirection();
                    MakeMove(nextDir);
                    if (GameIsLost())
                    {
                        isLost = true;
                        break;
                    }
                    if (GameIsWon())
                    {
                        break;
                    }
                    field.Show(snake, apple);
                    await Task.Delay(1000, cancellationToken);
                }
                catch (OperationCanceledException)
                {
                    //
                }
            }

            field.Show(snake, apple);
            if (isLost)
            {
                field.ShowGameOver(snake);
            }
            else
            {
                field.ShowGameWon(snake);
            }

            while (!cancellationToken.IsCancellationRequested)
            {
                await Task.Delay(100, cancellationToken);
            }
        }

        private bool GameIsWon()
        {
            return this.snake.Count == height * width;
        }

        private bool GameIsLost()
        {
            var head = snake.Last();
            // Snake left the field?
            if (!InField(head))
            {
                return true;
            }

            // Snake head intersects with the body?
            var headIndex = this.snake.IndexOf(head);
            return headIndex >= 0 && headIndex < snake.Count - 1;
        }

        private bool InField(Pos pos)
        {
            return 
                pos.X is >= 0 and < width 
                && pos.Y is >= 0 and < height;
        }

        private void MakeMove(Direction nextDir)
        {
            var head = snake.Last();
            var nextPos = head.GoTo(nextDir);
            snake.Add(nextPos);
            if (nextPos == apple)
            {
                if (snake.Count == width * height)
                {
                    // Game won, do nothing
                }
                else
                {
                    apple = PlaceApple(snake);
                }
            }
            else
            {
                snake.RemoveAt(0);
            }
        }

        private Direction ChooseDirection()
        {
            return Direction.Right;
        }
    }
}
