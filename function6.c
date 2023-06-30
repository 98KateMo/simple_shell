#include "shell.h"

/**
 * err_no - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int err_no(const char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _perror - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: Nothing
 */
void _perror(const info_t *info, const char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	_dprint(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * _dprint - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int _dprint(int input, int fd)
{
	int (*putchar_func)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int i, count = 0;
	unsigned int abs_val, current;

	if (input < 0)
	{
		abs_val = (unsigned int)(-input);
		putchar_func('-');
		count++;
	}
	else
	{
		abs_val = (unsigned int)input;
	}
	current = abs_val;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_val / i)
		{
			putchar_func('0' + current / i);
			count++;
		}
		current %= i;
	}

	putchar_func('0' + current);
	count++;

	return (count);
}

/**
 * conv_int - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *conv_int(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = (unsigned long)((num < 0 && !(flags & TO_UNSIGNED)) ? -num : num);
	const char *array = (flags & TO_LOWER) ? "0123456789abcdef" : "0123456789ABCDEF";

	if (num < 0 && !(flags & TO_UNSIGNED))
		sign = '-';

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * rm_comm - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Nothing
 */
void rm_comm(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
