#include "terminal.h"

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
	//enabling or disabling an alternative buffer.
	static void setAltBuf(bool enable);
	//enabling or disabling cursor visibility.
	static void setCursorVisibility(bool enable);

#if defined (__linux__)
	struct termios oldSettings;

	//allows to receive characters without pressing the enter key.
	static void setInstantInputMode(bool enable);
	//enabling or disabling an alternative buffer.
	static void setAltBuf(bool enable);
	//enabling or disabling cursor visibility.
	static void setCursorVisibility(bool enable);
#elif defined (_WIN32)
	HANDLE hConsole;

	//allows the use of ANSI codes.
	static void enableVirtualTerminalProcessing();
	static void disableVirtualTerminalProcessing();
#endif

}

#if defined (__linux__)
void ter::init(){
	tcgetattr(STDIN_FILENO, &oldSettings);
}
void ter::setAltMode(bool enable){
	setInstantInputMode(enable);
	setAltBuf(enable);
	setCursorVisibility(!enable);
}
void ter::setCursorPos(int x, int y){
	std::cout << "\033[" << y << ';' << x << 'H' << std::flush;
}
int ter::instantGetChar(){
	return getchar();
}

void ter::setInstantInputMode(bool enable){
	if(enable){
		struct termios newSettings = oldSettings;
		newSettings.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
	}
	else{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
	}
}
#elif defined (_WIN32)
void ter::init(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
void ter::setAltMode(bool enable){
	if(enable)
		enableVirtualTerminalProcessing();
	setAltBuf(enable);
	setCursorVisibility(!enable);
	if(!enable)
		disableVirtualTerminalProcessing();
}
void ter::setCursorPos(int x, int y){
	COORD pos = {static_cast<short>(x), static_cast<short>(y)};
    SetConsoleCursorPosition(hConsole, pos);
}
int ter::instantGetChar(){
	return _getch();
}

void ter::enableVirtualTerminalProcessing(){
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
void ter::disableVirtualTerminalProcessing(){
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif

void ter::clear(){
	std::cout << "\033[2J" << std::flush;
}
std::ostream& ter::operator<<(std::ostream& io, const Color color){
	return io << "\033[" << static_cast<int>(color) << 'm';
}
void ter::setAltBuf(bool enable){
	if(enable)
		std::cout << "\033[?1049h" << std::flush;
	else
		std::cout << "\033[?1049l" << std::flush;
}
void ter::setCursorVisibility(bool enable){
	if(enable)
		std::cout << "\033[?25h" << std::flush;
	else
		std::cout << "\033[?25l" << std::flush;
}
