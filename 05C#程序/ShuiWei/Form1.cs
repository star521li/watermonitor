using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
//using System.Data;
using MySQLDriverCS;

namespace ShuiWei
{
    public partial class Form1 : Form
    {
        string str,st,std,stb;
        private Encoding Unicode;
        public Form1()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            for (int i = 1; i < 20; i++)
            {
                comboBox1.Items.Add("COM" + i.ToString());
            }
            comboBox1.Text = "COM1";
            comboBox2.Text = "9600";
            
            serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(port_DataReceived);
            //this.reportViewer1.RefreshReport();
            
        }
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

                System.Threading.Thread.Sleep(1500);//延时100ms等待接收完数据
                Int32 data;
                Int16 date;
                Int16 datc;
                
               
                date = (Int16)serialPort1.ReadByte();
                datc = (Int16)serialPort1.ReadByte();
               
                data = date * 256 + datc;
                str = Convert.ToString(data, 10);
                textBox1.Text = str + "cm";

                MySQLConnection myconn = null;
                myconn = new MySQLConnection(new MySQLConnectionString("localhost", "water", "root", "root", 3306).AsString);
                myconn.Open();  //打开连接
                string strSQL1 = "insert into waterinfor values(null,null,'zhangjiakou',"+str+")";
                MySQLCommand Command_1 = new MySQLCommand(strSQL1, myconn);
                Command_1.ExecuteNonQuery();//执行SQL命令插入
                          
        }
        private void SearchAndAddSerialToComboBox(SerialPort MyPort, ComboBox MyBox)
        {                                                              
            string Buffer;                                             
            MyBox.Items.Clear();                                       
            for (int i = 1; i < 20; i++)                               
            {
                try                                                   
                {
                    Buffer = "COM" + i.ToString();
                    MyPort.PortName = Buffer;
                    MyPort.Open();                                      

                    MyBox.Items.Add(Buffer);                         
                    MyPort.Close();                                     //关闭
                }
                catch
                {

                }
            }
        }
        private void WriteByteToSerialPort(byte data)                 
        {
            byte[] Buffer = new byte[1] { data };                      
            if (serialPort1.IsOpen)                                     
            {
                try
                {
                    serialPort1.Write(Buffer, 0, 1);                    
                }
                catch
                {
                    MessageBox.Show("串口数据发送出错，请检查.", "错误");//错误处理
                }
            }
        }
        //关闭串口
        private void button3_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            button2.Enabled = true;
            button3.Enabled = false;
        }
        //打开串口
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = comboBox1.Text;
                serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                serialPort1.Open();
                button2.Enabled = false;
                button3.Enabled = true;
            }
            catch
            {
                MessageBox.Show("串口错误，请检查串口");
            }
        }
        //扫描按钮
        private void button1_Click(object sender, EventArgs e)
        {
            SearchAndAddSerialToComboBox(serialPort1, comboBox1); 
        }
  
        //端口文本
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        //端口标签
        private void label1_Click(object sender, EventArgs e)
        {

        }
        //水位值标签
        private void label3_Click(object sender, EventArgs e)
        {

        }
        //显示表格
        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.listView1.Columns.Add("id");
            this.listView1.Columns.Add("时间");
            this.listView1.Columns.Add("地点");
            this.listView1.Columns.Add("水位值");
            this.listView1.View = System.Windows.Forms.View.Details;
        }
        //显示数据按钮
        private void button4_Click_1(object sender, EventArgs e)
        {     
            MySQLConnection myconn = null;
            myconn = new MySQLConnection(new MySQLConnectionString("localhost", "water", "root", "root", 3306).AsString);
          
            try {
                myconn.Open();  //打开连接
                MySQLCommand cmd = new MySQLCommand("select * from waterinfor", myconn);
               
                //cmd.ExecuteNonQuery();
                MySQLDataReader sdr = cmd.ExecuteReaderEx();
             
                while (sdr.Read())
                {
                    //构建一个ListView的数据，存入数据库数据，以便添加到listView1的行数据中
                    ListViewItem lt = new ListViewItem();
                    //将数据库数据转变成ListView类型的一行数据
                    lt.Text = sdr["id"].ToString();
                    lt.SubItems.Add(sdr["time"].ToString());
                    lt.SubItems.Add(sdr["place"].ToString());
                   // lt.SubItems.Add(sdr.GetString ( 2 ));                  
                    lt.SubItems.Add(sdr["value"].ToString());      
                   // Console.WriteLine(st);
                  //  Console.WriteLine(System.Text.Encoding.Default.EncodingName);
                    //将lt数据添加到listView1控件中
                    listView1.Items.Add(lt);
                }
                myconn.Close();
                sdr.Close();
            }
            catch {
                myconn.Close();
            }
        }
        
        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
        //波特率标签
        private void label2_Click(object sender, EventArgs e)
        {

        }
        //波特率文本
        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        //水位值文本
        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
 
    }
}
