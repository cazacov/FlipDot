using System;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class FlipDotRenderer2 : IRenderer
    {
        private readonly int fieldWidth;
        private readonly int fieldHeight;
        private readonly int matrixWidth;
        private readonly int matrixHeight;
        private readonly string matrixUrl;
        private byte[] bits;
        private readonly HttpClient restClient;
        private readonly int bytesInRow;

        public FlipDotRenderer2(int fieldWidth, int fieldHeight, int matrixWidth, int matrixHeight, string matrixUrl)
        {
            this.fieldWidth = Math.Min(fieldWidth * 2, matrixWidth) ;
            this.fieldHeight = Math.Min(fieldHeight * 2, matrixHeight);
            this.matrixWidth = matrixWidth;
            this.matrixHeight = matrixHeight;
            this.matrixUrl = matrixUrl;
            this.bytesInRow = (matrixWidth + 7) / 8;
            this.bits = new byte[bytesInRow * matrixHeight];
            this.restClient = new HttpClient();
            restClient.BaseAddress = new Uri(matrixUrl);
        }

        public async Task Clear()
        {
            var content = new StringContent("{\n}", Encoding.UTF8, "application/json");
            content.Headers.ContentType = MediaTypeHeaderValue.Parse("application/json");
            var result = await restClient.PostAsync("cls", content);

        }

        public void Dispose()
        {
            restClient.Dispose();
        }

        public void Begin()
        {
            this.bits = new byte[matrixHeight * bytesInRow];
        }

        public void Draw(int x, int y, SnakeObject obj, Direction inDir, Direction outDir)
        {
            var xx = x*2;
            var yy = y*2;
            switch (obj)
            {
                case SnakeObject.Apple:
                    SetPixel(xx - 1, yy, true);
                    SetPixel(xx + 1, yy, true);
                    SetPixel(xx, yy, true);
                    SetPixel(xx, yy - 1, true);
                    SetPixel(xx, yy + 1, true);
                    break;
                case SnakeObject.Hit:
                    SetPixel(xx, yy, true);
                    break;
                case SnakeObject.SnakeBody:
                case SnakeObject.SnakeHead:
                    SetPixel(xx, yy, true);
                    if (inDir == Direction.Left || outDir == Direction.Left)
                    {
                        SetPixel(xx-1, yy, true);
                    }
                    if (inDir == Direction.Right || outDir == Direction.Right)
                    {
                        SetPixel(xx + 1, yy, true);
                    }
                    if (inDir == Direction.Up || outDir == Direction.Up)
                    {
                        SetPixel(xx, yy - 1, true);
                    }
                    if (inDir == Direction.Down || outDir == Direction.Down)
                    {
                        SetPixel(xx, yy + 1, true);
                    }
                    break;
                case SnakeObject.Wall:
                case SnakeObject.Empty:
                case SnakeObject.Path:
                    break;
            }
        }

        private void SetPixel(int x, int y, bool set)
        {
            var xx = (this.matrixWidth - this.fieldWidth) / 2 + x;
            if (xx < 0 || x >= matrixWidth)
            {
                return;
            }
            if (y < 0 || y >= fieldHeight)
            {
                return;
            }

            var pos = bytesInRow * y + xx / 8;
            if (set)
            {
                bits[pos] |= (byte)(0x80 >> (xx & 7));
            }
            else
            {
                bits[((matrixWidth + 7) / 8) * y + xx / 8] &= (byte)(0xFF7F >> (xx & 7));
            }
        }

        public async Task End()
        {
            var base64 = Convert.ToBase64String(bits);
            var str = $"{{\n   \"frameBuffer\": \"{base64}\"\n}}";
            var content = new StringContent(str, Encoding.UTF8, "application/json");
            content.Headers.ContentType = MediaTypeHeaderValue.Parse("application/json");
            var result = await restClient.PostAsync("data", content);
        }

        public async Task GameOver(int x, int y)
        {
            //
        }

        public async Task GameWon()
        {
            //
        }

        public async Task ShowScore(int score)
        {
            //
        }

        public int GetWidth()
        {
            //return fieldWidth;
            return (fieldWidth + 1) / 2;
        }

        public int GetHeight()
        {
            //return fieldHeight;
            return (fieldHeight + 1) / 2;
        }
    }
}
