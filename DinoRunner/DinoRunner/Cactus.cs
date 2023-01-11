using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DinoRunner
{
    enum CactusType
    {
        Type1,
        Type2
    }

    internal class Cactus : Pos
    {
        public CactusType Type { get; }

        public Cactus(int x, int y, CactusType type) : base(x, y)
        {
            Type = type;
        }
    }
}
