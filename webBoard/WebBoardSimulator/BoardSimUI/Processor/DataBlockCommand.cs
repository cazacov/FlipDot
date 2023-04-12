namespace BoardSimUI.Processor
{
    internal class DataBlockCommand : BaseCommand
    {
        public int Left;
        public int Top;
        public int Width;
        public int Height;
        public byte[] FrameBuffer;
    }
}
