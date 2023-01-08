namespace BoardSimUI.Processor
{
    public interface ICommandProcessor
    {
        bool ProcessCommand(BaseCommand command, out string message);
    }
}
