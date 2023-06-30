#include "shell.h"

/**
 * _eputs - prints a string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(const char *str)
{
	if (str != NULL)
		write(2, str, _strlen(str));
}

/**
 * _eputchar - writes a character to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	return (write(2, &c, 1));
}

/**
 * _put_fdesc - writes a character to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _put_fdesc(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
 * _puts_fdesc - prints a string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _puts_fdesc(const char *str, int fd)
{
	if (str != NULL)
		return (write(fd, str, _strlen(str)));
	return (0);
}
