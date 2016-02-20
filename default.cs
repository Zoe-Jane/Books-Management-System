using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string Name = textBox1.Text, Password = textBox2.Text, DB = System.IO.File.ReadAllText(@"logFile.dat");//读取文本框字符+读取密码储存文件
            int lengthDB = DB.Length, lengthName = Name.Length, lengthPassword = Password.Length, PasswordCnt = 0,Count=0;
            if (lengthPassword < 6 || lengthName < 3) { MessageBox.Show("用户名或密码错误，请重新输入！"); return; }//检查用户名密码长度
            int IDXname = DB.IndexOf(Name);//定位用户名位置
            if ((DB[IDXname + lengthName] != '#' || DB[IDXname + lengthName + lengthPassword + 1] != '*' )|| (IDXname == -1 || DB.IndexOf(Password) == -1)) 
            { MessageBox.Show("用户名或密码错误，请重新输入！"); return; }//检测是否找到用户名和密码，以及检查用户名和密码的长度
            for (; PasswordCnt < lengthPassword; )//遍历密码，将其与文件中的密码作对比
            {
                if(DB[IDXname + lengthName + PasswordCnt + 1]==Password[PasswordCnt])
                {
                    PasswordCnt++;
                    continue;
                }else
                    break;
            }
            if (PasswordCnt != lengthPassword) { MessageBox.Show("用户名或密码错误，请重新输入！"); return; }//对比密码长度
            if (Name == "admin")//检查是否管理员账户"admin"
            {
                StreamWriter sw = new StreamWriter("softwaretranspot.ini");//对softwaretranspot.ini写入11，使其可以把账户信息传给主程序，使其启动管理员模式
                string Authority = "11";
                sw.Write(Authority);
                sw.Close();
            }
            else
            {
                StreamWriter sw = new StreamWriter("softwaretranspot.ini");//对softwaretranspot.ini写入00，使其可以把账户信息传给主程序，使其启动普通用户模式
                string Authority = "00";
                sw.Write(Authority);
                sw.Close();
            }
            System.Diagnostics.Process p = new System.Diagnostics.Process();//启动主程序
            p.StartInfo.CreateNoWindow = true;
            p.StartInfo.FileName = "TGProm.exe";
            p.StartInfo.Arguments = @"cmdstr";
            p.Start();
            Application.ExitThread();//关闭登陆程序
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
