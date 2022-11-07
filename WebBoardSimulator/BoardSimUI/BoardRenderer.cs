using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoardSimUI
{
    internal class BoardRenderer
    {
        private readonly PictureBox pictureBox;

        public BoardRenderer(PictureBox pictureBox)
        {
            this.pictureBox = pictureBox;
        }

        public void Show(Board board)
        {
            var cellWidth = pictureBox.Width / board.Width;
            var cellHeight = pictureBox.Height / board.Height;
            if (cellWidth > cellHeight)
            {
                cellWidth = cellHeight;
            }
            else
            {
                cellHeight = cellWidth;
            }

            if (cellHeight < 2)
            {
                cellHeight = cellWidth = 2;
            }

            var marginX = (pictureBox.Width - cellWidth * board.Width - 1) / 2;
            var marginY = (pictureBox.Height - cellHeight * board.Height - 1) / 2;

            var result = new Bitmap(pictureBox.Width, pictureBox.Height);
            var gt = Graphics.FromImage(result);

            gt.FillRectangle(Brushes.DimGray, 0, 0, pictureBox.Width, pictureBox.Height);
            gt.FillRectangle(Brushes.Black, marginX, marginY, cellWidth * board.Width, cellHeight * board.Height);

            for (var y = 0; y <= board.Height; y++)
            {
                gt.DrawLine(Pens.Gray, 
                    (int)marginX, (int)(marginY + y*cellHeight), 
                    (int)(marginX + cellWidth * board.Width), (int)(marginY + y * cellHeight));
            }

            for (var x = 0; x <= board.Width; x++)
            {
                gt.DrawLine(Pens.Gray,
                    (int)(marginX + x * cellWidth), (int)marginY,
                    (int)(marginX + +x * cellWidth), (int)(marginY + cellHeight * board.Height));
            }
            gt.Dispose();
            pictureBox.Image = result;
        }
    }
}
