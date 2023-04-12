namespace BoardSimUI.Processor
{
    internal class AddTextCommand :BaseCommand
    {
        public int Left;
        public int Bottom;
        public bool IsBig;
        public string Text;
    }
}
