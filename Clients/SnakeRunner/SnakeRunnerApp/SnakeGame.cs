using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class SnakeGame : BaseService
    {
        private readonly int width;
        private readonly int height;
        private readonly Random random = new();

        private readonly List<Pos> snake;
        private Pos apple;
        private Direction snakeDirection;

        private readonly Field field;
        private readonly PathFinder pathFinder;
        private int score;
        private int penalty;
        private readonly List<IRenderer> renderers;

        public SnakeGame()
        {
            this.renderers = new List<IRenderer>();
            this.renderers.Add(new ConsoleRenderer(12, 10));
            this.renderers.Add(new FlipDotRenderer2(12, 10, 32, 19, "http://localhost:5000/"));

            field =  new Field(renderers, 12, 10);
            this.width = field.Width;
            this.height = field.Height;
            this.pathFinder = new PathFinder(this.width, this.height);
            this.snake = new List<Pos>()
            {
                new Pos(random.Next(width),random.Next(height))
            };
            this.apple = PlaceApple(snake);
            snakeDirection = snake[0].Y > height / 2 ? Direction.Up : Direction.Down;
            score = penalty = 0;
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
            await RenderClear();
            bool isLost = false;
            while (!cancellationToken.IsCancellationRequested)
            {
                try
                {
                    field.SetPath(null);
                     var nextDir = ChooseDirection();
                    await MakeMove(nextDir);
                    if (GameIsLost())
                    {
                        isLost = true;
                        break;
                    }
                    if (GameIsWon())
                    {
                        break;
                    }
                    await field.Show(snake, apple);
                    await Task.Delay(100, cancellationToken);
                }
                catch (OperationCanceledException)
                {
                    //
                }
            }

            await field.Show(snake, apple);
            if (isLost)
            {
                var head = snake.Last();
                await  RenderGameOver(head.X, head.Y);
            }
            else
            {
                await RenderGameWon();
            }

            while (!cancellationToken.IsCancellationRequested)
            {
                await Task.Delay(100, cancellationToken);
            }
        }

        private async Task RenderGameWon()
        {
            foreach(var renderer in renderers)
            {
                await renderer.GameWon();
            }
        }

        private async Task RenderGameOver(int x, int y)
        {
            foreach (var renderer in renderers)
            {
                await renderer.GameOver(x, y);
            }
        }

        private async Task RenderClear()
        {
            foreach (var renderer in renderers)
            {
                await renderer.Clear();
            }
        }

        private async Task RenderShowScore(int score)
        {
            foreach (var renderer in renderers)
            {
                await renderer.ShowScore(score);
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
                pos.X >= 0 && pos.X < width 
                && pos.Y >= 0 && pos.Y < height;
        }

        private async Task MakeMove(Direction nextDir)
        {
            var head = snake.Last();
            var nextPos = head.GoTo(nextDir);
            this.snakeDirection = nextDir;
            snake.Add(nextPos);
            if (nextPos.Equals(apple))
            {
                if (snake.Count == width * height)
                {
                    // Game won, do nothing
                }
                else
                {
                    apple = PlaceApple(snake);
                }
                score += 100 - penalty;
                penalty = 0;
                await RenderShowScore(score);
            }
            else
            {
                snake.RemoveAt(0);
                penalty++;
            }
        }



        private Direction ChooseDirection()
        {
            var head = snake.Last();
            //return Direction.Right;
            var routeToApple = pathFinder.FindRoute(head, apple, snake);

            if (routeToApple != null)
            {
                var newSnake = new List<Pos>(snake).Union(routeToApple).Skip(routeToApple.Count-1).ToList();
                var newTail = newSnake.First();
                newSnake.RemoveAt(0);
                var routeToTail = pathFinder.FindRoute(apple, newTail, newSnake);
                if (routeToTail != null)
                {
                    field.SetPath(routeToApple);
                    return head.DirectionTo(routeToApple.First());
                }
            }
            var tail = snake.First();
            var tailRoute = pathFinder.FindRoute(head, tail, snake.Skip(1).ToList());
            if (tailRoute == null)
            {
                return FillArea(head);
            }
            else
            {
                field.SetPath(tailRoute);
                return head.DirectionTo( tailRoute.First());
            }
        }

        

        private Direction FillArea(Pos head)
        {
            var allDirections = new List<Direction> { Direction.Down, Direction.Up, Direction.Left, Direction.Right };
            allDirections.Remove(Opposite(this.snakeDirection));
            var candidates = new List<Direction>(allDirections);
            foreach (var dir in allDirections)
            {
                if (this.snake.Contains(head.GoTo(dir)))
                {
                    candidates.Remove(dir);
                }
            }

            if (!candidates.Any())
            {
                return allDirections[random.Next(allDirections.Count)];
            }
            else
            {
                return candidates[random.Next(candidates.Count)];
            }
        }



        private Direction Opposite(Direction direction)
        {
            return direction switch
            {
                Direction.Down => Direction.Up,
                Direction.Up => Direction.Down,
                Direction.Left => Direction.Right,
                Direction.Right => Direction.Left,
                _ => Direction.Down
            };
        }
    }
}
