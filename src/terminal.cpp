#include "terminal.h"
#include <iostream>

#if defined (__linux__)
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#elif defined (_WIN32)
#include <windows.h>
#include <conio.h>
#endif

namespace ter{
#if defined (__linux__)
	struct termios oldSettings;
#elif defined (_WIN32)
	HANDLE hConsole;
#endif

#if defined (__linux__)
	//allows to receive characters without pressing the enter key.
	static void setInstantInputMode(bool enable){
		if(enable){
			struct termios newSettings = oldSettings;
			newSettings.c_lflag &= ~(ICANON | ECHO);
			tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
		}
		else{
			tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
		}
	}
#endif

#if defined (_WIN32)
	//allows the use of ANSI codes.
	static void enableVirtualTerminalProcessing(){
		DWORD mode;
		GetConsoleMode(hConsole, &mode);
		SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
	static void disableVirtualTerminalProcessing(){
		DWORD mode;
		GetConsoleMode(hConsole, &mode);
		SetConsoleMode(hConsole, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
#endif

	//enabling or disabling an alternative buffer.
	static void setAltBuf(bool enable){
		if(enable)
			std::cout << "\033[?1049h" << std::endl;
		else
			std::cout << "\033[?1049l" << std::endl;
	}

	//enabling or disabling cursor visibility.
	static void setCursorVisibility(bool enable){
		if(enable)
			std::cout << "\033[?25h" << std::endl;
		else
			std::cout << "\033[?25l" << std::endl;
	}

}

void ter::init(){
#if defined (__linux__)
	tcgetattr(STDIN_FILENO, &oldSettings);
#elif defined (_WIN32)
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

#if defined (__linux__)
void ter::setAltMode(bool enable){
	setInstantInputMode(enable);
	setAltBuf(enable);
	setCursorVisibility(!enable);
}
#elif defined (_WIN32)
void ter::setAltMode(bool enable){
	if(enable)
		enableVirtualTerminalProcessing();
	setAltBuf(enable);
	setCursorVisibility(!enable);
	if(!enable)
		disableVirtualTerminalProcessing();
}
#endif

#if defined (__linux__)
int ter::instantGetChar(){
	return getchar();
}
#elif defined (_WIN32)
int ter::instantGetChar(){
	return _getch();
}
#endif
void ter::setColor(Color color){
	std::cout << "\033[" << static_cast<int>(color) << 'm';
}
