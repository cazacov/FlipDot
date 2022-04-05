using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class Field : IDisposable
    {
        private readonly int width;
        private readonly int height;
        private List<Pos> path = new List<Pos>();
        private IList<IRenderer> renderers;
        private readonly bool showFrame;

        public Field(List<IRenderer> renderers, int width, int height)
        {
            this.renderers = renderers;
            this.width = width;
            this.height = height;
        }

        public int Width => this.width;
        public int Height => this.height;

        public async Task Show(List<Pos> snake, Pos apple)
        {
            RenderersBegin();
            
            var snakeHead = snake.Last();

            if (showFrame)
            {
                for (var i = 0; i < width + 2; i++)
                {
                    RenderesDraw(i, 0, SnakeObject.Wall);
                    RenderesDraw(i, height + 1, SnakeObject.Wall);
                }
            }

            for (var y = 0; y < height; y++)
            {
                for (var x = 0; x < width; x++)
                {
                    var pos = new Pos(x, y);
                    var xx = x + (showFrame ? 1 : 0);
                    var yy = y + (showFrame ? 1 : 0);
                    if (pos.Equals(apple))
                    {
                        RenderesDraw(xx, yy, SnakeObject.Apple);
                    }
                    else
                    {
                        if (!snake.Contains(pos) && !path.Contains(pos))
                        {
                            RenderesDraw(xx, yy, SnakeObject.Empty);
                        }
                    }
                }
            }

            DrawChain(path, false);
            DrawChain(snake, true);

            await RenderersEnd();
        }

        private void RenderesDraw(int x, int y, SnakeObject snakeObject, Direction inDir = Direction.None, Direction outDir = Direction.None)
        {
            foreach (var renderer in renderers)
            {
                renderer.Draw(x, y, snakeObject, inDir, outDir);
            }
        }

        private void RenderersBegin()
        {
            foreach (var renderer in renderers)
            {
                renderer.Begin();
            }
        }

        private async Task RenderersEnd()
        {
            foreach (var renderer in renderers)
            {
                await renderer.End();
            }
        }

        private void DrawChain(List<Pos> chain, bool isSnake)
        {
            for (int i = 0; i < chain.Count; i++)
            {
                var pos = chain[i];
                var inDir = Direction.None;
                var outDir = Direction.None;
                if (i > 0)
                {
                    var prev = chain[i - 1];
                    inDir = pos.DirectionTo(prev);
                }

                if (i < chain.Count - 1)
                {
                    var next = chain[i + 1];
                    outDir = pos.DirectionTo(next);
                }

                if (isSnake)
                {
                    RenderesDraw(pos.X + (showFrame ? 1 : 0), pos.Y + (showFrame ? 1 : 0),
                        i == chain.Count - 1 ? SnakeObject.SnakeHead : SnakeObject.SnakeBody, inDir,
                        outDir);
                }
                else
                {
                    RenderesDraw(pos.X + (showFrame ? 1 : 0), pos.Y + (showFrame ? 1 : 0), SnakeObject.Path, inDir, outDir);
                }
            }
        }

        public void Dispose()
        {
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
