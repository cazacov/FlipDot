using System;

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
        private const int Height = 140;
        private const int Width = 140;

        private bool[,] Pixels = new bool[Height, Width];

        public void Cls()
        {
            Pixels = new bool[19, 140];
        }

        public void DrawBaseLine()
        {
            for (var x = 0; x < Height; x++)
            {
                Pixels[17, x] = true;
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
            Pixels[y + 6, x + 1] = false;
            Pixels[y + 7, x + 1] = false;
            Pixels[y + 7, x + 2] = false;
            Pixels[y + 8, x + 2] = false;
            Pixels[y + 6, x + 6] = false;
            Pixels[y + 7, x + 6] = false;
            Pixels[y + 7, x + 7] = false;
            Pixels[y + 8, x + 6] = false;
        }

        public void Display(string url)
        {
            ;
        }
    }
}
