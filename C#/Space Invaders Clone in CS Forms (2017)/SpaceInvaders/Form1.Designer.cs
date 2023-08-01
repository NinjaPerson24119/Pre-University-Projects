namespace SpaceInvaders
{
	partial class Form1
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
			this.components = new System.ComponentModel.Container();
			this.pnlView = new System.Windows.Forms.Panel();
			this.picBase = new System.Windows.Forms.PictureBox();
			this.picUFO = new System.Windows.Forms.PictureBox();
			this.picEnemy3 = new System.Windows.Forms.PictureBox();
			this.picEnemy2 = new System.Windows.Forms.PictureBox();
			this.picEnemy1 = new System.Windows.Forms.PictureBox();
			this.picShield = new System.Windows.Forms.PictureBox();
			this.picSpeed = new System.Windows.Forms.PictureBox();
			this.picLife = new System.Windows.Forms.PictureBox();
			this.picAttack = new System.Windows.Forms.PictureBox();
			this.lblInstructions = new System.Windows.Forms.Label();
			this.grpScore = new System.Windows.Forms.GroupBox();
			this.lblScore = new System.Windows.Forms.Label();
			this.grpHighScore = new System.Windows.Forms.GroupBox();
			this.lblHighScore = new System.Windows.Forms.Label();
			this.grpLives = new System.Windows.Forms.GroupBox();
			this.lblLives = new System.Windows.Forms.Label();
			this.btnNewGame = new System.Windows.Forms.Button();
			this.timRefresh = new System.Windows.Forms.Timer(this.components);
			this.grpDifficulty = new System.Windows.Forms.GroupBox();
			this.lblDifficulty = new System.Windows.Forms.Label();
			this.pnlView.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.picBase)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picUFO)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picEnemy3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picEnemy2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picEnemy1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picShield)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picSpeed)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picLife)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picAttack)).BeginInit();
			this.grpScore.SuspendLayout();
			this.grpHighScore.SuspendLayout();
			this.grpLives.SuspendLayout();
			this.grpDifficulty.SuspendLayout();
			this.SuspendLayout();
			// 
			// pnlView
			// 
			this.pnlView.Controls.Add(this.picBase);
			this.pnlView.Controls.Add(this.picUFO);
			this.pnlView.Controls.Add(this.picEnemy3);
			this.pnlView.Controls.Add(this.picEnemy2);
			this.pnlView.Controls.Add(this.picEnemy1);
			this.pnlView.Controls.Add(this.picShield);
			this.pnlView.Controls.Add(this.picSpeed);
			this.pnlView.Controls.Add(this.picLife);
			this.pnlView.Controls.Add(this.picAttack);
			this.pnlView.Controls.Add(this.lblInstructions);
			this.pnlView.Location = new System.Drawing.Point(0, 0);
			this.pnlView.Name = "pnlView";
			this.pnlView.Size = new System.Drawing.Size(800, 600);
			this.pnlView.TabIndex = 0;
			this.pnlView.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
			// 
			// picBase
			// 
			this.picBase.Location = new System.Drawing.Point(664, 419);
			this.picBase.Name = "picBase";
			this.picBase.Size = new System.Drawing.Size(32, 32);
			this.picBase.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picBase.TabIndex = 14;
			this.picBase.TabStop = false;
			// 
			// picUFO
			// 
			this.picUFO.Location = new System.Drawing.Point(664, 343);
			this.picUFO.Name = "picUFO";
			this.picUFO.Size = new System.Drawing.Size(32, 32);
			this.picUFO.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picUFO.TabIndex = 13;
			this.picUFO.TabStop = false;
			// 
			// picEnemy3
			// 
			this.picEnemy3.Location = new System.Drawing.Point(664, 381);
			this.picEnemy3.Name = "picEnemy3";
			this.picEnemy3.Size = new System.Drawing.Size(32, 32);
			this.picEnemy3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picEnemy3.TabIndex = 12;
			this.picEnemy3.TabStop = false;
			// 
			// picEnemy2
			// 
			this.picEnemy2.Location = new System.Drawing.Point(702, 381);
			this.picEnemy2.Name = "picEnemy2";
			this.picEnemy2.Size = new System.Drawing.Size(32, 32);
			this.picEnemy2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picEnemy2.TabIndex = 11;
			this.picEnemy2.TabStop = false;
			// 
			// picEnemy1
			// 
			this.picEnemy1.Location = new System.Drawing.Point(740, 381);
			this.picEnemy1.Name = "picEnemy1";
			this.picEnemy1.Size = new System.Drawing.Size(32, 32);
			this.picEnemy1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picEnemy1.TabIndex = 10;
			this.picEnemy1.TabStop = false;
			// 
			// picShield
			// 
			this.picShield.Location = new System.Drawing.Point(664, 229);
			this.picShield.Name = "picShield";
			this.picShield.Size = new System.Drawing.Size(32, 32);
			this.picShield.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picShield.TabIndex = 9;
			this.picShield.TabStop = false;
			// 
			// picSpeed
			// 
			this.picSpeed.Location = new System.Drawing.Point(664, 267);
			this.picSpeed.Name = "picSpeed";
			this.picSpeed.Size = new System.Drawing.Size(32, 32);
			this.picSpeed.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picSpeed.TabIndex = 8;
			this.picSpeed.TabStop = false;
			// 
			// picLife
			// 
			this.picLife.Location = new System.Drawing.Point(664, 305);
			this.picLife.Name = "picLife";
			this.picLife.Size = new System.Drawing.Size(32, 32);
			this.picLife.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picLife.TabIndex = 7;
			this.picLife.TabStop = false;
			// 
			// picAttack
			// 
			this.picAttack.Location = new System.Drawing.Point(664, 191);
			this.picAttack.Name = "picAttack";
			this.picAttack.Size = new System.Drawing.Size(32, 32);
			this.picAttack.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picAttack.TabIndex = 6;
			this.picAttack.TabStop = false;
			// 
			// lblInstructions
			// 
			this.lblInstructions.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblInstructions.Location = new System.Drawing.Point(13, 9);
			this.lblInstructions.Name = "lblInstructions";
			this.lblInstructions.Size = new System.Drawing.Size(775, 581);
			this.lblInstructions.TabIndex = 5;
			this.lblInstructions.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// grpScore
			// 
			this.grpScore.Controls.Add(this.lblScore);
			this.grpScore.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.grpScore.Location = new System.Drawing.Point(13, 607);
			this.grpScore.Name = "grpScore";
			this.grpScore.Size = new System.Drawing.Size(134, 50);
			this.grpScore.TabIndex = 1;
			this.grpScore.TabStop = false;
			this.grpScore.Text = "Score";
			// 
			// lblScore
			// 
			this.lblScore.AutoSize = true;
			this.lblScore.Location = new System.Drawing.Point(63, 22);
			this.lblScore.Name = "lblScore";
			this.lblScore.Size = new System.Drawing.Size(17, 18);
			this.lblScore.TabIndex = 0;
			this.lblScore.Text = "0";
			this.lblScore.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// grpHighScore
			// 
			this.grpHighScore.Controls.Add(this.lblHighScore);
			this.grpHighScore.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.grpHighScore.Location = new System.Drawing.Point(153, 607);
			this.grpHighScore.Name = "grpHighScore";
			this.grpHighScore.Size = new System.Drawing.Size(134, 50);
			this.grpHighScore.TabIndex = 2;
			this.grpHighScore.TabStop = false;
			this.grpHighScore.Text = "High Score";
			// 
			// lblHighScore
			// 
			this.lblHighScore.AutoSize = true;
			this.lblHighScore.Location = new System.Drawing.Point(62, 22);
			this.lblHighScore.Name = "lblHighScore";
			this.lblHighScore.Size = new System.Drawing.Size(17, 18);
			this.lblHighScore.TabIndex = 0;
			this.lblHighScore.Text = "0";
			this.lblHighScore.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// grpLives
			// 
			this.grpLives.Controls.Add(this.lblLives);
			this.grpLives.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.grpLives.Location = new System.Drawing.Point(293, 607);
			this.grpLives.Name = "grpLives";
			this.grpLives.Size = new System.Drawing.Size(134, 50);
			this.grpLives.TabIndex = 3;
			this.grpLives.TabStop = false;
			this.grpLives.Text = "Lives";
			// 
			// lblLives
			// 
			this.lblLives.AutoSize = true;
			this.lblLives.Location = new System.Drawing.Point(63, 22);
			this.lblLives.Name = "lblLives";
			this.lblLives.Size = new System.Drawing.Size(17, 18);
			this.lblLives.TabIndex = 0;
			this.lblLives.Text = "0";
			this.lblLives.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// btnNewGame
			// 
			this.btnNewGame.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnNewGame.Location = new System.Drawing.Point(573, 607);
			this.btnNewGame.Name = "btnNewGame";
			this.btnNewGame.Size = new System.Drawing.Size(217, 50);
			this.btnNewGame.TabIndex = 4;
			this.btnNewGame.Text = "New Game";
			this.btnNewGame.UseVisualStyleBackColor = true;
			this.btnNewGame.Click += new System.EventHandler(this.btnNewGame_Click);
			// 
			// timRefresh
			// 
			this.timRefresh.Interval = 17;
			this.timRefresh.Tick += new System.EventHandler(this.timRefresh_Tick);
			// 
			// grpDifficulty
			// 
			this.grpDifficulty.Controls.Add(this.lblDifficulty);
			this.grpDifficulty.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.grpDifficulty.Location = new System.Drawing.Point(433, 607);
			this.grpDifficulty.Name = "grpDifficulty";
			this.grpDifficulty.Size = new System.Drawing.Size(134, 50);
			this.grpDifficulty.TabIndex = 4;
			this.grpDifficulty.TabStop = false;
			this.grpDifficulty.Text = "Difficulty";
			// 
			// lblDifficulty
			// 
			this.lblDifficulty.AutoSize = true;
			this.lblDifficulty.Location = new System.Drawing.Point(63, 22);
			this.lblDifficulty.Name = "lblDifficulty";
			this.lblDifficulty.Size = new System.Drawing.Size(17, 18);
			this.lblDifficulty.TabIndex = 0;
			this.lblDifficulty.Text = "0";
			this.lblDifficulty.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 660);
			this.Controls.Add(this.grpDifficulty);
			this.Controls.Add(this.btnNewGame);
			this.Controls.Add(this.grpLives);
			this.Controls.Add(this.grpHighScore);
			this.Controls.Add(this.grpScore);
			this.Controls.Add(this.pnlView);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.KeyPreview = true;
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Nic\'s Space Invaders Variant";
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
			this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyUp);
			this.pnlView.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.picBase)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picUFO)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picEnemy3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picEnemy2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picEnemy1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picShield)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picSpeed)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picLife)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picAttack)).EndInit();
			this.grpScore.ResumeLayout(false);
			this.grpScore.PerformLayout();
			this.grpHighScore.ResumeLayout(false);
			this.grpHighScore.PerformLayout();
			this.grpLives.ResumeLayout(false);
			this.grpLives.PerformLayout();
			this.grpDifficulty.ResumeLayout(false);
			this.grpDifficulty.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Panel pnlView;
		private System.Windows.Forms.GroupBox grpScore;
		private System.Windows.Forms.Label lblScore;
		private System.Windows.Forms.GroupBox grpHighScore;
		private System.Windows.Forms.Label lblHighScore;
		private System.Windows.Forms.GroupBox grpLives;
		private System.Windows.Forms.Label lblLives;
		private System.Windows.Forms.Button btnNewGame;
		private System.Windows.Forms.Timer timRefresh;
		private System.Windows.Forms.GroupBox grpDifficulty;
		private System.Windows.Forms.Label lblDifficulty;
		private System.Windows.Forms.Label lblInstructions;
		private System.Windows.Forms.PictureBox picUFO;
		private System.Windows.Forms.PictureBox picEnemy3;
		private System.Windows.Forms.PictureBox picEnemy2;
		private System.Windows.Forms.PictureBox picEnemy1;
		private System.Windows.Forms.PictureBox picShield;
		private System.Windows.Forms.PictureBox picSpeed;
		private System.Windows.Forms.PictureBox picLife;
		private System.Windows.Forms.PictureBox picAttack;
		private System.Windows.Forms.PictureBox picBase;
	}
}

