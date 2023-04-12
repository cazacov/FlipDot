using System;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal class FlipDotRenderer : IRenderer
    {
        private readonly int fieldWidth;
        private readonly int fieldHeight;
        private readonly int matrixWidth;
        private readonly int matrixHeight;
        private readonly string matrixUrl;
        private byte[] bits;
        private readonly HttpClient restClient;
        private readonly int bytesInRow;

        public FlipDotRenderer(int fieldWidth, int fieldHeight, int matrixWidth, int matrixHeight, string matrixUrl)
        {
            this.fieldWidth = fieldWidth;
            this.fieldHeight = fieldHeight;
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
            var xx = (this.matrixWidth - 2*this.fieldWidth) / 2 + x;
            var pos = bytesInRow * y + xx / 8;

            switch (obj)
            {
                case SnakeObject.Apple:
                case SnakeObject.Hit:
                case SnakeObject.SnakeBody:
                case SnakeObject.SnakeHead:
                case SnakeObject.Wall:
                    bits[pos] |= (byte)(0x80 >> (xx & 7));
                    break;
                case SnakeObject.Empty:
                case SnakeObject.Path:
                    bits[((matrixWidth + 7) / 8) * y + xx / 8] &= (byte)(0xFF7F >> (xx & 7));
                    break;
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
            return fieldWidth;
        }

        public int GetHeight()
        {
            return fieldHeight;
        }
    }
}
