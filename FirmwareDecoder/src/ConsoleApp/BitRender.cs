using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;

namespace ConsoleApp
{
    class BitRender
    {
        public System.Drawing.Bitmap DoRender(byte[] bytes)
        {
            var height = 512;
            var width = bytes.Length / height;
            if (width * height < bytes.Length)
            {
                width++;
            }

            var image = new Bitmap(width * 20, height * 2, PixelFormat.Format24bppRgb);
            var graphics = Graphics.FromImage(image);
            using (var brush = new SolidBrush(Color.Black))
            {
                graphics.FillRectangle(brush, 0, 0, image.Width, image.Height);
            }

            using (var pen = new Pen(Color.White, 1))
            {

                for (int index = 0; index < bytes.Length; index++)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        var bit = (bytes[index] & (1 << i)) != 0;
                        var y = (index % height) * 2;
                        var x = (index / height + 1) * 20 - i * 2 - 2;
                        if (bit)
                        {
                            graphics.DrawRectangle(pen, x, y, 1, 1);
                        }
                    }
                }
            }
            return image;
        }
    }
}
