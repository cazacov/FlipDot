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
        private IRenderer renderer;
        private readonly bool showFrame;

        public Field(IRenderer renderer, bool showFrame)
        {
            this.renderer = renderer;
            this.showFrame = showFrame;

            this.width = renderer.GetWidth() - (showFrame ? 2 : 0);
            this.height = renderer.GetHeight() - (showFrame ? 2 : 0);
        }

        public int Width => this.width;
        public int Height => this.height;

        public async Task Show(List<Pos> snake, Pos apple)
        {
            renderer.Begin();
            var snakeHead = snake.Last();

            if (showFrame)
            {
                for (var i = 0; i < width + 2; i++)
                {
                    renderer.Draw(i, 0, SnakeObject.Wall);
                    renderer.Draw(i, height + 1, SnakeObject.Wall);
                }
            }

            for (var y = 0; y < height; y++)
            {
                if (showFrame) {
                   renderer.Draw(0, y+1, SnakeObject.Wall);
                }
                for (var x = 0; x < width; x++)
                {
                    var pos = new Pos(x, y);
                    var xx = x + (showFrame ? 1 : 0);
                    var yy = y + (showFrame ? 1 : 0);
                    if (pos.Equals(apple))
                    {
                        renderer.Draw(xx, yy, SnakeObject.Apple);
                    }
                    else
                    {
                        if (!snake.Contains(pos) && !path.Contains(pos))
                        {
                            renderer.Draw(xx, yy, SnakeObject.Empty);
                        }
                    }
                }
                if (showFrame)
                {
                    renderer.Draw(width + 1, y + 1, SnakeObject.Wall);
                }
            }

            DrawChain(path, false);
            DrawChain(snake, true);

            await renderer.End();
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
                    renderer.Draw(pos.X + (showFrame ? 1 : 0), pos.Y + (showFrame ? 1 : 0),
                        i == chain.Count - 1 ? SnakeObject.SnakeHead : SnakeObject.SnakeBody, inDir,
                        outDir);
                }
                else
                {
                    renderer.Draw(pos.X + (showFrame ? 1 : 0), pos.Y + (showFrame ? 1 : 0), SnakeObject.Path, inDir, outDir);
                }
            }
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
