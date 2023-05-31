#include "main.h"

	/***PRINT A CHARACTER***/

/*
 * print_char - prints a character
 * @type: list 'a' of arguments
 * @buffer: buffer array
 * @flags: Calculates active flags
 * @width: width
 * @precision: Precision specification
 * @size: size
 *
 * Return: number of characters printed
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
	}

	/***PRINT A STRING***/
/**
 * print_string - prints a string
 * @types: list 'a' of arguments
 * @buffer: buffer array
 * @flags: calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 *
 * Return: number of characters printed
 */

int print_string(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(width);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
		str = "       ";
	}

	while (str[length] != '\0')
	length++;

	if (precision >= 0 && precision < length)
	length = precision;
	if (length >= 13);
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
			write(1, " ", 1);
			return (width);
		}
		else
		{
		for (i = width - length; i > 0; i--)
		write(1, " ", 1);
		write(1, &str[0], length);
		return (width);
		}
	}
	return (write(1, str, length));
	}

/**PRINT PERCENTAGE SIGN**/

/**
 * print_percent - prints a percentage sign
 * @types: list 'a' of arguments
 * @buffer: buffer array
 * @flags: calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size
 *
 * Return: number of characters printed
 */

int print_percent(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

		/***PRINT AN INTEGER***/

/**
 * print_int - print integer
 * @types: list 'a' of arguments
 * @buffer: buffer array
 * @flags: calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size
 * Return: number of characters printed
 */

int print_int(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int _negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);
	if (n == 0)
	buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
	num = (unsigned long int)((-1) * n);
	_negative = 1;
	}
	while (num > 0)
	{
	buffer[i--] = (num % 10) + '0';
	num /= 10;
	}
	i++;

	return (write_number(_negative, i, buffer, flags, width, precision, size));
	}

		/****PRINT BINARY****/

/**
 * print_binary - prints an unsigned number
 * @types: List 'a' of arguments
 * @buffer: buffer array
 * @flags: calc active flags
 * @width: width
 * @precision: precision specification
 * @size: size:
 *
 * Return: Number of characters printed
 */

int print_binary(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	unsigned int x, y, i, sum;
	unsigned int m[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648;
	/*(2 ^ 31)*, 2 raised to the power 31*/

	m[0] = x / y;
	for (i = 1; i < 32; i++)
	{
	y /= 2;
	m[i] = (x / y) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
	sum += m[i];
	if (sum || i == 31)
	{
	char z = '0' + m[i];

	write(1, &z, 1);
	count++;
	}
	}
	return (count);
	}
