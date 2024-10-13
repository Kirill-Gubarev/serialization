#include "terminal.h"
#include <iostream>

#if defined (__linux__)
#include <termios.h>
#include <unistd.h>
#elif defined (_WIN32)
#include <conio.h>
#include <windows.h>
#endif

#if defined (__linux__)
static struct termios oldt;
#elif defined (_WIN32)
static HANDLE hConsole;
#endif

void ter::setAltTerminal(bool state){
	if(state){
#if defined (_WIN32)
		setVirtualTerminalProcessing(true);
#endif
		ter::setAltBuf(true);
#if defined (__linux__)
		ter::setInstantInputMode(true);
#endif
		ter::setCursorVisibility(false);
	}
	else{
		ter::setCursorVisibility(true);
#if defined (__linux__)
		ter::setInstantInputMode(false);
#endif
		ter::setAltBuf(false);
#if defined (_WIN32)
		setVirtualTerminalProcessing(false);
#endif
	}
}

#if defined (__linux__)
void ter::setInstantInputMode(bool state){
	if(state){
		tcgetattr(STDIN_FILENO, &oldt);
		struct termios newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}
	else{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
}
#endif

#if defined (_WIN32)
void ter::setVirtualTerminalProcessing(bool state){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);

	if(state)
		SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	else
		SetConsoleMode(hConsole, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif

void ter::setAltBuf(bool state){
	if(state)
		std::cout << "\033[?1049h" << std::endl;
	else
		std::cout << "\033[?1049l" << std::endl;
}

void ter::setCursorVisibility(bool state){
	if(state)
		std::cout << "\033[?25h" << std::endl;
	else
		std::cout << "\033[?25l" << std::endl;
}

#if defined (__linux__)
int ter::instantGetChar(){
	return getchar();
}
#elif defined (_WIN32)
int ter::instantGetChar(){
	return _getch();
}
#endif

void ter::setColor(ter::Color color){
	std::cout << "\033[" << static_cast<int>(color) << 'm';
}
