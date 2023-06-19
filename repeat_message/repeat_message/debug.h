#include <stdarg.h>
#include <string>
#include <mutex>
#include <thread>
#include <fstream>
#include <sstream>
#define Debug(...)               OutPutDebugView(__FUNCTION__, __LINE__, __VA_ARGS__)


#ifdef MODE_NAME

#define MODULE_NAME MODE_NAME

#else 

#define MODULE_NAME "default"

#endif

#define MAX_BUFF 1024 * 3

inline void GetTimeStr(std::string& time_str)
{
	time_t tt;
	time(&tt);
	tt = tt + 8 * 3600;
	tm* t = gmtime(&tt);
	char tmp[64] = { 0 };
	snprintf(tmp, 64, "%d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec);
	time_str = tmp;
}


static void OutPutDebugView(const char* p_function_name, int now_line, const char* p_format, ...)
{
    static std::mutex print_mutex;
    va_list arg_list;
    va_start(arg_list, p_format);
    char buff[MAX_BUFF];
    vsnprintf(buff, MAX_BUFF, p_format, arg_list);
    va_end(arg_list);

    std::string times_str;
    GetTimeStr(times_str);

    std::unique_lock<std::mutex> lock(print_mutex);
		std::ostringstream tid;
		tid << std::this_thread::get_id();
    std::string log_str = "[" + times_str + "][";
    log_str += p_function_name;
    log_str += "][";
    log_str += std::to_string(now_line);
    log_str += "][";
    log_str += MODULE_NAME;
    log_str += "][";
    log_str += tid.str();
    log_str += "][";
    log_str += buff;
    log_str += "]\r\n";
#ifdef _WIN32
	OutputDebugStringA(log_str.c_str());
#else
	// linux out /var/log
	static std::string path = (std::string)"/var/log/" + MODULE_NAME; 	
	static std::ofstream out_stream(path, std::ios::binary);
	out_stream << log_str;

#endif

}
