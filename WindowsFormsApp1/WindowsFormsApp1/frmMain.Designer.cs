namespace WindowsFormsApp1
{
    partial class frmMain
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.btnNativeMain = new System.Windows.Forms.Button();
            this.btnThreadRun = new System.Windows.Forms.Button();
            this.btnThreadstop = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(289, 151);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 1;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(192, 196);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(264, 199);
            this.richTextBox1.TabIndex = 2;
            this.richTextBox1.Text = "";
            // 
            // btnNativeMain
            // 
            this.btnNativeMain.Location = new System.Drawing.Point(113, 32);
            this.btnNativeMain.Name = "btnNativeMain";
            this.btnNativeMain.Size = new System.Drawing.Size(75, 23);
            this.btnNativeMain.TabIndex = 3;
            this.btnNativeMain.Text = "btnNativeMain";
            this.btnNativeMain.UseVisualStyleBackColor = true;
            this.btnNativeMain.Click += new System.EventHandler(this.btnNativeMain_Click);
            // 
            // btnThreadRun
            // 
            this.btnThreadRun.Location = new System.Drawing.Point(275, 45);
            this.btnThreadRun.Name = "btnThreadRun";
            this.btnThreadRun.Size = new System.Drawing.Size(114, 23);
            this.btnThreadRun.TabIndex = 4;
            this.btnThreadRun.Text = "btnThreadRun";
            this.btnThreadRun.UseVisualStyleBackColor = true;
            this.btnThreadRun.Click += new System.EventHandler(this.btnThreadRun_Click);
            // 
            // btnThreadstop
            // 
            this.btnThreadstop.Location = new System.Drawing.Point(414, 45);
            this.btnThreadstop.Name = "btnThreadstop";
            this.btnThreadstop.Size = new System.Drawing.Size(113, 23);
            this.btnThreadstop.TabIndex = 5;
            this.btnThreadstop.Text = "btnThreadstop";
            this.btnThreadstop.UseVisualStyleBackColor = true;
            this.btnThreadstop.Click += new System.EventHandler(this.btnThreadstop_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btnThreadstop);
            this.Controls.Add(this.btnThreadRun);
            this.Controls.Add(this.btnNativeMain);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.textBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button btnNativeMain;
        private System.Windows.Forms.Button btnThreadRun;
        private System.Windows.Forms.Button btnThreadstop;
    }
}

