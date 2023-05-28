#include "main.h"

void print_buffer(char buffer[], int *buff_i);

/**
 * _printf - function that produces output according to a format.
 * @format: character string composed of zero or more directives.
 *
 * Return: the number of characters printed excluding '\0'.
 */

int _printf(const char *format, ...)
{
	va_list ap;
	int i, print_ = 0, print_chars = 0;
	int flags, width, precision, size, buff_i = 0;
	char buffer[BUFSIZE];

	if (format == NULL)
	return (-1);

	va_start(ap, format);

/*index, i starts from 0, conversion specifiers and the index of*/
/*the conversion specifier which is not the terminating byte if true*/
/*should be increased by one*/

	for (i = 0; format && format[i] != '\0'; i++)
	{
	if (format[i] != '%')
	{
	buffer[buff_i++] = format[i];
	if (buff_i == BUFSIZE)
	print_buffer(buffer, &buff_i);

	/*write(1 & format[i], 1)*/
	print_chars++;
	}
	else
	{
	print_buffer(buffer, &buff_i);
	flags = get_flags(format, &i);
	width = get_width(format, &i, ap);
	precision = get_precision(format, &i, ap);
	size = get_size(format, &i);
	++i;
	print_ = handle_print(format, &i, ap, buffer, flags, width, precision, size);

	if (print_ == -1)
	return (-1);

	print_chars += print_;
	}
	}

	print_buffer(buffer, &buff_i);

	va_end(ap);
	return (print_chars);
	}

/**
 * print_buffer - prints the content of the buffer if it exits
 * @buffer: array of characters
 * @buff_i: index length
 */

void print_buffer(char buffer[], int *buff_i)
/**function imitates _putchar function**/
{
	if (*buff_i > 0)
	write(1, &buffer[0], *buff_i);

	*buff_i = 0;
	}
