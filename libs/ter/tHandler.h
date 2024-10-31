#ifndef THANDLER_H
#define THANDLER_H

#include <functional>

//termination handler
namespace thd{
	void init();
	void addTermination(const std::function<void()>& func);
	void addSuspension(const std::function<void()>& func);
	void addRestoration(const std::function<void()>& func);
}

#endif//THANDLER_H
