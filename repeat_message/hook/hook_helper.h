#ifndef __HOOK__HELPER__H__
#define __HOOK__HELPER__H__

#ifdef _WIN32
#define EXPORT __declspec(dllexport) 
#else
#ifndef EXPORT 
#define EXPORT
#endif
#ifndef __stdcall
#define  __stdcall __attribute__((stdcall))
#endif 
#endif

#ifndef START_EXTERNC 
#define START_EXTERNC extern "C"{
#endif 
#ifndef END_EXTERNC 
#define END_EXTERNC }
#endif 

#define KEY_INFO 
enum KeyEnum \
{ \
    NUMBER_0 = 0x30, NUMBER_1 = 0x31, NUMBER_2 = 0x32, NUMBER_3 = 0x33, NUMBER_4 = 0x34, NUMBER_5 = 0x35, NUMBER_6 = 0x36, NUMBER_7 = 0x37, NUMBER_8 = 0x38, NUMBER_9 = 0x39, \
    NUMBER_F1 = 0x70, NUMBER_F2 = 0x71, NUMBER_F3 = 0x72, NUMBER_F4 = 0x73, NUMBER_F5 = 0x74, NUMBER_F6 = 0x75, NUMBER_F7 = 0x76, NUMBER_F8 = 0x77, NUMBER_F9 = 0x78, NUMBER_F10 = 0x79, NUMBER_F11 = 0x7A, NUMBER_F12 = 0x7B, \
    NUMBER_A = 0x41, NUMBER_B = 0x42, NUMBER_C = 0x43, NUMBER_D = 0x44, NUMBER_E = 0x45, NUMBER_F = 0x46, NUMBER_G = 0x47, NUMBER_H = 0x48, NUMBER_I = 0x49,  NUMBER_J = 0x4A, \
    NUMBER_K = 0x4B, NUMBER_L = 0x4C, NUMBER_M = 0x4D, NUMBER_N = 0x4E, NUMBER_O = 0x4F, NUMBER_P = 0x50, NUMBER_Q = 0x51, NUMBER_R = 0x52, NUMBER_S = 0x53, \
    NUMBER_T = 0x54, NUMBER_U = 0x55, NUMBER_V = 0x56, NUMBER_W = 0x57, NUMBER_X = 0x58, NUMBER_Y = 0x59, NUMBER_Z = 0x5A \
}; \
typedef void(__stdcall *PKeyEventCall)(KeyEnum); \
struct KeyInfoStruct \
{ \
    PKeyEventCall call;\
    int *p_find_key; \
    int find_key_len; \
};


START_EXTERNC
EXPORT bool RegisterKeyboardEvent(KeyInfoStruct *p_key_info_struct);
EXPORT bool UnRegisterKeyboardEvent();
END_EXTERNC

#endif
