using System.Drawing;
using System.Drawing.Imaging;

namespace BitsViewer
{
    class BitsRender
    {
        private byte[] bytes;
        private int len;
        private int rows;
        private int columns;
        private int bytesInBlock;
        private int blockPixels;

        public void LoadBytes(byte[] bytes)
        {
            this.bytes = bytes;
            this.len = bytes.Length;
            this.Image = null;
        }

        public Image Image { get; set; }

        public void Render(int bitSize, int rows)
        {
            this.bytesInBlock = 1;
            this.rows = rows;
            this.columns = (len / bytesInBlock  - 1) / rows + 1;
            this.blockPixels = bytesInBlock * 8 * bitSize + bytesInBlock - 1 + bitSize;

            this.Image = new Bitmap(columns * blockPixels, rows* bitSize, PixelFormat.Format24bppRgb);
            var graphics = Graphics.FromImage(Image);
            using (var brush = new SolidBrush(Color.Black))
            {
                graphics.FillRectangle(brush, 0, 0, Image.Width, Image.Height);
            }

            using (var pen = new Pen(Color.White, 1))
            {
                var index = 0;
                while (index < bytes.Length)
                {
                    for (var i = 0; i < 8; i++)
                    {
                        var bit = (bytes[index] & (1 << i)) != 0;
                        var y = (index % rows) * bitSize;
                        var x = (index / rows + 1) * blockPixels - i * bitSize - bitSize;
                        if (bit)
                        {
                            graphics.DrawRectangle(pen, x, y, 1, 1);
                        }
                    }
                    index++;
                }
            }

        }
    }
}
