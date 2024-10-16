#include "tHandler.h"

#include <vector>
#include <cstdlib>
#include <csignal>
#include <unistd.h>

static std::vector<std::function<void()>> termTasks;
#if defined (__linux__)
static std::vector<std::function<void()>> suspTasks;
static std::vector<std::function<void()>> restTasks;
#endif

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

static void execute(const std::vector<std::function<void()>>& tasks){
	size_t size = tasks.size();
	for(size_t i = 0; i < size; ++i)
		tasks[i]();
}

static void terminate(int signal){
	execute(termTasks);
	exit(signal);
}

#if defined (__linux__)
static void suspend(int signal) {
    execute(suspTasks);
    std::signal(SIGTSTP, SIG_DFL);
    raise(SIGTSTP);
}

static void restore(int signal) {
	execute(restTasks);
	std::signal(SIGTSTP, suspend);
}
#endif

void thd::init(){
	std::signal(SIGINT, terminate);
#if defined (__linux__)
	std::signal(SIGTSTP, suspend);
    std::signal(SIGCONT, restore);
#endif
}
