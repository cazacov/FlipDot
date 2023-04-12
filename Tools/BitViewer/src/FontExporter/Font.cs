using System.Collections.Generic;

namespace FontExporter
{
    internal class Font
    {
        public int FontCode;
        public SortedList<int, Character> Characters = new SortedList<int, Character>();
    }
}