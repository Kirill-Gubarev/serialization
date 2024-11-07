#include "tHandler.h"

#include <vector>
#include <cstdlib>
#include <csignal>
#include <unistd.h>

namespace thd{
	static std::vector<std::function<void()>> termTasks;
	static void execute(const std::vector<std::function<void()>>& tasks);
	static void terminate(int signal);
#if defined (__linux__)
	static std::vector<std::function<void()>> suspTasks;
	static std::vector<std::function<void()>> restTasks;
	static void suspend(int signal);
	static void restore(int signal);
#endif
}

void thd::init(){
	std::signal(SIGINT, terminate);
#if defined (__linux__)
	std::signal(SIGTSTP, suspend);
    std::signal(SIGCONT, restore);
#endif
}
void thd::addTermination(const std::function<void()>& func){
	termTasks.push_back(func);
}
void thd::addSuspension(const std::function<void()>& func){
#if defined (__linux__)
	suspTasks.push_back(func);
#endif
}
void thd::addRestoration(const std::function<void()>& func){
#if defined (__linux__)
	restTasks.push_back(func);
#endif
}

void thd::execute(const std::vector<std::function<void()>>& tasks){
	size_t size = tasks.size();
	for(size_t i = 0; i < size; ++i)
		tasks[i]();
}
void thd::terminate(int signal){
	execute(termTasks);
	exit(signal);
}

#if defined (__linux__)
void thd::suspend(int signal) {
    execute(suspTasks);
    std::signal(SIGTSTP, SIG_DFL);
    raise(SIGTSTP);
}
void thd::restore(int signal) {
	execute(restTasks);
	std::signal(SIGTSTP, suspend);
}
#endif

