#include <unordered_set>

#ifdef _WIN32
#include<Windows.h>

HHOOK  keyboardll_handle = nullptr;
HANDLE init_hook_thread_handle = nullptr;
DWORD  init_hook_thread_id = 0;

#else 

#ifndef BOOL
using BOOL = int;
#endif 

#endif

#include "hook_helper.h"
#include "../repeat_message/debug.h"

KeyInfoStruct* extern_keyboard_info = nullptr;

#ifndef _WIN32

static __attribute__((constructor)) void Befor()
{
	
}	

#else 
BOOL WINAPI DllMain(HANDLE instance, ULONG reason, LPVOID reserved)
 {
    switch (reason) 
    {
        case DLL_PROCESS_ATTACH:
            //dll_instance = (HINSTANCE)instance;
            return TRUE;
        case DLL_PROCESS_DETACH:
            return TRUE;
        case DLL_THREAD_DETACH:
            return TRUE;
        default:
            return TRUE;
    };
}

LRESULT CALLBACK KeyboardCallBack(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode == HC_ACTION && wParam == WM_KEYUP)
    {
        std::unordered_set<KeyEnum> set_key = 
        {
            NUMBER_0, NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9,
            NUMBER_F1, NUMBER_F2, NUMBER_F3, NUMBER_F4, NUMBER_F5, NUMBER_F6, NUMBER_F7, NUMBER_F8, NUMBER_F9, NUMBER_F10, NUMBER_F11, NUMBER_F12,
            NUMBER_A, NUMBER_B, NUMBER_C, NUMBER_D, NUMBER_E, NUMBER_F, NUMBER_G, NUMBER_H, NUMBER_I,  NUMBER_J,
            NUMBER_K, NUMBER_L, NUMBER_M, NUMBER_N, NUMBER_O, NUMBER_P, NUMBER_Q, NUMBER_R, NUMBER_S,
            NUMBER_T, NUMBER_U, NUMBER_V, NUMBER_W, NUMBER_X, NUMBER_Y, NUMBER_Z
        };        
        if(extern_keyboard_info && extern_keyboard_info->find_key_len)
        {
            for(int i =0; i < extern_keyboard_info->find_key_len; i++)
            {
                KeyEnum enum_key = (KeyEnum)((KBDLLHOOKSTRUCT*)lParam)->vkCode;
                if(extern_keyboard_info->p_find_key[i] == enum_key)
                {
                    extern_keyboard_info->call(enum_key);
                    break;                    
                }
            }
        }
        else if(extern_keyboard_info && set_key.find((KeyEnum)((KBDLLHOOKSTRUCT*)lParam)->vkCode) != set_key.end()) 
        {
            KeyEnum enum_key = (KeyEnum)((KBDLLHOOKSTRUCT*)lParam)->vkCode;
            extern_keyboard_info->call(enum_key);            
        }
    }
    return CallNextHookEx(keyboardll_handle, nCode, wParam, lParam);
}

#endif

void InitHookThread()
{
#ifdef _WIN32
    keyboardll_handle = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardCallBack, NULL, 0);
    if(!keyboardll_handle)
    {
        return;
    }
    MSG msg = {};
   	while (GetMessageA(&msg, NULL, 0, 0) > 0)
    {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
#endif 
}


bool  RegisterKeyboardEvent(KeyInfoStruct* p_key_info_struct)
{
    if(!p_key_info_struct)
    {
        return false;
    }

    extern_keyboard_info = p_key_info_struct;

#ifdef _WIN32
    init_hook_thread_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitHookThread, NULL, 0, &init_hook_thread_id);
    if(!init_hook_thread_handle)
    {
        return false;
    }
#endif
    return true;
}

bool  UnRegisterKeyboardEvent()
{
#ifdef _WIN32
    if(!init_hook_thread_id || !init_hook_thread_handle)
    {
        return false;
    }

    if(!UnhookWindowsHookEx(keyboardll_handle))
    {
       return false;        
    }
    CloseHandle(keyboardll_handle);
    keyboardll_handle = nullptr;
    PostThreadMessage(init_hook_thread_id, WM_QUIT, NULL, NULL);
    WaitForSingleObject(init_hook_thread_handle, INFINITE);
    CloseHandle(init_hook_thread_handle);
    init_hook_thread_handle = nullptr;
    init_hook_thread_id = 0;
#endif
    return true;
}
