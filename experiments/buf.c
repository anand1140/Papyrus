#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Buffer {
	char* b;
	size_t len;
};

void append(struct Buffer* buf, const char* ab, size_t length) {
	char* new = realloc(buf->b,buf->len + length);

	if(new != NULL) {
		buf->b = new;
	} else return;
	new += buf->len;
	memcpy(new, ab, length);
	buf->len += length;
}


int main() {
	char buf[100] = "Hello\nWorld\n";
	// printf("%s",buf);

	const char *name = "Anand\n";
	

	// printf("%lu",strlen(buf));
	// printf("%lu",strlen(name));

	write(STDOUT_FILENO, buf, strlen(buf));
	write(STDOUT_FILENO, name, strlen(name));

	return 0;
}
