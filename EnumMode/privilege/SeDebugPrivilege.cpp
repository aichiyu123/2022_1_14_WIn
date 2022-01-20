#include <windows.h>
#include "SeDebugPrivilege.h"

bool __stdcall EnableDebugPrivilege
(
    
)
{
    HANDLE open_token_handle;
    BOOL   b_ret = true;
    if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&open_token_handle))
    {
        LUID luid;
        if(LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid))
        {
           TOKEN_PRIVILEGES new_token_privilege;
           new_token_privilege.PrivilegeCount = 1;
           new_token_privilege.Privileges[0].Luid = luid;
           new_token_privilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
           if(!AdjustTokenPrivileges
                                 (open_token_handle,
                                  false,
                                  &new_token_privilege,
                                  sizeof(new_token_privilege),
                                  NULL,
                                  NULL
                                  )
            )
           {
                b_ret = false;
           } 
        }
    }
    return b_ret;    
}