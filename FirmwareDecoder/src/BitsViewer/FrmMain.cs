﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
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
                lblFileSize.Text = $"Size: {fileSize}";
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
            ShowFile();
            this.fileLoaded = true;
            DisplayVariables();
        }

        private void ShowFile()
        {
            this.columns = (fileSize - 1)/ rows + 1;
            this.position = 0;
            this.render.LoadBytes(this.bytes);
            this.render.Render(this.bitSize, this.rows);
            if (this.render.Image != null)
            {
                this.pictureBox.Image = render.Image;
                this.pictureBox.Width = render.Image.Width;
                this.pictureBox.Height = render.Image.Height;
                this.pictureBox.Location = new Point(0, 0);
            }
            else
            {
                pictureBox.BackColor = SystemColors.InactiveCaption;
            }
        }
    }
}