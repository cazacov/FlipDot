using System.Diagnostics;

namespace FontExporter
{
    [DebuggerDisplay("{Code} ({FontCode})  {Width}x{Height}")]
    class Character
    {
        public int Code;
        public int FontCode;
        public int Width;
        public int Height;
        public bool[,] Bits;
    }
}