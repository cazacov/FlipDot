using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class SnakeGame : BaseService
    {
        private const int width = 4;
        private const int height = 3;
        private readonly Random random = new Random();

        public List<Pos> snake;
        public Pos apple;

        private Field field = new Field(width, height);

        public SnakeGame()
        {
            this.snake = new List<Pos>()
            {
                new Pos(random.Next(width),random.Next(height))
            };
            this.apple = PlaceApple(snake);
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
            while (!cancellationToken.IsCancellationRequested)
            {
                try
                {
                    field.Show(snake, apple);
                    await Task.Delay(1000, cancellationToken);
                }
                catch (OperationCanceledException)
                {
                    //
                }

            }
        }
    }
}
