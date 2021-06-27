using System;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace BitsViewer
{
    public partial class frmMain : Form
    {
        private string fileName;
        private int fileSize;
        private int bitSize;
        private int rows;
        private int columns;
        private bool fileLoaded;
        private bool isBigEndian;
        private int wordLength;
        private int offset;
        private byte[] bytes;
        private readonly BitsRender bitsRender;
        private readonly DumpRender dumpRender;

        public frmMain()
        {
            InitializeComponent();
            this.bitsRender = new BitsRender();
            this.dumpRender = new DumpRender(this.lvDump);
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            this.InitVariables();
            this.DisplayVariables();
        }

        private void DisplayVariables()
        {
            if (!fileLoaded)
            {
                pnlScrollbox.BackColor = SystemColors.InactiveCaption;
                pictureBox.BackColor = SystemColors.InactiveCaption;
                lblFileName.Text = "No file";
                lblFileSize.Text = "Size: ";
            }
            else
            {
                lblFileName.Text = System.IO.Path.GetFileName(fileName);
                lblFileSize.Text = $"Size: {fileSize} bytes";
                pnlScrollbox.BackColor = Color.DarkGray;
                pictureBox.BackColor = Color.Black;
            }
            cbBitSize.SelectedIndex = this.bitSize - 1;
            txtRows.Text = rows.ToString();
            txtCols.Text = columns.ToString();
            cbWordSize.SelectedIndex = this.wordLength - 1;
            cbEndian.SelectedIndex = this.isBigEndian ? 0 : 1;
            cbOffset.SelectedIndex = this.offset;
        }

        private void InitVariables()
        {
            this.fileName = "";
            this.fileSize = 0;
            this.fileLoaded = false;
            this.bitSize = 2;
            this.rows = 512;
            this.columns = 0;
            this.wordLength = 1;
            this.isBigEndian = true;
            this.offset = 0;
        }

        private void btnFile_Click(object sender, EventArgs e)
        {
            if (dlgFile.ShowDialog() == DialogResult.OK)
            {
                //Get the path of specified file
                this.fileName = dlgFile.FileName;
                LoadFile();
            }
        }

        private void LoadFile()
        {
            this.bytes = System.IO.File.ReadAllBytes(this.fileName);
            this.fileSize = bytes.Length;
            this.fileLoaded = true;
            ShowFile();
            DisplayVariables();
            this.dumpRender.Load(this.bytes);
        }

        private void ShowFile()
        {
            if (!this.fileLoaded)
            {
                return;
            }
            this.columns = (fileSize - 1)/ rows + 1;
            this.bitsRender.LoadBytes(this.bytes);
            this.bitsRender.Render(this.bitSize, this.rows, this.wordLength, this.isBigEndian, this.offset);
            if (this.bitsRender.Image != null)
            {
                pictureBox.AutoSize = true;
                this.pictureBox.Image = bitsRender.Image;
            }
            else
            {
                pictureBox.BackColor = SystemColors.InactiveCaption;
            }
        }

        private void cbBitSize_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.bitSize = cbBitSize.SelectedIndex + 1;
            ShowFile();
        }

        private void pictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            var offset = this.bitsRender.GetOffset(e.X, e.Y);

            if (offset >= 0)
            {
                stlPosition.Text = $"Address: 0x{offset:X6} {offset:D8}";
                strValue.Text = $"Value: {bytes[offset]:D3} {bytes[offset]:X2}";
            }
            else
            {
                stlPosition.Text = "";
                strValue.Text = "";
            }
        }

        private void cbWordSize_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.wordLength = cbWordSize.SelectedIndex + 1;
            ShowFile();
        }

        private void cbEndian_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.isBigEndian = cbEndian.SelectedIndex == 0;
            ShowFile();
        }

        private void cbOffset_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.offset = cbOffset.SelectedIndex;
            ShowFile();
        }
    }
}
