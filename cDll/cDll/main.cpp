//#include "stdafx.h"
//#include "Windows.h"
//#using <system.dll>
using namespace System::Diagnostics;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Threading;
using namespace System::Collections::Generic;
#define EXTERN __declspec(dllexport)






namespace KoyjoyCLI
{

#pragma region CCallback ���
    public delegate void dlgt_WriteLine(String^ Str);
    public delegate void dlgt_Done();

    //Mother callback �Լ��� �����Ű���� ���� Ŭ������
    //NativeC��� ��Ȱ �ϵ��� static���� �������.
    //delegate ���� ���� ���� �ۼ� RiseEvent�� fnXXX �Լ� ȣ��� �̷������.
    public ref class CCallback  //delegate
    {
    protected:

    public:
        static event dlgt_WriteLine^ RiseEvent_fnWriteLine;
        static event dlgt_Done^ RiseEvent_fnDone;

        //mother ���� invoke�� ����ϸ� �������Ƿ� string�� �������ӿ� �ѹ��� �����ϵ��� ������Ų��.
        static List<String^>^ m_lstWriteLine = gcnew List<String^>(100);

        //1�����ӿ��� ���� ������ msg add
        //�̺�Ʈ�� �߻���Ű�� �ʴ´�.
        static void fnAddWriteLine(String^ str)
        {
            
            static int i = 0;
            i++;
            m_lstWriteLine->Add(i.ToString() + " "+ str);

            fnWriteLine(i.ToString() + " " + str);
        }


        static void fnWriteLine(String^ str)
        {
            RiseEvent_fnWriteLine(str);
        }

        static void fnDone()
        {
            //������ debugmsg�� ��Ƽ� �ѹ��� �����Ѵ�.
            String ^addStr;

            addStr = String::Join("\n", m_lstWriteLine->ToArray());
            m_lstWriteLine->Clear();

            fnWriteLine(addStr);

            RiseEvent_fnDone();
        }
    };
#pragma endregion


#pragma region Thread ���.
    public ref class CWorkThread
    {
    public :
        bool m_bEnable = false;

        void fnDoWork()
        {
            //CCallback^ cCallback = gcnew CCallback;
            m_bEnable = true;
            while (m_bEnable)
            {
                Thread::Sleep(10);                
                CCallback::fnAddWriteLine("Abcd1234567");
            }
        }

    };
    //NativeC ��� �°� ��� �ϵ��� static ���� ������Ŵ.
    static ref class CThreadMain
    {
        static CWorkThread^ m_cWorkthread;
        static ThreadStart^ m_threadDelegate;
        static Thread^ m_newThread;
    public:
        static void fnRun()
        {
            fnStop();       //thread �� �������� ��� ������ ��Ų��.

            m_cWorkthread = gcnew CWorkThread;
            m_threadDelegate = gcnew ThreadStart(m_cWorkthread, &CWorkThread::fnDoWork);
            m_newThread = gcnew Thread(m_threadDelegate);
            
            //m_newThread->Join();
            m_newThread->Start();
        }
        static void fnStop()
        {
            if (m_cWorkthread != nullptr)
            {
                m_cWorkthread->m_bEnable = false;

                m_cWorkthread = nullptr;
                m_threadDelegate= nullptr;
                m_newThread = nullptr;
            }
                
        }
    };
#pragma endregion

#pragma region NativeC ���.
    //class CCallback�� ����ϹǷ� ��ġ�� �Ʒ��� �־�� �Ѵ�.
    extern "C"
    {
        EXTERN void fnNative_main()
        {
            CCallback::fnWriteLine("abcdef");
            CCallback::fnDone();
        }

        EXTERN void fnNative_run()
        {
            CThreadMain::fnRun();
        }


        EXTERN void fnNative_stop()
        {
            CThreadMain::fnStop();
        }
    }
#pragma endregion
}