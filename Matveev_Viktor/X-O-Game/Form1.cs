using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Крестики_Нолики
{
    public partial class Form1 : Form
    {
        private int x = 12, y = 13;
        private Button[,] buttons = new Button[3,3];
        private int player;
        public Form1()
        {
            InitializeComponent();
            this.Height = 600;
            this.Width = 900;
            player = 1;
            label1.Text = "Current step: player 1";
            for (int i = 0; i < buttons.Length / 3; i++)
            {
                for (int j = 0; j < buttons.Length / 3; j++)
                {
                    buttons[i, j] = new Button();
                    buttons[i, j].Size = new Size(100,100);
                }
            }
            setButtons();
        }

        private void setButtons()
        {
            for (int i = 0; i < buttons.Length / 3; i++)
            {
                for (int j = 0; j < buttons.Length / 3; j++)
                {
                    buttons[i, j].Location = new Point(13 + 108 * j, 12 + 106 * i);
                    buttons[i, j].Click += button1_Click;
                    buttons[i, j].Font = new Font(new FontFamily("Microsoft Sans Serif"), 50);
                    this.Controls.Add(buttons[i, j]);
                }
            }   
                    
        } 

        private void button1_Click(object sender, EventArgs e)
        {
            switch(player){

                case 1:
                    sender.GetType().GetProperty("Text").SetValue(sender, "X");
                    player = 0;
                    label1.Text = "Current step: player 2";
                    break;
                case 0:
                    sender.GetType().GetProperty("Text").SetValue(sender, "O");
                    player = 1;
                    label1.Text = "Current step: player 1";
                    break;

            }
            sender.GetType().GetProperty("Enabled").SetValue(sender, false);
            checkwin();
        }
        private void checkwin()
        {
            if (buttons[0, 0].Text == buttons[0, 1].Text && buttons[0, 1].Text == buttons[0, 2].Text)
            {
                if (buttons[0, 0].Text != "")
                {
                MessageBox.Show("You WIN!");
                    return;
                }
            }
            if (buttons[1, 0].Text == buttons[1, 1].Text && buttons[1, 1].Text == buttons[1, 2].Text)
            {
                if (buttons[1, 0].Text != "")
                    MessageBox.Show("You WIN!");
            }
            if (buttons[2, 0].Text == buttons[2, 1].Text && buttons[2, 1].Text == buttons[2, 2].Text)
            {
                if (buttons[2, 0].Text != "")
                    MessageBox.Show("You WIN!");
            }
            if (buttons[0, 0].Text == buttons[1, 0].Text && buttons[1, 0].Text == buttons[2, 0].Text)
            {
                if (buttons[0, 0].Text != "")
                    MessageBox.Show("You WIN!");
            }
            if (buttons[0, 1].Text == buttons[1, 1].Text && buttons[1, 1].Text == buttons[2, 1].Text)
            {
                if (buttons[0, 1].Text != "")
                    MessageBox.Show("You WIN!");
            }
            if (buttons[0, 2].Text == buttons[1, 2].Text && buttons[1, 2].Text == buttons[2, 2].Text)
            {
                if (buttons[0, 2].Text != "")
                    MessageBox.Show("You WIN!");
            }
            if (buttons[0, 0].Text == buttons[1, 1].Text && buttons[1, 1].Text == buttons[2, 2].Text)
            {
                if (buttons[0, 0].Text != "")
                    MessageBox.Show("You WIN!");
            }
            if (buttons[0, 2].Text == buttons[1, 1].Text && buttons[1, 1].Text == buttons[2, 0].Text)
            {
                if (buttons[0, 2].Text != "")
                    MessageBox.Show("You WIN!");
            }
        }

        private void buttonPlay_Click(object sender, EventArgs e)
        {
            for (int i=0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    buttons[i, j].Text = "";
                    buttons[i, j].Enabled = true;
                }
            }
        }
    }
}
