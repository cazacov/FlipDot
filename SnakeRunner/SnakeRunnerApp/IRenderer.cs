using System;

namespace SnakeRunnerApp
{
    internal interface IRenderer : IDisposable
    {
        void Begin();
        void Draw(int x, int y, SnakeObject obj);
        void End();
        void GameOver(int x, int y);
        void GameWon();
        void ShowScore(int score);
    }
}