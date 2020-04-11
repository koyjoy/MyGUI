using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using u8 = System.Byte;
using s8 = System.SByte;
using u16 = System.UInt16;
using s16 = System.Int16;
using u32 = System.UInt32;
using s32 = System.Int32;
using u64 = System.UInt64;
using s64 = System.Int64;

namespace WindowsFormsApp1
{        
    public partial class frmMain : Form
    {

        [DllImport("cDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void fnNative_run();

        [DllImport("cDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void fnNative_stop();

        [DllImport("cDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void fnNative_main();

        public frmMain()
        {
            InitializeComponent();

            //CCallback 클래스는 모두 static 으로 만들었다.
            //static CCallback 클래스의 static RiseEvent_fnWriteLine 가 발생하는 놈을
            //구독 하라고 현재 사용중의 클래스의 mehtode 를 등록 시킨다.
            KoyjoyCLI.CCallback.RiseEvent_fnWriteLine +=
                new KoyjoyCLI.dlgt_WriteLine(EventCli_fnWriteLine);

            KoyjoyCLI.CCallback.RiseEvent_fnDone +=
                new KoyjoyCLI.dlgt_Done(EventCli_fnDone);

        }

        public void EventCli_fnWriteLine(string str)
        {
            //Debug.WriteLine(str);
            this.Invoke(new MethodInvoker(
                     delegate ()
                     {
                         richTextBox1.Text = string.Format(str) + richTextBox1.Text;
                     }
                )
            );
        }

        int m_i = 0;
        public void EventCli_fnDone()
        {

            this.Invoke(new MethodInvoker(
                     delegate ()
                     {
                         richTextBox1.Text = string.Format("Done:" + m_i.ToString()+"\n") + richTextBox1.Text;
                         Debug.WriteLine("Done:" + m_i.ToString());
                         
                     }
                )
            );
        }

        private void btnNativeMain_Click(object sender, EventArgs e)
        {
            fnNative_main();
        }

        private void btnThreadRun_Click(object sender, EventArgs e)
        {
            fnNative_run();            
        }

        private void btnThreadstop_Click(object sender, EventArgs e)
        {
            fnNative_stop();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            //종료시 cli 쓰레드를 마무리 시킨다.
            fnNative_stop();
        }
    }
}
