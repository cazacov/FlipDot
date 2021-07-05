using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;

namespace FontExporter
{
    class AdafruitFontExporter
    {
        private const int PREVIEW_X = 128;
        private const int PREVIEW_Y = 128;
        private const int PIXEL_SIZE = 4;

        public void Export(string headerFileName, string previewFileName, string fontName, Font font, Character refChar)
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
                        gr.DrawString(ch.Code.ToString(), ft, Brushes.Cyan, rect, stringFormat);

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
    }
}
