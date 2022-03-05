using System;
using System.Diagnostics;

namespace SnakeRunnerApp
{
    [DebuggerDisplay("{X},{Y}")]
    public class Pos
    {
        public int Y { get; set; }
        public int X { get; set; }

        public Pos(int X, int Y)
        {
            this.X = X;
            this.Y = Y;
        }
        

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

        protected bool Equals(Pos other)
        {
            return Y == other.Y && X == other.X;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj is not Pos pos) return false;
            return Equals(pos);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Y, X);
        }
    }

    [DebuggerDisplay("{X},{Y} - {CostDistance}")]
    public class PathPos: Pos
    {
        public PathPos(int X, int Y) : base(X, Y) {}
        public int Cost { get; set; }
        public int Distance { get; set; }
        public int CostDistance => Cost + Distance;
        public PathPos Parent { get; set; }

        public void SetDistance(Pos target)
        {
            this.Distance = Math.Abs(target.X - X) + Math.Abs(target.Y - Y);
        }

        protected bool Equals(PathPos other)
        {
            return Y == other.Y && X == other.X;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj is not Pos pos) return false;
            return Equals(pos);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Y, X);
        }
    }
}