using System.Text.RegularExpressions;

namespace BoardSimUI
{
    internal class Board
    {
        public bool [,] Pixels;
        public int Height;
        public int Width;

        public Board()
        {
            this.Init("140x19");
        }

        public void Init(string size)
        {
            var oldSize = $"{Width}x{Height}";
            if (size != oldSize)
            {
                var regex = new Regex("(\\d+)x(\\d+)");
                var matches = regex.Match(size);
                if (matches.Groups.Count == 2)
                {
                    this.Width = Int32.Parse(matches.Groups[1].Value);
                    this.Height = Int32.Parse(matches.Groups[2].Value);
                }
                else
                {
                    this.Width = 140;
                    this.Height = 19;
                }

                Pixels = new bool[Height, Width];
            }
        }
    }
}
