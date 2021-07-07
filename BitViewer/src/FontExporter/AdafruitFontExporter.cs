using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;

namespace FontExporter
{
    class AdafruitFontExporter
    {
        private const int PREVIEW_X = 128;
        private const int PREVIEW_Y = 128;
        private const int PIXEL_SIZE = 4;

        public void Preview(string previewFileName, Font font, Character refChar)
        {
            var cols = 8;
            var rows = (font.Characters.Count - 1) / 8 + 1;

            StringFormat stringFormat = new StringFormat();
            stringFormat.Alignment = StringAlignment.Center;
            stringFormat.LineAlignment = StringAlignment.Center;

            using (var bmp = new Bitmap(cols * PREVIEW_X, rows * PREVIEW_Y, PixelFormat.Format24bppRgb))
            {
                using (var gr = Graphics.FromImage(bmp))
                {
                    var ft = new System.Drawing.Font("Verdana", 8);
                    gr.FillRectangle(Brushes.Black, gr.ClipBounds);

                    for (int i = 0; i < font.Characters.Count; i++)
                    {
                        var ch = font.Characters.Values[i];
                        var col = i % 8;
                        var row = i / 8;
                        var frame = new Rectangle(col * PREVIEW_X, row * PREVIEW_Y, PREVIEW_X-1, PREVIEW_Y-1);
                        gr.DrawRectangle(Pens.Gray, frame);
                        var rect = new Rectangle(col * PREVIEW_X, (row  + 1)* PREVIEW_Y - 18 , PREVIEW_X-1, 18);
                        var charDesc = $"{ch.Code} {ch.Width}x{ch.Height}";
                        gr.DrawString(charDesc, ft, Brushes.Cyan, rect, stringFormat);

                        var x0 = PREVIEW_X / 2 - ch.Width * PIXEL_SIZE  / 2 + col * PREVIEW_X;
                        var y0 = row * PREVIEW_Y + 4;

                        for (var x = 0; x < ch.Width; x++)
                        {
                            for (var y = 0; y < ch.Height; y++)
                            {
                                var pixelFrame = new Rectangle(x0 + x * PIXEL_SIZE, y0 + y * PIXEL_SIZE, PIXEL_SIZE,
                                    PIXEL_SIZE);
                                gr.DrawRectangle(Pens.Gray, pixelFrame);
                                var pixel = new Rectangle(x0 + x * PIXEL_SIZE + 1, y0 + y * PIXEL_SIZE + 1, PIXEL_SIZE-1,
                                    PIXEL_SIZE-1);

                                if (ch.Bits[y, x])
                                {
                                    gr.FillRectangle(Brushes.Yellow, pixel);
                                }
                            }
                        }
                    }
                    gr.Flush();
                    bmp.Save(previewFileName, ImageFormat.Png);
                }
            }



        }

        public void Export(string fileName, Font font, string fontName, Character refChar, int fromChar, int toChar,
            int advance)
        {
            var rc = CharPlaceholderUnderscore(refChar);

            var bitmaps = new List<int>();
            var glyphs = new List<List<int>>();

            if (toChar < 0)
            {
                toChar = font.Characters.Values.Max(x => x.Code);
            }

            /*
            var height = font.Characters.Values
                .Where(x => x.Code >= fromChar && x.Code <= toChar)
                .Max(x => x.Height);
            */

            var height = refChar.Height;

            var refCharIndex = -1;

            using (var sr = new StreamWriter(fileName))
            {
                sr.WriteLine($"const uint8_t {fontName}Bitmaps[] PROGMEM = {{");

                for (var ch = fromChar; ch <= toChar; ch++)
                {
                    bool isPlaceholder = false;
                    var bitmapIndex = bitmaps.Count;

                    Character character;
                    if (!font.Characters.TryGetValue(ch, out character))
                    {
                        character = rc;
                        isPlaceholder = true;
                    }

                    var data = GetPixels(character.Bits, character.Width, character.Height);
                    var glyph = new List<int>();
                    glyph.Add(character.Code);
                    glyph.Add(bitmapIndex); // bitmap index
                    glyph.Add(character.Width);
                    glyph.Add(character.Height);
                    glyph.Add(character.Width + advance);
                    glyph.Add(0);
                    glyph.Add(-(height - 1));
                    glyphs.Add(glyph);

                    bitmaps.AddRange(data);
                    var bytes = String.Join(", ", data.ConvertAll(x => "0x" + x.ToString("X2"))) + ",";
                    sr.WriteLine($"\t{bytes}  // {character.Code}");
                    
                }
                sr.WriteLine("};");

                sr.WriteLine();
                sr.WriteLine($"const GFXglyph {fontName}Glyphs[] PROGMEM = {{");
                foreach (var glyph in glyphs)
                {
                    var glStr = String.Join(", ", glyph.ConvertAll(x => x.ToString()).Skip(1));
                    sr.WriteLine($"\t{{ {glStr} }}, \t // 0x{glyph[0]:X2}");
                }
                sr.WriteLine("}");

                sr.WriteLine($"const GFXfont {fontName} PROGMEM = {{(uint8_t*){fontName}Bitmaps,\n\t(GFXglyph *){fontName}Glyphs,\n\t 0x{fromChar:X2},0x{toChar:X2},{height+1}}}; ");
            }
        }

        private List<int> GetPixels(bool[,] bits, int width, int height)
        {
            var shift = 7;
            var result = new List<int>();
            var acc = 0;

            for (var y = 0; y < height; y++)
            {
                for (var x = 0; x < width; x++)
                {
                    if (bits[y, x])
                    {
                        acc += 1 << shift;
                    }
                    shift--;
                    if (shift >= 0)
                    {
                        continue;
                    }
                    shift = 7;
                    result.Add(acc);
                    acc = 0;
                }
            }

            if (shift != 7)
            {
                result.Add(acc);
            }
            return result;
        }

        private Character CharPlaceholderBox(Character refChar)
        {
            var result = new Character()
            {
                Bits = new bool[refChar.Height, refChar.Width],
                Code = 0,
                FontCode = 0,
                Height = refChar.Height,
                Width = refChar.Width
            };

            for (int x = 0; x < result.Width; x++)
            {
                result.Bits[0, x] = true;
                result.Bits[result.Height - 1, x] = true;
            }

            for (var y = 0; y < result.Height; y++)
            {
                result.Bits[y, 0] = true;
                result.Bits[y, result.Width - 1] = true;
            }
            return result;
        }

        private Character CharPlaceholderUnderscore(Character refChar)
        {
            var result = new Character()
            {
                Bits = new bool[1, refChar.Width],
                Code = 0,
                FontCode = 0,
                Height = 1,
                Width = refChar.Width
            };

            for (int x = 0; x < result.Width; x++)
            {
                result.Bits[0, x] = true;
            }
            return result;
        }
    }
}
