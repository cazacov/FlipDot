using System.Diagnostics.PerformanceData;
using Accessibility;

namespace BoardSimUI.Processor
{
    internal class BoardCommandProcessor : ICommandProcessor
    {
        private readonly Board board;

        public BoardCommandProcessor(Board board)
        {
            this.board = board;
        }

        public bool ProcessCommand(BaseCommand command, out string message)
        {
            switch (command)
            {
                case DataCommand data: 
                    return SetFrameBuffer(data.FrameBuffer, out message);
                    break;
                default:
                    message = "Unknown command";
                    return false;
            }

            message = "Ok";
            return true;
        }

        private bool SetFrameBuffer(byte[] frameBuffer, out string message)
        {
            var bytesPerRow = (board.Width + 7) / 8;

            var mask = 0x80;
            var y = 0;
            var x = 0;
            var index = 0;

            while (index < Math.Min(frameBuffer.Length, bytesPerRow * board.Height))
            {
                var pixel = frameBuffer[index] & mask;
                if (pixel == 0)
                {
                    board.Pixels[y, x] = false;
                }
                else
                {
                    board.Pixels[y, x] = true;
                }
                
                mask >>= 1;
                if (mask == 0)
                {
                    ++index;
                    mask = 0x80;
                }

                ++x;
                if (x == board.Width)
                {
                    ++y;
                    x = 0;
                    index++;
                    mask = 0x80;
                }
                else
                {

                }
            }

            message = "Ok";
            return true;
        }
    }
}
