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
                case ClsCommand:
                    message = "Accepted";
                    Cls();
                    return true;
                case DataBlockCommand data:
                    return DataBlock(
                        data.Left, data.Top, data.Width, data.Height,
                        data.FrameBuffer, out message);
                    break;
                case BlockCommand data:
                    return SetBlock(
                        data.Left, data.Top, data.Width, data.Height,
                        data.On, out message);
                    break;
                case AddTextCommand text:
                    return TextCommand(text.Text, text.Left, text.Bottom, text.IsBig, out message);
                    break;
                default:
                    message = "Unknown command";
                    return false;
            }

            message = "Accepted";
            return true;
        }

        private bool TextCommand(string text, int left, int bottom, bool isBig, out string message)
        {
            message = "Accepted";
            return true;
        }

        private bool SetBlock(int left, int top, int width, int height, bool on, out string message)
        {
            var bytesPerRow = (width + 7) >> 3;

            for (var y = 0; y < board.Height - top; y++)
            {
                for (var x = 0; x < board.Width - left; x++)
                {
                    var index = y * bytesPerRow + (x >> 3);
                    var mask = 0x80 >> ((x + left) >> 3);
                    board.Pixels[y + top, x + left] = on;
                }
            }

            message = "Accepted";
            return true;
        }

        private bool DataBlock(int left, int top, int width, int height, byte[] dataFrameBuffer, out string message)
        {
            var bytesPerRow = (width + 7) >> 3;

            for (var y = 0; y < Math.Min(board.Height - top, height); y++)
            {
                for (var x = 0; x < Math.Min(board.Width - left, width); x++)
                {
                    var index = y * bytesPerRow + (x >> 3);
                    var mask = 0x80 >> (x & 0x07);
                    board.Pixels[y + top, x + left] = (dataFrameBuffer[index] & mask) != 0;
                }
            }

            message = "Accepted";
            return true;
        }

        private void Cls()
        {
            board.Pixels = new bool[board.Height, board.Width];
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

            message = "Accepted";
            return true;
        }
    }
}
