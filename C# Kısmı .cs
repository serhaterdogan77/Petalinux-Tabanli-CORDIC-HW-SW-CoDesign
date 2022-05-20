using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
            serialPort1.BaudRate = 9600;
            serialPort1.PortName = "COM6";

            serialPort1.Open();

        }


        private void button1(object sender, EventArgs e)
        {
            string message;
            message;= textBox1.Text;

            serialPort1.WriteLine(message;);
        }


        private void serialPort1_Data(object sender, System.IO.Ports.SerialDataEventArgs e)
        {
            string data = serialPort1.ReadExisting();
            if (richTextBox1.InvokeRequired)
            {
                richTextBox1.Invoke(new MethodInvoker(delegate { richTextBox1.Text += data + "\r\n"; }));
            }

        }

    }

}