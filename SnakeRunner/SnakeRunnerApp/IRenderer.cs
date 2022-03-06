using System;
using System.Threading.Tasks;

namespace SnakeRunnerApp
{
    internal interface IRenderer : IDisposable
    {
        void Begin();
        void Draw(int x, int y, SnakeObject obj);
        Task End();
        Task GameOver(int x, int y);
        Task GameWon();
        Task ShowScore(int score);
        Task Clear();
    }
}