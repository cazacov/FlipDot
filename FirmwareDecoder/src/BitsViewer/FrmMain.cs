using System;
using System.Drawing;
using System.Windows.Forms;

namespace BitsViewer
{
    public partial class frmMain : Form
    {
        private string fileName;
        private int fileSize;
        private int bitSize;
        private int rows;
        private int columns;
        private int position;
        private bool fileLoaded;
        private byte[] bytes;
        private readonly BitsRender render;

        public frmMain()
        {
            InitializeComponent();
            this.render = new BitsRender();
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
        }

        private void InitVariables()
        {
            this.fileName = "";
            this.fileSize = 0;
            this.fileLoaded = false;
            this.bitSize = 2;
            this.rows = 512;
            this.columns = 0;
            this.position = 0;
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
        }

        private void ShowFile()
        {
            if (!this.fileLoaded)
            {
                return;
            }
            this.columns = (fileSize - 1)/ rows + 1;
            this.position = 0;
            this.render.LoadBytes(this.bytes);
            this.render.Render(this.bitSize, this.rows);
            if (this.render.Image != null)
            {
                pictureBox.AutoSize = true;
                this.pictureBox.Image = render.Image;
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
            var offset = this.render.GetOffset(e.X, e.Y);
            stlPosition.Text = offset;
        }
    }
}
