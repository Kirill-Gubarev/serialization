#ifndef TERMINAL_H
#define TERMINAL_H

namespace ter{
	//reset the terminal settings
	void setAltTerminal(bool state);

#if defined (__linux__)
	//allows to receive characters without pressing the enter key.
	void setInstantInputMode(bool state);
#endif

#if defined (_WIN32)
	//allows the use of ANSI codes.
	void setVirtualTerminalProcessing(bool state);
#endif

	//enabling or disabling an alternative buffer.
	void setAltBuf(bool state);

	//enabling or disabling cursor visibility.
	void setCursorVisibility(bool state);

	//get a character without pressing the enter key.
	int instantGetChar();
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

	void setColor(Color color);
}

#endif//TERMINAL_H
