
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
            this.gbView = new System.Windows.Forms.GroupBox();
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
            this.pnlScrollbox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.panel2.SuspendLayout();
            this.gbView.SuspendLayout();
            this.gbFile.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlScrollbox
            // 
            this.pnlScrollbox.AutoScroll = true;
            this.pnlScrollbox.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.pnlScrollbox.Controls.Add(this.pictureBox);
            this.pnlScrollbox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlScrollbox.Location = new System.Drawing.Point(0, 0);
            this.pnlScrollbox.Name = "pnlScrollbox";
            this.pnlScrollbox.Size = new System.Drawing.Size(1846, 1211);
            this.pnlScrollbox.TabIndex = 1;
            // 
            // pictureBox
            // 
            this.pictureBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.pictureBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.pictureBox.Location = new System.Drawing.Point(88, 134);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(967, 597);
            this.pictureBox.TabIndex = 1;
            this.pictureBox.TabStop = false;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.gbView);
            this.panel2.Controls.Add(this.gbFile);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel2.Location = new System.Drawing.Point(1425, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(421, 1169);
            this.panel2.TabIndex = 2;
            // 
            // gbView
            // 
            this.gbView.Controls.Add(this.txtCols);
            this.gbView.Controls.Add(this.lblCols);
            this.gbView.Controls.Add(this.txtRows);
            this.gbView.Controls.Add(this.lblRows);
            this.gbView.Controls.Add(this.label2);
            this.gbView.Controls.Add(this.cbBitSize);
            this.gbView.Location = new System.Drawing.Point(23, 189);
            this.gbView.Name = "gbView";
            this.gbView.Size = new System.Drawing.Size(370, 149);
            this.gbView.TabIndex = 1;
            this.gbView.TabStop = false;
            this.gbView.Text = "View";
            // 
            // txtCols
            // 
            this.txtCols.Location = new System.Drawing.Point(256, 85);
            this.txtCols.Name = "txtCols";
            this.txtCols.ReadOnly = true;
            this.txtCols.Size = new System.Drawing.Size(97, 31);
            this.txtCols.TabIndex = 5;
            this.txtCols.Text = "512";
            // 
            // lblCols
            // 
            this.lblCols.AutoSize = true;
            this.lblCols.Location = new System.Drawing.Point(190, 88);
            this.lblCols.Name = "lblCols";
            this.lblCols.Size = new System.Drawing.Size(55, 25);
            this.lblCols.TabIndex = 4;
            this.lblCols.Text = "Cols";
            // 
            // txtRows
            // 
            this.txtRows.Location = new System.Drawing.Point(108, 85);
            this.txtRows.Name = "txtRows";
            this.txtRows.Size = new System.Drawing.Size(69, 31);
            this.txtRows.TabIndex = 3;
            this.txtRows.Text = "512";
            // 
            // lblRows
            // 
            this.lblRows.AutoSize = true;
            this.lblRows.Location = new System.Drawing.Point(18, 88);
            this.lblRows.Name = "lblRows";
            this.lblRows.Size = new System.Drawing.Size(65, 25);
            this.lblRows.TabIndex = 2;
            this.lblRows.Text = "Rows";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 38);
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
            "3x3 px"});
            this.cbBitSize.Location = new System.Drawing.Point(108, 30);
            this.cbBitSize.Name = "cbBitSize";
            this.cbBitSize.Size = new System.Drawing.Size(121, 33);
            this.cbBitSize.TabIndex = 0;
            // 
            // gbFile
            // 
            this.gbFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gbFile.Controls.Add(this.btnFile);
            this.gbFile.Controls.Add(this.lblFileSize);
            this.gbFile.Controls.Add(this.lblFileName);
            this.gbFile.Location = new System.Drawing.Point(23, 23);
            this.gbFile.Name = "gbFile";
            this.gbFile.Size = new System.Drawing.Size(370, 137);
            this.gbFile.TabIndex = 0;
            this.gbFile.TabStop = false;
            this.gbFile.Text = "File";
            // 
            // btnFile
            // 
            this.btnFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnFile.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnFile.Location = new System.Drawing.Point(256, 84);
            this.btnFile.Name = "btnFile";
            this.btnFile.Size = new System.Drawing.Size(92, 37);
            this.btnFile.TabIndex = 2;
            this.btnFile.Text = "Select";
            this.btnFile.UseVisualStyleBackColor = true;
            this.btnFile.Click += new System.EventHandler(this.btnFile_Click);
            // 
            // lblFileSize
            // 
            this.lblFileSize.AutoSize = true;
            this.lblFileSize.Location = new System.Drawing.Point(18, 90);
            this.lblFileSize.Name = "lblFileSize";
            this.lblFileSize.Size = new System.Drawing.Size(184, 25);
            this.lblFileSize.TabIndex = 1;
            this.lblFileSize.Text = "Size: 65536 bytes";
            // 
            // lblFileName
            // 
            this.lblFileName.AutoSize = true;
            this.lblFileName.Location = new System.Drawing.Point(18, 43);
            this.lblFileName.Name = "lblFileName";
            this.lblFileName.Size = new System.Drawing.Size(30, 25);
            this.lblFileName.TabIndex = 0;
            this.lblFileName.Text = "...";
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.stlPosition});
            this.statusStrip1.Location = new System.Drawing.Point(0, 1169);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1846, 42);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // stlPosition
            // 
            this.stlPosition.Name = "stlPosition";
            this.stlPosition.Size = new System.Drawing.Size(125, 32);
            this.stlPosition.Text = "Offset: 0 0";
            // 
            // dlgFile
            // 
            this.dlgFile.FileName = "openFileDialog1";
            this.dlgFile.RestoreDirectory = true;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1846, 1211);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.pnlScrollbox);
            this.Name = "frmMain";
            this.Text = "BitsViewer";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.pnlScrollbox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.panel2.ResumeLayout(false);
            this.gbView.ResumeLayout(false);
            this.gbView.PerformLayout();
            this.gbFile.ResumeLayout(false);
            this.gbFile.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
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
    }
}

