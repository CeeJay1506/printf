#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - function that produces output according to a format.
 * @format: character string composed of zero or more directives.
 *
 * Return: characters printed excluding '\0'.
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	return (-1);

	va_start(list, format);

/*index, i starts from 0, conversion specifiers and the index of*/
/*the conversion specifier which is not the terminating byte if true*/
/*should be increased by one*/

	for (i = 0; format && format[i] != '\0'; i++)
	{
	if (format[i] != '%')
	{
	buffer[buff_ind++] = format[i];
	if (buff_ind == BUFF_SIZE)
	print_buffer(buffer, &buff_ind);

	/*write(1 & format[i], 1)*/
	printed_chars++;
	}
	else
	{
	print_buffer(buffer, &buff_ind);
	flags = get_flags(format, &i);
	width = get_width(format, &i, list);
	precision = get_precision(format, &i, list);
	size = get_size(format, &i);
	++i;
	printed = handle_print(format, &i, list, buffer,
		flags, width, precision, size);

	if (printed == -1)
	return (-1);

	printed_chars += printed;
	}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);
	return (printed_chars);
	}

/**
 * print_buffer - prints the content of the buffer if it exits
 * @buffer: array of characters
 * @buff_ind: index represents length
 */

void print_buffer(char buffer[], int *buff_ind)
/**function imitates _putchar function**/
{
	if (*buff_ind > 0)
	write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
	}
