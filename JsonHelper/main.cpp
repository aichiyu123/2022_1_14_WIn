#include <stdio.h>
#include <string>
#include "json.h"


int main()
{
	json_helper::JsonHelper js1(rapidjson::kObjectType);
	std::pair<std::string, std::string> data_pair1 = {"hello1", "world"};
	std::pair<std::string, int> data_pair2 = {"hello2", 1};
	std::pair<std::string, double> data_pair3 = {"hello3", 1.22};
	std::pair<std::string, bool> data_pair4 = {"hello4", false};
	js1.AddRef(data_pair1.first, data_pair1.second);
	js1.Add(data_pair1.first, data_pair1.second);
	js1.Add(data_pair2.first, data_pair2.second);
	js1.Add(data_pair3.first, data_pair3.second);
	js1.Add(data_pair4.first, data_pair4.second);
	
	std::string str_ret;
	js1.ToString(str_ret);
	printf("js1:%s\r\n", str_ret.c_str());
		
	json_helper::JsonHelper js2(rapidjson::kArrayType);
	js2.Push(1);	
	js2.Push(2);
	js2.Push(3);
	std::string str = "MyStr";
	js2.PushCopy(str);	
	
	str_ret;
	js2.ToString(str_ret);
	printf("js2:%s\r\n", str_ret.c_str());

	std::string str_arr = "arr";
	js1.Add(str_arr, js2.GetDoc());
	js1.ToString(str_ret);
	printf("js1js2:%s\r\n", str_ret.c_str());

	js2.Push(js1.GetDoc());
	js2.ToString(str_ret);
	printf("js2js1:%s\r\n", str_ret.c_str());
	return 0;
}
