#ifndef TERMINAL_H
#define TERMINAL_H

#if defined (__linux__)
#include <termios.h>
#elif defined (_WIN32)
#include <windows.h>
#endif

namespace ter{
	enum class Color{
		reset	= 0,
		reverse = 7,
		fred	= 31,
		fgreen	= 32,
		fyellow	= 33,
		fblue	= 34,
		fpurple	= 35,
		fcyan	= 36,
		fwhite	= 37,
		bred	= 41,
		bgreen	= 42,
		byellow	= 43,
		bblue	= 44,
		bpurple	= 45,
		bcyan	= 46,
		bwhite	= 47
	};

	class Terminal{
	private:
#if defined (__linux__)
		struct termios oldSettings;

		//allows to receive characters without pressing the enter key.
		void setInstantInputMode(bool state) const;
#elif defined (_WIN32)
		HANDLE hConsole;

		//allows the use of ANSI codes.
		void enableVirtualTerminalProcessing() const;
		void disableVirtualTerminalProcessing() const;
#endif
		//enabling or disabling an alternative buffer.
		void setAltBuf(bool state) const;
		//enabling or disabling cursor visibility.
		void setCursorVisibility(bool state) const;
	public:
		Terminal();
		void setAltMode(bool state) const;
		void setColor(Color color) const;
		//get a character without pressing the enter key.
		int instantGetChar() const;
	};
}

#endif//TERMINAL_H
