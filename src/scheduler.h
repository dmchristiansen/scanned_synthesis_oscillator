/*
 * scheduler.h
 *
 * Simple task queue implementation
 *
 */

struct task_t {
	void (*acton)(void*);
	void* arg;
};

class taskQueue {
	private:
		uint8_t maxTasks;
		task_t* 
	public:
		taskQueue();
		initialize();
		addTask();
		freeTask();
}

