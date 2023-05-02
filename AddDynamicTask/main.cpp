#include <functional>
#include <string>
#include <stdio.h>
#include "fun.h"

void Fun1()
{
	printf("HelloWorld Fun1\r\n");
}

void Fun2(std::string& str_mes, int index)
{	
	printf("HelloWorld Fun2 Mes:%s index:%d\r\n", str_mes.c_str(), index);
}

int Fun3(int index)
{
	return index + 1;
}


int main()
{
	Task1 t;
	t.Submit(Fun1);
	std::string str_msg = "MyStr";
	int index = 0;	
	//auto Fun2Ex = std::bind(Fun2, std::placeholders::_1, std::placeholders::_2);
	auto Fun2Ex = std::bind(Fun2, std::ref(str_msg), index);
	t.Submit(Fun2Ex);
	t.Submit([str_msg, index]{printf("HelloWorld Mes:%s index:%d\r\n", str_msg.c_str(), index);});
	auto r1 = t.RSubmit([index]{return index + 1;});
	auto Fun3Ex = std::bind(Fun3, 1);
	auto r2 = t.RSubmit(Fun3Ex);
	t.RunaAllTask();
	r1.wait();
	r2.wait();
	printf("r1 %d\nr2 %d\n", r1.get(), r2.get());
	return 0;
}
