using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

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
        private int bmpHeight;
        private int bmpWidth;
        private int[] bits;
        private int colBitOn;
        private int bitSize;
        private int wordLength;
        private bool isBigEndian;
        private int offset;
        private int colBitOff;
        private int colBack;
        private int colBorder;
        private int colOnSelected;
        private int colBorderSelected;
        private int selectedFrom;
        private int selectedTo;

        public void LoadBytes(byte[] bytes)
        {
            this.bytes = bytes;
            this.len = bytes.Length;
            this.Image = null;
            this.colBitOn = Color.White.ToArgb();
            this.colBitOff = Color.Black.ToArgb();
            this.colBorder = Color.DimGray.ToArgb();
            this.colOnSelected = Color.Yellow.ToArgb();
            this.colBorderSelected = Color.SaddleBrown.ToArgb();
            this.colBack = Color.Navy.ToArgb();
            this.selectedFrom = 0;
            this.selectedTo = 0;
        }

        public Image Image { get; set; }

        public void Render(int bitSize, int rows, int wordLength, bool isBigEndian, int offset)
        {
            this.bitSize = bitSize;
            this.bytesInBlock = wordLength;
            this.wordLength = wordLength;
            this.isBigEndian = isBigEndian;
            this.offset = offset;
            this.rows = rows;
            this.columns = (len / bytesInBlock - 1) / rows + 1;
            this.blockPixels = bytesInBlock * 8 * bitSize + (bytesInBlock + 1) * bitSize;

            this.bmpHeight = rows * bitSize;
            this.bmpWidth = columns * blockPixels;
            this.bits = new Int32[bmpWidth * bmpHeight];
            for (int i = 0; i < bits.Length; i++)
            {
                bits[i] = colBack;
            }

            var index = 0;
            while (index < bytes.Length)
            {
                for (var k = 0; k < wordLength; k++)
                {
                    RenderByte(index);
                    index++;
                    if (index == bytes.Length)
                    {
                        break;
                    }
                }
            }
            var bitsHandle = GCHandle.Alloc(bits, GCHandleType.Pinned);
            var bmp = new Bitmap(bmpWidth, bmpHeight, bmpWidth * 4, PixelFormat.Format32bppPArgb,
                bitsHandle.AddrOfPinnedObject());
            this.Image = bmp.Clone(new Rectangle(0,0, bmpWidth, bmpHeight), bmp.PixelFormat);
            bmp.Dispose();
            bitsHandle.Free();
//            bits = null;
        }

        private void RenderPart(int from, int to)
        {
            if (from < offset)
            {
                from = offset;
            }
            for (var i = from; i < to; i++)
            {
                RenderByte(i - offset);
            }
        }

        private void RenderByte(int index)
        {
            var j = index % this.wordLength;
            for (var i = 0; i < 8; i++)
            {
                var data = 0;
                var pos = index + this.offset;
                if (pos < bytes.Length)
                {
                    data = bytes[pos];
                }
                var bit = (data & (1 << i)) != 0;
                var y = ((index / this.wordLength) % this.rows) * this.bitSize;
                int x = index / (this.rows * this.wordLength) * this.blockPixels;
                if (this.isBigEndian)
                {
                    x += j * 8 * this.bitSize + (7 - i) * this.bitSize;
                }
                else
                {
                    x += (this.wordLength - j - 1) * 8 * this.bitSize + (7 - i) * this.bitSize;
                }
                var isSelected = pos >= selectedFrom && pos < selectedTo;
                ShowBit(x, y, bit, isSelected);
            }
        }

        private void ShowBit(int x, int y, bool bit, bool isSelected)
        {
            var border = isSelected ? colBorderSelected : colBorder;
            var pixel = bit ? (isSelected ? colOnSelected : colBitOn) : colBitOff;

            var idx = x + y * bmpWidth;

            if (bitSize < 3)
            {
                for (var j = 0; j < this.bitSize; j++)
                {
                    for (var k = 0; k < this.bitSize; k++)
                    {
                        bits[idx++] = pixel;
                    }

                    idx -= this.bitSize;
                    idx += bmpWidth;
                }
            }
            else
            {
                for (var j = 0; j < this.bitSize; j++)
                {
                    for (var k = 0; k < this.bitSize; k++)
                    {
                        if (j > 0 && k > 0 && j < bitSize - 1 && k < bitSize - 1)
                        {
                            bits[idx++] = pixel;
                        }
                        else
                        {
                            bits[idx++] = border;
                        }
                    }
                    idx -= this.bitSize;
                    idx += bmpWidth;
                }
            }
        }

        public Bitmap Bitmap { get; set; }

        public int GetOffset(int ptrX, int ptrY)
        {
            if (bytes == null)
            {
                return -1;
            }

            var y = ptrY / bitSize;
            var x = ptrX / blockPixels;
            var xx = ptrX % blockPixels / (8 * bitSize);
            if (xx >= wordLength)
            {
                xx = wordLength - 1;
            }
            if (!isBigEndian)
            {
                xx = wordLength - xx - 1;
            }
            var pos = x * rows * wordLength + y * wordLength + xx + offset;
            if (pos >= bytes.Length)
            {
                return -1;
            }
            return pos;
        }

        public void SetSelection(int from, int to)
        {
            bool isOverlap = from < selectedTo && to > selectedFrom;
            if (isOverlap)
            {
                var updateFrom = Math.Min(selectedFrom, from);
                var updateTo = Math.Max(selectedTo, to);
                selectedFrom = from;
                selectedTo = to;
                RenderPart(updateFrom, updateTo);
            }
            else
            {
                var updateFrom = selectedFrom;
                var updateTo = selectedTo;
                selectedFrom = from;
                selectedTo = to;
                RenderPart(updateFrom, updateTo);
                RenderPart(selectedFrom, selectedTo);
            }
        }
    }
}
