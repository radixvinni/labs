using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Graf
{
    public partial class Dialog1 : Form
    {
        public int dA=-1, dB=-1, dC=-1, dD=-1;
        public int grafn;

        public Dialog1()
        {
            InitializeComponent();
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            dA = this.comboBox1.SelectedIndex;
            dB = this.comboBox2.SelectedIndex;
            dC = this.comboBox3.SelectedIndex;
            //dD = this.comboBox4.SelectedIndex;
            this.Hide();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void dialog1_Shown(object sender, EventArgs e)
        {
            this.comboBox1.Items.Clear();
            this.comboBox2.Items.Clear();
            this.comboBox3.Items.Clear();
            //this.comboBox4.Items.Clear();
 
            for(int j=0;j<grafn;j++)
			 {
				 this.comboBox1.Items.Add(Convert.ToString(j));
				 this.comboBox2.Items.Add(Convert.ToString(j));
				 this.comboBox3.Items.Add(Convert.ToString(j));
				 //this.comboBox4.Items.Add(Convert.ToString(j));				 
			 }

        }
    }
}
