#include "terminal.h"

#ifdef __linux__
	#include <stdio.h>
    #include <termios.h>
    #include <unistd.h>

	static struct termios newt;
	static struct termios oldt;

	void setNewTerSet(){	
        tcgetattr(STDIN_FILENO, &oldt);           
        newt = oldt;                              
        newt.c_lflag &= ~(ICANON | ECHO);         
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
	}
	void setOldTerSet(){
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
	}
    int getOneChar() {
       return getchar();
    }
#elif defined(_WIN32)
    #include <conio.h>
	void setNewTerSet(){}
	void setOldTerSet(){}
	int getOneChar(){
		return _getch();
	}
#else
	#error "there is no implementation of getOneChar();"
#endif
