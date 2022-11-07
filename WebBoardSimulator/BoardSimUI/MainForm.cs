namespace BoardSimUI
{
    public partial class MainForm : Form
    {
        private readonly Board board;
        private readonly BoardRenderer boardRenderer;

        public MainForm()
        {
            InitializeComponent();

            this.boardRenderer = new BoardRenderer(this.pbBoard);

            this.board = new Board();
            this.cbSize.SelectedItem = 0;
            this.board.Init(cbSize.SelectedText);
            this.boardRenderer.Show(board);
        }

        private void pbBoard_Resize(object sender, EventArgs e)
        {
            
        }

        private void panel1_Resize(object sender, EventArgs e)
        {
            pbBoard.Left = 19;
            pbBoard.Top = 71;
            pbBoard.Width = pBoard.Width - 40;
            pbBoard.Height = pBoard.Height - 92;
            this.boardRenderer.Show(board);
        }
    }
}