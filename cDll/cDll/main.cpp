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

#pragma region CCallback 기술
    public delegate void dlgt_WriteLine(String^ Str);
    public delegate void dlgt_Done();

    //Mother callback 함수를 실행시키도록 만든 클래스로
    //NativeC운영에 원활 하도록 static으로 만들었다.
    //delegate 독립 실행 으로 작성 RiseEvent를 fnXXX 함수 호출로 이루어진다.
    public ref class CCallback  //delegate
    {
    protected:

    public:
        static event dlgt_WriteLine^ RiseEvent_fnWriteLine;
        static event dlgt_Done^ RiseEvent_fnDone;

        //mother 에서 invoke를 사용하면 느려지므로 string을 한프레임에 한번만 전송하도록 누적시킨다.
        static List<String^>^ m_lstWriteLine = gcnew List<String^>(100);

        //1프레임에서 실행 누적할 msg add
        //이벤트는 발생시키지 않는다.
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
            //누적된 debugmsg를 모아서 한번에 전송한다.
            String ^addStr;

            addStr = String::Join("\n", m_lstWriteLine->ToArray());
            m_lstWriteLine->Clear();

            fnWriteLine(addStr);

            RiseEvent_fnDone();
        }
    };
#pragma endregion


#pragma region Thread 기술.
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
    //NativeC 운영에 맞게 사용 하도록 static 으로 구성시킴.
    static ref class CThreadMain
    {
        static CWorkThread^ m_cWorkthread;
        static ThreadStart^ m_threadDelegate;
        static Thread^ m_newThread;
    public:
        static void fnRun()
        {
            fnStop();       //thread 가 실행중일 경우 중지를 시킨다.

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

#pragma region NativeC 기술.
    //class CCallback을 사용하므로 위치가 아래에 있어야 한다.
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