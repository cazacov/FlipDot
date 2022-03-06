using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class Field : IDisposable
    {
        private int width;
        private int height;
        private List<Pos> path = new List<Pos>();
        private IRenderer renderer;

        public Field(int width, int height, IRenderer renderer)
        {
            this.width = width;
            this.height = height;
            this.renderer = renderer;
        }

        public async Task Show(List<Pos> snake, Pos apple)
        {
            renderer.Begin();
            var snakeHead = snake.Last();
            for (var i = 0; i < width + 2; i++)
            {
                renderer.Draw(i, 0, SnakeObject.Wall);
                renderer.Draw(i, height+1, SnakeObject.Wall);
            }
            for (var y = 0; y < height; y++)
            {
                renderer.Draw(0, y+1, SnakeObject.Wall);
                for (var x = 0; x < width; x++)
                {
                    var pos = new Pos(x, y);
                    if (pos.Equals(snakeHead))
                    {
                        renderer.Draw(x + 1, y + 1, SnakeObject.SnakeHead);
                    }
                    else if (snake.Contains(pos))
                    {
                        renderer.Draw(x+1, y+1, SnakeObject.SnakeBody);
                    }
                    else if (path.Contains(pos))
                    {
                        renderer.Draw(x + 1, y + 1, SnakeObject.Path);
                    }
                    else if (pos.Equals(apple))
                    {
                        renderer.Draw(x + 1, y + 1, SnakeObject.Apple);
                    }
                    else
                    {
                        renderer.Draw(x + 1, y + 1, SnakeObject.Empty);
                    }
                }
                renderer.Draw(width+1, y + 1, SnakeObject.Wall);
            }
            await renderer.End();
        }

        public void Dispose()
        {
            if (renderer != null)
            {
                renderer.Dispose();
            }
            this.renderer = null;
            
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
