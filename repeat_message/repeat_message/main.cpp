#ifdef _WIN32
#include <Windows.h>
#endif

#include <thread>

#include "../hook/hook_helper.h"
#include "debug.h"

typedef bool (__stdcall *PRegisterKeyboardEvent)(KeyInfoStruct*);
typedef bool (__stdcall *PUnRegisterKeyboardEvent)();


bool is_start_send_message = false;
bool is_kill = false;

void __stdcall KeyCallBack(KeyEnum key_num)
{
    Debug("KeyNum:%d", key_num);
    switch(key_num)
    {
        case NUMBER_F2:
        {
            is_start_send_message = true;
            break;
        }
        case NUMBER_F3:
        {
            is_start_send_message = false;
            break;
        }
        case NUMBER_F4:
        {
            is_kill = true;
            break;
        }
    }
}

void SendCtrlAndVEvent()
{
#ifdef _WIN32
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x56, 0, 0, 0);
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
#endif 
}

void SendEnterEvent()
{
#ifdef _WIN32
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
#endif
}

#ifdef _WIN32
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
#else 
int main()
#endif
{
	PRegisterKeyboardEvent p_key = nullptr;
	PUnRegisterKeyboardEvent p_unkey = nullptr;
#ifdef _WIN32
    HMODULE hook_handle = LoadLibrary("hooks.dll");
	if (hook_handle == NULL)
	{
		Debug("LoadLibraryError Code:%d\r\n", GetLastError());
		return 0;
	}

	p_key = (PRegisterKeyboardEvent)GetProcAddress(hook_handle, "RegisterKeyboardEvent");
	p_unkey = (PUnRegisterKeyboardEvent)GetProcAddress(hook_handle, "UnRegisterKeyboardEvent");
	if (p_key == NULL || p_unkey == NULL)
	{
		Debug("GetInterfaceError EventStatus:%p HookStatus:%p Code:%d", p_key, p_unkey, GetLastError());
		FreeLibrary(hook_handle);
		hook_handle = 0x0;
		return 0;
	}
#endif
    int* p_key_arr = new(std::nothrow) int[4];
    if(p_key_arr == nullptr)
    {
        Debug("MallocIsNULL");
        return 0;
    }
    
    *p_key_arr       = KeyEnum::NUMBER_F2;
    *(p_key_arr + 1) = KeyEnum::NUMBER_F3;
    *(p_key_arr + 2) = KeyEnum::NUMBER_F4;
    *(p_key_arr + 3) = KeyEnum::NUMBER_A;

    KeyInfoStruct key_info;
    key_info.call = KeyCallBack;
    key_info.p_find_key = p_key_arr;
    key_info.find_key_len = 4;

    if(!p_key(&key_info))
    {
        Debug("RegisterKeyError");
        if(p_key_arr)
        {
            delete[] p_key_arr;
            p_key_arr = nullptr;
        }
        return 0;
    }
    
    bool is_one = true;
    while (!is_kill)
	{
		if (is_start_send_message)
		{
            if(!is_one)
            {
			    SendCtrlAndVEvent();
            }
			SendEnterEvent();
            is_one = false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

    if(!p_unkey())
    {
        Debug("RegisterUnKeyError");
        //return 0;
    }
    if(p_key_arr)
    {
        delete[] p_key_arr;
        p_key_arr = nullptr;
    }    
    return 0;
}
