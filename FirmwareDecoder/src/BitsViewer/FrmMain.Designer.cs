
namespace BitsViewer
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pnlScrollbox = new System.Windows.Forms.Panel();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.lvDump = new System.Windows.Forms.ListView();
            this.clAddress = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.clByteDec = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.chByteHex = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.clBits = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.gbView = new System.Windows.Forms.GroupBox();
            this.cbOffset = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cbEndian = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cbWordSize = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtCols = new System.Windows.Forms.TextBox();
            this.lblCols = new System.Windows.Forms.Label();
            this.txtRows = new System.Windows.Forms.TextBox();
            this.lblRows = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbBitSize = new System.Windows.Forms.ComboBox();
            this.gbFile = new System.Windows.Forms.GroupBox();
            this.btnFile = new System.Windows.Forms.Button();
            this.lblFileSize = new System.Windows.Forms.Label();
            this.lblFileName = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.stlPosition = new System.Windows.Forms.ToolStripStatusLabel();
            this.dlgFile = new System.Windows.Forms.OpenFileDialog();
            this.panel1 = new System.Windows.Forms.Panel();
            this.strValue = new System.Windows.Forms.ToolStripStatusLabel();
            this.pnlScrollbox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.panel2.SuspendLayout();
            this.gbView.SuspendLayout();
            this.gbFile.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlScrollbox
            // 
            this.pnlScrollbox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlScrollbox.AutoScroll = true;
            this.pnlScrollbox.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.pnlScrollbox.Controls.Add(this.pictureBox);
            this.pnlScrollbox.Location = new System.Drawing.Point(8, 5);
            this.pnlScrollbox.Margin = new System.Windows.Forms.Padding(6);
            this.pnlScrollbox.Name = "pnlScrollbox";
            this.pnlScrollbox.Size = new System.Drawing.Size(861, 849);
            this.pnlScrollbox.TabIndex = 1;
            // 
            // pictureBox
            // 
            this.pictureBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.pictureBox.Location = new System.Drawing.Point(0, 0);
            this.pictureBox.Margin = new System.Windows.Forms.Padding(6);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(500, 400);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox.TabIndex = 1;
            this.pictureBox.TabStop = false;
            this.pictureBox.Click += new System.EventHandler(this.pictureBox_Click);
            this.pictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseMove);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.lvDump);
            this.panel2.Controls.Add(this.gbView);
            this.panel2.Controls.Add(this.gbFile);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel2.Location = new System.Drawing.Point(873, 0);
            this.panel2.Margin = new System.Windows.Forms.Padding(6);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(501, 860);
            this.panel2.TabIndex = 2;
            // 
            // lvDump
            // 
            this.lvDump.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lvDump.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.clAddress,
            this.clByteDec,
            this.chByteHex,
            this.clBits});
            this.lvDump.Font = new System.Drawing.Font("Courier New", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lvDump.FullRowSelect = true;
            this.lvDump.HideSelection = false;
            this.lvDump.Location = new System.Drawing.Point(18, 433);
            this.lvDump.Name = "lvDump";
            this.lvDump.Size = new System.Drawing.Size(468, 403);
            this.lvDump.TabIndex = 2;
            this.lvDump.UseCompatibleStateImageBehavior = false;
            this.lvDump.View = System.Windows.Forms.View.Details;
            // 
            // clAddress
            // 
            this.clAddress.Text = "Address";
            this.clAddress.Width = 100;
            // 
            // clByteDec
            // 
            this.clByteDec.Text = "Dec";
            this.clByteDec.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // chByteHex
            // 
            this.chByteHex.Text = "Hex";
            // 
            // clBits
            // 
            this.clBits.Text = "Bits";
            this.clBits.Width = 200;
            // 
            // gbView
            // 
            this.gbView.Controls.Add(this.cbOffset);
            this.gbView.Controls.Add(this.label4);
            this.gbView.Controls.Add(this.cbEndian);
            this.gbView.Controls.Add(this.label3);
            this.gbView.Controls.Add(this.cbWordSize);
            this.gbView.Controls.Add(this.label1);
            this.gbView.Controls.Add(this.txtCols);
            this.gbView.Controls.Add(this.lblCols);
            this.gbView.Controls.Add(this.txtRows);
            this.gbView.Controls.Add(this.lblRows);
            this.gbView.Controls.Add(this.label2);
            this.gbView.Controls.Add(this.cbBitSize);
            this.gbView.Location = new System.Drawing.Point(18, 162);
            this.gbView.Margin = new System.Windows.Forms.Padding(6);
            this.gbView.Name = "gbView";
            this.gbView.Padding = new System.Windows.Forms.Padding(6);
            this.gbView.Size = new System.Drawing.Size(468, 251);
            this.gbView.TabIndex = 1;
            this.gbView.TabStop = false;
            this.gbView.Text = "View";
            // 
            // cbOffset
            // 
            this.cbOffset.CausesValidation = false;
            this.cbOffset.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbOffset.FormattingEnabled = true;
            this.cbOffset.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3"});
            this.cbOffset.Location = new System.Drawing.Point(104, 198);
            this.cbOffset.Margin = new System.Windows.Forms.Padding(6);
            this.cbOffset.Name = "cbOffset";
            this.cbOffset.Size = new System.Drawing.Size(126, 33);
            this.cbOffset.TabIndex = 11;
            this.cbOffset.SelectedIndexChanged += new System.EventHandler(this.cbOffset_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 201);
            this.label4.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 25);
            this.label4.TabIndex = 10;
            this.label4.Text = "Offset";
            // 
            // cbEndian
            // 
            this.cbEndian.CausesValidation = false;
            this.cbEndian.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbEndian.FormattingEnabled = true;
            this.cbEndian.Items.AddRange(new object[] {
            "big",
            "little"});
            this.cbEndian.Location = new System.Drawing.Point(363, 142);
            this.cbEndian.Margin = new System.Windows.Forms.Padding(6);
            this.cbEndian.Name = "cbEndian";
            this.cbEndian.Size = new System.Drawing.Size(93, 33);
            this.cbEndian.TabIndex = 9;
            this.cbEndian.SelectedIndexChanged += new System.EventHandler(this.cbEndian_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(275, 145);
            this.label3.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 25);
            this.label3.TabIndex = 8;
            this.label3.Text = "Endian";
            // 
            // cbWordSize
            // 
            this.cbWordSize.CausesValidation = false;
            this.cbWordSize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbWordSize.FormattingEnabled = true;
            this.cbWordSize.Items.AddRange(new object[] {
            "1 byte",
            "2 bytes",
            "3 bytes",
            "4 bytes"});
            this.cbWordSize.Location = new System.Drawing.Point(105, 142);
            this.cbWordSize.Margin = new System.Windows.Forms.Padding(6);
            this.cbWordSize.Name = "cbWordSize";
            this.cbWordSize.Size = new System.Drawing.Size(126, 33);
            this.cbWordSize.TabIndex = 7;
            this.cbWordSize.SelectedIndexChanged += new System.EventHandler(this.cbWordSize_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 145);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 25);
            this.label1.TabIndex = 6;
            this.label1.Text = "Word";
            // 
            // txtCols
            // 
            this.txtCols.Location = new System.Drawing.Point(342, 84);
            this.txtCols.Margin = new System.Windows.Forms.Padding(6);
            this.txtCols.Name = "txtCols";
            this.txtCols.ReadOnly = true;
            this.txtCols.Size = new System.Drawing.Size(114, 31);
            this.txtCols.TabIndex = 5;
            this.txtCols.Text = "512";
            // 
            // lblCols
            // 
            this.lblCols.AutoSize = true;
            this.lblCols.Location = new System.Drawing.Point(275, 87);
            this.lblCols.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.lblCols.Name = "lblCols";
            this.lblCols.Size = new System.Drawing.Size(55, 25);
            this.lblCols.TabIndex = 4;
            this.lblCols.Text = "Cols";
            // 
            // txtRows
            // 
            this.txtRows.Location = new System.Drawing.Point(105, 87);
            this.txtRows.Margin = new System.Windows.Forms.Padding(6);
            this.txtRows.Name = "txtRows";
            this.txtRows.Size = new System.Drawing.Size(126, 31);
            this.txtRows.TabIndex = 3;
            this.txtRows.Text = "512";
            // 
            // lblRows
            // 
            this.lblRows.AutoSize = true;
            this.lblRows.Location = new System.Drawing.Point(12, 90);
            this.lblRows.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.lblRows.Name = "lblRows";
            this.lblRows.Size = new System.Drawing.Size(65, 25);
            this.lblRows.TabIndex = 2;
            this.lblRows.Text = "Rows";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 35);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 25);
            this.label2.TabIndex = 1;
            this.label2.Text = "Bit size";
            // 
            // cbBitSize
            // 
            this.cbBitSize.CausesValidation = false;
            this.cbBitSize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbBitSize.FormattingEnabled = true;
            this.cbBitSize.Items.AddRange(new object[] {
            "1x1 px",
            "2x2 px",
            "3x3 px",
            "4x4 px",
            "5x5 px",
            "6x6 px",
            "7x7 px",
            "8x8 px",
            "9x9 px",
            "10x10 px",
            "11x11 px",
            "12x12 px"});
            this.cbBitSize.Location = new System.Drawing.Point(104, 32);
            this.cbBitSize.Margin = new System.Windows.Forms.Padding(6);
            this.cbBitSize.Name = "cbBitSize";
            this.cbBitSize.Size = new System.Drawing.Size(127, 33);
            this.cbBitSize.TabIndex = 0;
            this.cbBitSize.SelectedIndexChanged += new System.EventHandler(this.cbBitSize_SelectedIndexChanged);
            // 
            // gbFile
            // 
            this.gbFile.Controls.Add(this.btnFile);
            this.gbFile.Controls.Add(this.lblFileSize);
            this.gbFile.Controls.Add(this.lblFileName);
            this.gbFile.Location = new System.Drawing.Point(18, 15);
            this.gbFile.Margin = new System.Windows.Forms.Padding(6);
            this.gbFile.Name = "gbFile";
            this.gbFile.Padding = new System.Windows.Forms.Padding(6);
            this.gbFile.Size = new System.Drawing.Size(468, 119);
            this.gbFile.TabIndex = 0;
            this.gbFile.TabStop = false;
            this.gbFile.Text = "File";
            // 
            // btnFile
            // 
            this.btnFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnFile.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnFile.Location = new System.Drawing.Point(351, 74);
            this.btnFile.Margin = new System.Windows.Forms.Padding(6);
            this.btnFile.Name = "btnFile";
            this.btnFile.Size = new System.Drawing.Size(105, 33);
            this.btnFile.TabIndex = 2;
            this.btnFile.Text = "Select";
            this.btnFile.UseVisualStyleBackColor = true;
            this.btnFile.Click += new System.EventHandler(this.btnFile_Click);
            // 
            // lblFileSize
            // 
            this.lblFileSize.AutoSize = true;
            this.lblFileSize.Location = new System.Drawing.Point(12, 78);
            this.lblFileSize.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.lblFileSize.Name = "lblFileSize";
            this.lblFileSize.Size = new System.Drawing.Size(184, 25);
            this.lblFileSize.TabIndex = 1;
            this.lblFileSize.Text = "Size: 65536 bytes";
            // 
            // lblFileName
            // 
            this.lblFileName.AutoSize = true;
            this.lblFileName.Location = new System.Drawing.Point(12, 28);
            this.lblFileName.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.lblFileName.Name = "lblFileName";
            this.lblFileName.Size = new System.Drawing.Size(30, 25);
            this.lblFileName.TabIndex = 0;
            this.lblFileName.Text = "...";
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.stlPosition,
            this.strValue});
            this.statusStrip1.Location = new System.Drawing.Point(0, 860);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Padding = new System.Windows.Forms.Padding(2, 0, 28, 0);
            this.statusStrip1.Size = new System.Drawing.Size(1374, 42);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // stlPosition
            // 
            this.stlPosition.AutoSize = false;
            this.stlPosition.Name = "stlPosition";
            this.stlPosition.Size = new System.Drawing.Size(320, 32);
            this.stlPosition.Text = "Offset: 0 0";
            this.stlPosition.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // dlgFile
            // 
            this.dlgFile.FileName = "openFileDialog1";
            this.dlgFile.RestoreDirectory = true;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.pnlScrollbox);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(873, 860);
            this.panel1.TabIndex = 4;
            // 
            // strValue
            // 
            this.strValue.Name = "strValue";
            this.strValue.Size = new System.Drawing.Size(85, 32);
            this.strValue.Text = "Value: ";
            // 
            // frmMain
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(1374, 902);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.statusStrip1);
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "frmMain";
            this.Text = "BitsViewer";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.pnlScrollbox.ResumeLayout(false);
            this.pnlScrollbox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.panel2.ResumeLayout(false);
            this.gbView.ResumeLayout(false);
            this.gbView.PerformLayout();
            this.gbFile.ResumeLayout(false);
            this.gbFile.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel pnlScrollbox;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.GroupBox gbFile;
        private System.Windows.Forms.Label lblFileSize;
        private System.Windows.Forms.Label lblFileName;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel stlPosition;
        private System.Windows.Forms.GroupBox gbView;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbBitSize;
        private System.Windows.Forms.Button btnFile;
        private System.Windows.Forms.Label lblCols;
        private System.Windows.Forms.TextBox txtRows;
        private System.Windows.Forms.Label lblRows;
        private System.Windows.Forms.TextBox txtCols;
        private System.Windows.Forms.OpenFileDialog dlgFile;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbEndian;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cbWordSize;
        private System.Windows.Forms.ComboBox cbOffset;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ListView lvDump;
        private System.Windows.Forms.ColumnHeader clAddress;
        private System.Windows.Forms.ColumnHeader clByteDec;
        private System.Windows.Forms.ColumnHeader chByteHex;
        private System.Windows.Forms.ColumnHeader clBits;
        private System.Windows.Forms.ToolStripStatusLabel strValue;
    }
}

