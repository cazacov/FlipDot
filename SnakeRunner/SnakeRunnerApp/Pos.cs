using System;

namespace SnakeRunnerApp
{
    public record Pos(int X, int Y)
    {
        public Pos GoTo(Direction nextDir)
        {
            switch (nextDir)
            {
                case Direction.Up:
                    return new Pos(X, Y - 1);
                case Direction.Down:
                    return new Pos(X, Y + 1);
                case Direction.Left:
                    return new Pos(X-1, Y);
                case Direction.Right:
                    return new Pos(X+1, Y);
            }
            throw new ArgumentOutOfRangeException("Direction out of range");
        }
    }
}