namespace Demo
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.rtStatus = new System.Windows.Forms.RichTextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnSave = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbTxt = new System.Windows.Forms.RadioButton();
            this.rbSnp = new System.Windows.Forms.RadioButton();
            this.chkConnect = new System.Windows.Forms.CheckBox();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.txtFilePath = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtVisa = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.Controls.Add(this.rtStatus, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(4);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 306F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(736, 455);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // rtStatus
            // 
            this.rtStatus.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rtStatus.Location = new System.Drawing.Point(4, 310);
            this.rtStatus.Margin = new System.Windows.Forms.Padding(4);
            this.rtStatus.Name = "rtStatus";
            this.rtStatus.Size = new System.Drawing.Size(728, 141);
            this.rtStatus.TabIndex = 0;
            this.rtStatus.Text = "";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Transparent;
            this.panel1.Controls.Add(this.btnSave);
            this.panel1.Controls.Add(this.groupBox1);
            this.panel1.Controls.Add(this.chkConnect);
            this.panel1.Controls.Add(this.btnBrowse);
            this.panel1.Controls.Add(this.txtFilePath);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.txtVisa);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(4, 4);
            this.panel1.Margin = new System.Windows.Forms.Padding(4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(728, 298);
            this.panel1.TabIndex = 1;
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSave.Font = new System.Drawing.Font("Arial", 24F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSave.Location = new System.Drawing.Point(538, 166);
            this.btnSave.Margin = new System.Windows.Forms.Padding(4);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(174, 114);
            this.btnSave.TabIndex = 7;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbTxt);
            this.groupBox1.Controls.Add(this.rbSnp);
            this.groupBox1.Location = new System.Drawing.Point(144, 152);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(228, 80);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "dataType";
            // 
            // rbTxt
            // 
            this.rbTxt.AutoSize = true;
            this.rbTxt.Location = new System.Drawing.Point(99, 30);
            this.rbTxt.Margin = new System.Windows.Forms.Padding(4);
            this.rbTxt.Name = "rbTxt";
            this.rbTxt.Size = new System.Drawing.Size(92, 22);
            this.rbTxt.TabIndex = 1;
            this.rbTxt.Text = "pure data";
            this.rbTxt.UseVisualStyleBackColor = true;
            this.rbTxt.Click += new System.EventHandler(this.rbFileType_Clicked);
            // 
            // rbSnp
            // 
            this.rbSnp.AutoSize = true;
            this.rbSnp.Checked = true;
            this.rbSnp.Location = new System.Drawing.Point(9, 30);
            this.rbSnp.Margin = new System.Windows.Forms.Padding(4);
            this.rbSnp.Name = "rbSnp";
            this.rbSnp.Size = new System.Drawing.Size(51, 22);
            this.rbSnp.TabIndex = 0;
            this.rbSnp.TabStop = true;
            this.rbSnp.Text = "snp";
            this.rbSnp.UseVisualStyleBackColor = true;
            this.rbSnp.Click += new System.EventHandler(this.rbFileType_Clicked);
            // 
            // chkConnect
            // 
            this.chkConnect.AutoSize = true;
            this.chkConnect.Location = new System.Drawing.Point(14, 166);
            this.chkConnect.Margin = new System.Windows.Forms.Padding(4);
            this.chkConnect.Name = "chkConnect";
            this.chkConnect.Size = new System.Drawing.Size(81, 22);
            this.chkConnect.TabIndex = 5;
            this.chkConnect.Text = "connect";
            this.chkConnect.UseVisualStyleBackColor = true;
            this.chkConnect.CheckedChanged += new System.EventHandler(this.chkConnect_CheckedChanged);
            // 
            // btnBrowse
            // 
            this.btnBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnBrowse.Location = new System.Drawing.Point(640, 110);
            this.btnBrowse.Margin = new System.Windows.Forms.Padding(4);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(72, 32);
            this.btnBrowse.TabIndex = 4;
            this.btnBrowse.Text = "...";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // txtFilePath
            // 
            this.txtFilePath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtFilePath.Location = new System.Drawing.Point(16, 112);
            this.txtFilePath.Margin = new System.Windows.Forms.Padding(4);
            this.txtFilePath.Name = "txtFilePath";
            this.txtFilePath.Size = new System.Drawing.Size(586, 26);
            this.txtFilePath.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Navy;
            this.label2.Location = new System.Drawing.Point(13, 79);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 18);
            this.label2.TabIndex = 2;
            this.label2.Text = "SavePath";
            // 
            // txtVisa
            // 
            this.txtVisa.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtVisa.Location = new System.Drawing.Point(14, 37);
            this.txtVisa.Margin = new System.Windows.Forms.Padding(4);
            this.txtVisa.Name = "txtVisa";
            this.txtVisa.Size = new System.Drawing.Size(590, 26);
            this.txtVisa.TabIndex = 1;
            this.txtVisa.Text = "TCPIP0::LOCALHOST::hislip0::INSTR";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Navy;
            this.label1.Location = new System.Drawing.Point(14, 9);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(99, 18);
            this.label1.TabIndex = 0;
            this.label1.Text = "VisaAddress";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightSkyBlue;
            this.ClientSize = new System.Drawing.Size(736, 455);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "saveDemo";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.RichTextBox rtStatus;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rbTxt;
        private System.Windows.Forms.RadioButton rbSnp;
        private System.Windows.Forms.CheckBox chkConnect;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.TextBox txtFilePath;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtVisa;
        private System.Windows.Forms.Label label1;
    }
}

