//#define _POSIX_C_SOURCE 200112L
//#define _DARWIN_C_SOURCE


#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct termios orig_termios ;

void disableRawMode() {
	tcsetattr(STDIN_FILENO , TCSAFLUSH , &orig_termios ) ;
}

void enableRawMode(void) {

	tcgetattr(STDIN_FILENO , &orig_termios );
	atexit(disableRawMode);

	//below piece of code disables a lot of flags like for input output carriage retunr etc 
	struct termios raw = orig_termios ;
	raw.c_iflag &= ~(ICRNL | IXON) ;
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | IEXTEN | ICANON | ISIG ) ;

	tcsetattr(STDIN_FILENO , TCSAFLUSH , &raw );
}


int main(void) {
	
	enableRawMode() ;
	char c;


	while ( read(STDIN_FILENO ,&c , 1 ) == 1 && c != 'q' ) {
	if (iscntrl(c)) {
		printf("%d\n",c);
	}else {
		printf("%d ('%c')\r\n" , c ,c );
	}
	}

	return 0 ;

}
