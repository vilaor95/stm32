#include <stddef.h>
#include <stdbool.h>

#include "usart.h"

enum fd_e {
	FD_IN,
	FD_OUT,
	FD_ERR,
};

int _write(int fd, char* ptr, int len)
{
	(void)fd, (void)ptr, (void)len;

	if (fd == FD_OUT) usart_write_buf(USART2, ptr, (size_t)len);
	return -1;
}

int _read(int fd, char* ptr, int len)
{
	(void)fd, (void)ptr, (void)len;
	return -1;
}

int _fstat(int fd, int ptr)
{
	(void)fd, (void)ptr;
	return -1;
}

int _close(int fd)
{
	(void)fd;
	return -1;
}

int _lseek(int fd, int ptr, int dir)
{
	(void)fd, (void)ptr, (void)dir;
	return 0;
}

extern void *_end;
void* _sbrk(int increment)
{
	static unsigned char *heap = NULL;
	unsigned char *prev_heap;

	if (heap == NULL)
	{
		heap = (unsigned char*)&_end;
	}
	prev_heap = heap;

	heap += increment;

	return prev_heap;
}

int _isatty(int fd)
{
	(void)fd;
	return 1;
}
