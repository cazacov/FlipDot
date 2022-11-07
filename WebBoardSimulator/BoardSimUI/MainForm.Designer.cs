namespace BoardSimUI
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pBoard = new System.Windows.Forms.Panel();
            this.pbBoard = new System.Windows.Forms.PictureBox();
            this.cbSize = new System.Windows.Forms.ComboBox();
            this.lMatrixSize = new System.Windows.Forms.Label();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.panel2 = new System.Windows.Forms.Panel();
            this.rtLog = new System.Windows.Forms.RichTextBox();
            this.pBoard.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbBoard)).BeginInit();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // pBoard
            // 
            this.pBoard.Controls.Add(this.pbBoard);
            this.pBoard.Controls.Add(this.cbSize);
            this.pBoard.Controls.Add(this.lMatrixSize);
            this.pBoard.Dock = System.Windows.Forms.DockStyle.Top;
            this.pBoard.Location = new System.Drawing.Point(0, 0);
            this.pBoard.Name = "pBoard";
            this.pBoard.Size = new System.Drawing.Size(1440, 282);
            this.pBoard.TabIndex = 11;
            this.pBoard.Resize += new System.EventHandler(this.panel1_Resize);
            // 
            // pbBoard
            // 
            this.pbBoard.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pbBoard.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.pbBoard.Location = new System.Drawing.Point(19, 71);
            this.pbBoard.Name = "pbBoard";
            this.pbBoard.Size = new System.Drawing.Size(1400, 190);
            this.pbBoard.TabIndex = 11;
            this.pbBoard.TabStop = false;
            this.pbBoard.Resize += new System.EventHandler(this.pbBoard_Resize);
            // 
            // cbSize
            // 
            this.cbSize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbSize.FormattingEnabled = true;
            this.cbSize.Items.AddRange(new object[] {
            "28x19",
            "38x28",
            "56x38"});
            this.cbSize.Location = new System.Drawing.Point(162, 12);
            this.cbSize.Name = "cbSize";
            this.cbSize.Size = new System.Drawing.Size(242, 40);
            this.cbSize.TabIndex = 7;
            // 
            // lMatrixSize
            // 
            this.lMatrixSize.AutoSize = true;
            this.lMatrixSize.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lMatrixSize.Location = new System.Drawing.Point(19, 15);
            this.lMatrixSize.Name = "lMatrixSize";
            this.lMatrixSize.Size = new System.Drawing.Size(128, 32);
            this.lMatrixSize.TabIndex = 6;
            this.lMatrixSize.Text = "Matrix size";
            // 
            // splitter1
            // 
            this.splitter1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.splitter1.Cursor = System.Windows.Forms.Cursors.HSplit;
            this.splitter1.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter1.Location = new System.Drawing.Point(0, 282);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(1440, 10);
            this.splitter1.TabIndex = 12;
            this.splitter1.TabStop = false;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.SystemColors.Control;
            this.panel2.Controls.Add(this.rtLog);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 292);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1440, 382);
            this.panel2.TabIndex = 13;
            // 
            // rtLog
            // 
            this.rtLog.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.rtLog.BackColor = System.Drawing.Color.Black;
            this.rtLog.ForeColor = System.Drawing.Color.White;
            this.rtLog.Location = new System.Drawing.Point(18, 20);
            this.rtLog.Name = "rtLog";
            this.rtLog.Size = new System.Drawing.Size(1400, 347);
            this.rtLog.TabIndex = 14;
            this.rtLog.Text = "";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 32F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1440, 674);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.pBoard);
            this.Name = "MainForm";
            this.Text = "WebBoard Simulator";
            this.pBoard.ResumeLayout(false);
            this.pBoard.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbBoard)).EndInit();
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private Panel pBoard;
        private PictureBox pbBoard;
        private ComboBox cbSize;
        private Label lMatrixSize;
        private Splitter splitter1;
        private Panel panel2;
        private RichTextBox rtLog;
    }
}