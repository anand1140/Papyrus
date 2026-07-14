#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>

struct papyrus_buf{
	char *b;
	int len;
};

void pbufFree(struct papyrus_buf *ab); 
void pbufAppend(struct papyrus_buf *ab, const char *p, int len); 
void die(const char *s);
void disableRawMode();
void enableRawMode(void);
int getWindowSize(int *rows, int *cols);
char editorReadKey();
void initEditor();
void editorProcessKeypress();
void editorRefreshScreen();

#define PAPYRUS_VARIENT "0.0.1"
#define PAPYRUS_BUF {NULL, 0}
//this produces the controle code for Ctrl-Q and then check it against
//the input read from terminal 
#define CTRL_KEY(k) ((k) & 0x1f)


//the struct for storing the original configurations 
struct termios orig_termios ;

/*** data ***/

//the struct to store the global state of the terminal window 
struct editorConfig {
	int cx, cy;
	int screenrows;
	int screencols;
	struct termios orig_termios;
};

struct editorConfig E;

/*** terminal ***/

//the function which handles dieng of our window 
void die(const char *s) {
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);

	perror(s);
	exit(1);
}

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
		die("tcsetattr");
}

void enableRawMode(void) {
	if ( tcgetattr(STDIN_FILENO , &E.orig_termios ) == -1 ) die("tcgetattr");
	atexit(disableRawMode);

	//below piece of code disables a lot of flags like for input output carriage retunr etc 
	struct termios raw = E.orig_termios ;
	raw.c_iflag &= ~(ICRNL | IXON | INPCK | ISTRIP | IXON) ;
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag &= (CS8);
	raw.c_lflag &= ~(ECHO | IEXTEN | ICANON | ISIG ) ;
	raw.c_cc[VMIN] = 0 ;
	raw.c_cc[VTIME] = 1;

	if ( tcsetattr(STDIN_FILENO , TCSAFLUSH , &raw ) == -1) die("tcsetattr");
}

//this waits for one keypress and return's it later
char editorReadKey() {
	int nread;
	char c;
	while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN) die ("read");
	}
	return c;
}

int getCursorPosition(int *rows, int *cols) {
	char buf[32];
	unsigned int i = 0;


	if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

	while( i < sizeof(buf) -1 ) {
		if(read(STDIN_FILENO, &buf[i], 1) != 1) break;
		if(buf[i] == 'R') break;
		i++;
	}
	buf[i] = '\0';
	
	if (buf[0] != '\x1b' || buf[1] != '[' ) return -1;
	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2 ) return -1;

	return -1;
}

//this method gets the window size and sets it in our struct names ws ;
//ws, ioctl(), TIOCGWIZSZ comes from ioctl.h 
int getWindowSize(int *rows, int *cols) {
	struct winsize ws;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
		if( write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
		return getCursorPosition(rows, cols);
	} else {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}

/*** input ***/
void editorMoveCursor(char key) {
	switch (key) {
		case 'h':
			if(E.cx > 0)
			E.cx--;
			break;
		case 'l':
			if(E.cx < E.screencols - 1)
			E.cx++;
			break;
		case 'k':
			if(E.cy > 0)
			E.cy--;
			break;
		case 'j':
			if(E.cy < E.screenrows - 1)
			E.cy++;
			break;
	} 
}

//waits for a keypress and then processes it
void editorProcessKeypress() {
	char c = editorReadKey();

	switch (c) {
		case CTRL_KEY('q'):
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;
		case 'j':
		case 'k':
		case 'h':
		case 'l':
			editorMoveCursor(c);
			break;
	}
}

/*** init ***/
void editorDrawRows(struct papurus_buf *ab) {
	int y;
	for ( y = 0; y < E.screenrows; y++) {
	if (y == E.screenrows / 3) {
		char welcome[80];
		int welcomelen = snprintf(welcome, sizeof(welcome), "Papyrus editor -- version %s this is my first editor and it's kinda cool isnt it oh how much i like it", PAPYRUS_VARIENT);

		if (welcomelen > E.screencols) welcomelen = E.screencols;
		int padding = (E.screencols - welcomelen) / 2;
		if (padding) {
			pbufAppend(ab, "~", 1);
			padding--;
		}

		while (padding--) pbufAppend(ab, " ", 1);
//this line below is buggy ,as welcomelen isn't the true length of the buffer
		pbufAppend(ab, welcome, welcomelen);
	} else {
		pbufAppend(ab,"~",1);
	}

	pbufAppend(ab, "\x1b[K", 3);
	if (y < E.screenrows -1) {
		pbufAppend(ab,"\r\n",2);
		}
	}
}

void editorRefreshScreen() {
	struct papyrus_buf ab = PAPYRUS_BUF;	

	pbufAppend(&ab,"\x1b[?25l", 4);
	pbufAppend(&ab,"\x1b[H", 3);
	
	editorDrawRows(&ab);

	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
	pbufAppend(&ab,buf, strlen(buf));

	pbufAppend(&ab,"\x1b[?25H", 6);
	
	write(STDOUT_FILENO, ab.b, ab.len);
	pbufFree(&ab);
}
 
/*** init ***/

void initEditor() {
	E.cx = 0;
	E.cy = 0;
	if(getWindowSize(&E.screenrows, &E.screencols) == -1) 
		die("getWindowSize");
}

/*** append buffer ***/



void pbufAppend(struct papyrus_buf *ab, const char *p, int len) {
	char *new = realloc(ab->b, ab->len+len);

	if(new == NULL) return;
	memcpy(&new[ab->len], p, len);
	ab->b = new;
	ab->len += len;
}

void pbufFree(struct papyrus_buf *ab) {
	free(ab->b);
}

int main() {
	enableRawMode() ;
	initEditor();

	while (1) {
		editorRefreshScreen();
		editorProcessKeypress();
		}

	return 0 ;

}
