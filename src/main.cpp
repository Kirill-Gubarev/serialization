#include "gui.h"
#include "terminal.h"
#include <csignal>
#include <unistd.h>

//reset the terminal settings at the external termination of the program
void exTermination(int signal){
	ter::setAltTerminal(false);
	exit(signal);
}

#if defined (__linux__)
void handleStopSignal(int signal) {
    ter::setAltTerminal(false);
    std::signal(SIGTSTP, SIG_DFL);  // Временно восстанавливаем стандартное поведение для SIGTSTP
    raise(SIGTSTP);                 // Отправляем себе сигнал SIGTSTP, чтобы приостановиться
}

void handleContinueSignal(int signal) {
    ter::setAltTerminal(true);
	std::signal(SIGTSTP, handleStopSignal); // Повторно устанавливаем обработчик для SIGTSTP   ter::setAltTerminal(true);
}
#endif
int main(int argc, char* argv[]){
	std::signal(SIGINT, exTermination);    // Обработка Ctrl + C
#if defined (__linux__)
	std::signal(SIGTSTP, handleStopSignal); // Обработка Ctrl + Z
    std::signal(SIGCONT, handleContinueSignal);
#endif
	gui::GUI gui;
	gui.main_loop();

    return 0;
}
