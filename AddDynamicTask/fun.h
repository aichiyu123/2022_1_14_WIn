#ifndef __FUN__H__ 
#define __FUN__H__
#include <vector>
#include <utility>
#include <future>
#include <queue>

class TaskInterface
{
	
public:

	TaskInterface(TaskInterface&) = delete;
	TaskInterface(const TaskInterface&) = delete;
	TaskInterface& operator = (const TaskInterface&) = delete; 

	template<typename T>
	TaskInterface(T&& f){p_exec = new Exec<T>(std::forward<T>(f));}
	TaskInterface(TaskInterface&& task) : p_exec(task.p_exec) {task.p_exec = nullptr;}
	TaskInterface& operator = (TaskInterface&& task)
	{
		delete p_exec;
		p_exec = task.p_exec;
		task.p_exec = nullptr;
		return *this;
	}
	
	~TaskInterface()
	{
		if(p_exec != nullptr)
		{
			delete p_exec;
			p_exec = nullptr;
		}
	}

	/*void operator()()
	{
		if(!p_exec)
		p_exec->call(); 
	}*/

	void Run()
	{
		if(p_exec)
		p_exec->call(); 
	}

private:
	
	struct BaseExec
	{
		virtual void call() = 0;
		virtual ~BaseExec() {}; 
	};
	
	template<typename T>
	struct Exec : BaseExec
	{
		T foo;
		Exec(T&& f) : foo(std::forward<T>(f)){}
		void call() override {foo();}		
	};

	struct BaseExec* p_exec = nullptr;

};

class Task1
{

public:
	Task1() {}
	~Task1() {}

	template<typename T>
	void Submit(T&& task)
	{
		//TaskInterface t1(std::forward<T>(task));
		//t1.Run();
		task_vec_.emplace(std::forward<T>(task));
		//TaskInterface t = std::move(task_vec_.front());
		//t.Run();
	}
	
	template<typename  T>
	auto RSubmit(T&& task) -> std::future<typename std::result_of<T()>::type>
	{
		using ret_type = typename std::result_of<T()>::type;
		std::packaged_task<ret_type()> pack(std::move(task));
		std::future<ret_type> ret_fut(pack.get_future());
		task_vec_.emplace(std::move(pack));
		return ret_fut;
	}

	void RunaAllTask()
	{
		size_t len = task_vec_.size();	
		for(size_t i = 0; i < len; i++)
		{
			auto t = std::move(task_vec_.front());
			t.Run();
			task_vec_.pop();
		}
	}

private:
	std::queue<TaskInterface> task_vec_;	
};


#endif
