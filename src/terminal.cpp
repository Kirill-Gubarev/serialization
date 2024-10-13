#include "terminal.h"
#include <iostream>

#if defined (__linux__)
#include <unistd.h>
#elif defined (_WIN32)
#include <conio.h>
#endif

ter::Terminal::Terminal(){
#if defined (__linux__)
	tcgetattr(STDIN_FILENO, &oldSettings);
#elif defined (_WIN32)
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

void ter::Terminal::setAltMode(bool state) const{
#if defined (__linux__)
	setInstantInputMode(state);
	setAltBuf(state);
	setCursorVisibility(!state);
#elif defined (_WIN32)
	if(state)
		enableVirtualTerminalProcessing();
	setAltBuf(state);
	setCursorVisibility(!state);
	if(!state)
		disableVirtualTerminalProcessing();
#endif
}

#if defined (__linux__)
void ter::Terminal::setInstantInputMode(bool state) const{
	if(state){
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
void ter::Terminal::enableVirtualTerminalProcessing() const{
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
void ter::Terminal::disableVirtualTerminalProcessing() const{
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif

void ter::Terminal::setAltBuf(bool state) const{
	if(state)
		std::cout << "\033[?1049h" << std::endl;
	else
		std::cout << "\033[?1049l" << std::endl;
}

void ter::Terminal::setCursorVisibility(bool state) const{
	if(state)
		std::cout << "\033[?25h" << std::endl;
	else
		std::cout << "\033[?25l" << std::endl;
}

#if defined (__linux__)
int ter::Terminal::instantGetChar() const{
	return getchar();
}
#elif defined (_WIN32)
int ter::Terminal::instantGetChar() const{
	return _getch();
}
#endif

void ter::Terminal::setColor(Color color) const{
	std::cout << "\033[" << static_cast<int>(color) << 'm';
}
