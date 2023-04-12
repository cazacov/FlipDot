using System;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal interface IRenderer : IDisposable
    {
        void Begin();
        void Draw(int x, int y, SnakeObject obj, Direction inDir = Direction.None, Direction outDir = Direction.None);
        Task End();

        int GetWidth();
        int GetHeight();
        Task Clear();
        Task GameOver(int x, int y);
        Task GameWon();
        Task ShowScore(int score);
    }
}