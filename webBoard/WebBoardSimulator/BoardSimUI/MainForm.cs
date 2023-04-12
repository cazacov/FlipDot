using BoardSimUI.Processor;

namespace BoardSimUI
{
    public partial class MainForm : Form, ICommandProcessor
    {
        private readonly Board board;
        private readonly BoardRenderer boardRenderer;
        private readonly BoardCommandProcessor commandProcessor;

        public MainForm()
        {
            InitializeComponent();

            this.boardRenderer = new BoardRenderer(this.pbBoard);
            this.board = new Board();
            this.commandProcessor = new BoardCommandProcessor(board);
            
            this.cbSize.SelectedItem = 0;
            this.board.Init(cbSize.SelectedText);
            this.boardRenderer.Show(board);
        }

        private void pbBoard_Resize(object sender, EventArgs e)
        {
            
        }

        private void panel1_Resize(object sender, EventArgs e)
        {
            if (board == null)
            {
                return;
            }
            pbBoard.Left = 19;
            pbBoard.Top = 71;
            pbBoard.Width = pBoard.Width - 40;
            pbBoard.Height = pBoard.Height - 92;
            this.boardRenderer.Show(board);
        }

        public bool ProcessCommand(BaseCommand command, out string message)
        {
            var result = this.commandProcessor.ProcessCommand(command, out message);
            if (result)
            {
                ShowBoardSafe();
            }
            return result;
        }

        private void ShowBoardSafe()
        {
            if (pBoard.InvokeRequired)
            {
                var safeShow = ShowBoardSafe;
                pBoard.Invoke(safeShow);
            }
            else
            {
                this.boardRenderer.Show(board);
            }
        }
    }
}