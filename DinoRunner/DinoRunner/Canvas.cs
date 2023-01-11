using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Net.Http.Json;
using System.Text.Json.Serialization;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using static System.Formats.Asn1.AsnWriter;

namespace DinoRunner
{

    enum State
    {
        Step1,
        Step2,
        Jump
    }

    internal class Canvas
    {
        public const int Height = 19;
        public const int Width = 140;

        private bool[,] Pixels = new bool[Height, Width];

        public void Cls()
        {
            Pixels = new bool[19, 140];
        }

        public void DrawBaseLine()
        {
            for (var x = 0; x < Width; x++)
            {
                Pixels[16, x] = true;
            }
        }

        public void PutDino(int x, int y, State state)
        {
            Pixels[y + 3, x] = true;
            Pixels[y + 4, x] = true;
            Pixels[y + 4, x + 1] = true;
            Pixels[y + 5, x + 1] = true;
            Pixels[y + 5, x + 2] = true;
            Pixels[y + 6, x + 2] = true;
            Pixels[y + 4, x + 3] = true;
            Pixels[y + 5, x + 3] = true;
            Pixels[y + 6, x + 3] = true;
            Pixels[y + 7, x + 3] = true;
            Pixels[y + 4, x + 4] = true;
            Pixels[y + 5, x + 4] = true;
            Pixels[y + 6, x + 4] = true;
            Pixels[y + 7, x + 4] = true;
            Pixels[y + 0, x + 5] = true;
            Pixels[y + 1, x + 5] = true;
            Pixels[y + 2, x + 5] = true;
            Pixels[y + 3, x + 5] = true;
            Pixels[y + 4, x + 5] = true;
            Pixels[y + 5, x + 5] = true;
            Pixels[y + 6, x + 5] = true;
            Pixels[y + 7, x + 5] = true;
            Pixels[y + 0, x + 6] = true;
            Pixels[y + 2, x + 6] = true;
            Pixels[y + 3, x + 6] = true;
            Pixels[y + 4, x + 6] = true;
            Pixels[y + 5, x + 6] = true;
            Pixels[y + 0, x + 7] = true;
            Pixels[y + 1, x + 7] = true;
            Pixels[y + 2, x + 7] = true;
            Pixels[y + 0, x + 8] = true;
            Pixels[y + 1, x + 8] = true;
            Pixels[y + 2, x + 8] = true;

            switch (state)
            {
                case State.Step1:
                    Pixels[y + 8, x + 3] = true;
                    Pixels[y + 8, x + 4] = false;
                    Pixels[y + 8, x + 5] = false;
                    break;
                case State.Step2:
                    Pixels[y + 8, x + 3] = false;
                    Pixels[y + 8, x + 4] = false;
                    Pixels[y + 8, x + 5] = true;
                    break;
                case State.Jump:
                    Pixels[y + 8, x + 3] = true;
                    Pixels[y + 8, x + 4] = false;
                    Pixels[y + 8, x + 5] = true;
                    break;
            }
            Pixels[y + 6, x] = false;
            Pixels[y + 6, x + 1] = false;
            Pixels[y + 7, x + 1] = false;
            Pixels[y + 7, x + 2] = false;
            Pixels[y + 8, x + 2] = false;

            Pixels[y + 6, x + 6] = false;
            Pixels[y + 6, x + 7] = false;
            Pixels[y + 7, x + 6] = false;
            Pixels[y + 7, x + 7] = false;
            Pixels[y + 8, x + 6] = false;
        }

        public async Task Display(string url)
        {
            var bytesperRow = (Width + 7) >> 3;
            var bytes = new byte[bytesperRow * Height];

            for (var y = 0; y < Height; y++)
            {
                var mask = 0x80;
                var index = bytesperRow * y;
                for (var x = 0; x < Width; x++)
                {
                    if (Pixels[y, x])
                    {
                        bytes[index] = (byte)(bytes[index] | mask);
                    }
                    mask >>= 1;
                    if (mask == 0)
                    {
                        index++;
                        mask = 0x80;
                    }
                }
            }

            var encoded = Convert.ToBase64String(bytes);

            var client = new HttpClient();
            client.BaseAddress = new Uri(url);

            var str = JsonConvert.SerializeObject(
                new
                {
                    frameBuffer = encoded
                }
            );
            var content = new StringContent(str, Encoding.UTF8, "application/json");
            content.Headers.ContentType = MediaTypeHeaderValue.Parse("application/json");
            var result = await client.PostAsync("data", content);
        }

        public void DrawStones(List<Pos> stones)
        {
            foreach (var stone in stones)
            {
                PutPixel(stone.X, stone.Y);
            }
        }

        private void PutPixel(int x, int y)
        {
            if (x is >= 0 and < Width && y is >= 0 and < Height)
            {
                Pixels[y, x] = true;
            }
        }

        public void DrawCacti(List<Cactus> cacti)
        {
            foreach (var cactus in cacti)
            {
                var x = cactus.X;
                var y = cactus.Y;

                PutBar(x + 2, y, 2, 8);

                switch (cactus.Type)
                {
                    case CactusType.Type1:
                        PutBar(x, y + 2, 1, 3);
                        PutPixel(x + 1, y + 4);
                        PutPixel(x + 4, y+3);
                        PutBar(x + 5, y+1, 1, 3);
                        break;
                    case CactusType.Type2:
                        PutBar(x, y + 1, 1, 4);
                        PutPixel(x + 1, y + 4);
                        PutPixel(x + 4, y + 4);
                        PutBar(x + 5, y + 2, 1, 3);
                        break;
                }
            }
        }

        private void PutBar(int x, int y, int w, int h)
        {
            for (var xx = x; xx < x + w; xx++)
            {
                for (var yy = y; yy < y + h; yy++)
                {
                    PutPixel(xx,yy);
                }
            }
        }
    }
}
