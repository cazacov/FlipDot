﻿using System;
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
        private int col;
        private int bitSize;

        public void LoadBytes(byte[] bytes)
        {
            this.bytes = bytes;
            this.len = bytes.Length;
            this.Image = null;
            this.col = Color.LightGray.ToArgb();
        }

        public Image Image { get; set; }

        public void Render(int bitSize, int rows)
        {
            this.bitSize = bitSize;
            this.bytesInBlock = 1;
            this.rows = rows;
            this.columns = (len / bytesInBlock - 1) / rows + 1;
            this.blockPixels = bytesInBlock * 8 * bitSize + bytesInBlock - 1 + bitSize;

            this.bmpHeight = rows * bitSize;
            this.bmpWidth = columns * blockPixels;
            this.bits = new Int32[bmpWidth * bmpHeight];

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
                        ShowBit(x, y);
                    }
                }
                index++;
            }
            var bitsHandle = GCHandle.Alloc(bits, GCHandleType.Pinned);
            var bmp = new Bitmap(bmpWidth, bmpHeight, bmpWidth * 4, PixelFormat.Format32bppPArgb,
                bitsHandle.AddrOfPinnedObject());
            this.Image = bmp.Clone(new Rectangle(0,0, bmpWidth, bmpHeight), bmp.PixelFormat);
            bmp.Dispose();
            bitsHandle.Free();
//            bits = null;
        }

        private void ShowBit(int x, int y)
        {
            var idx = x + y * bmpWidth;
            for (var j = 0; j < this.bitSize; j++)
            {
                for (var k = 0; k < this.bitSize; k++)
                {
                    bits[idx++] = col;
                }

                idx -= this.bitSize;
                idx += bmpWidth;
            }
        }

        public Bitmap Bitmap { get; set; }

        public string GetOffset(int ptrX, int ptrY)
        {
            var y = ptrY / bitSize;
            var x = ptrX / blockPixels;
            var pos = x * rows + y;
            return $"{pos}  0x{pos:X04}";
        }
    }
}
