using System;
using System.Collections.Generic;

namespace FontExporter
{
    class FontsParser
    {
        private byte[] bytes;
        public Dictionary<int, Font> Fonts { get; private set; }

        public void Parse(byte[] bytes)
        {
            this.bytes = bytes;
            Fonts = new Dictionary<int, Font>();
            int offset = 0x100;
            while (offset < 0x4FDA)
            {
                var ch = ReadNextCharacter(ref offset);
                if (!Fonts.TryGetValue(ch.FontCode, out var font))
                {
                    font = new Font() {FontCode = ch.FontCode};
                    Fonts.Add(ch.FontCode, font);
                }
                font.Characters.Add(ch.Code, ch);
            }
        }

        private Character ReadNextCharacter(ref int offset)
        {
            var character = new Character();
            character.Code = this.bytes[offset++];
            character.FontCode = this.bytes[offset++];
            character.Width = this.bytes[offset++];
            var len = this.bytes[offset++];
            character.Bits = new bool[24, character.Width];

            var y = 0;
            var x = 0;
            var maxy = 0;
            for (int i = 0; i < len - 4; i++)
            {
                var b = bytes[offset++];
                var bits = (i % 3 == 2) ? 5 : 7;
                b <<= 8 - bits;
                while (bits-- > 0)
                {
                    character.Bits[y,x] = (b & 0x80) != 0;
                    if (character.Bits[y, x] && y > maxy)
                    {
                        maxy = y;
                    }
                    b <<= 1;
                    y++;
                }
                if (i % 3 == 2)
                {
                    y = 0;
                    x++;
                }
            }
            character.Height = maxy + 1;
            return character;
        }
    }
}
