#include "main.h"

/**
 * print_char - Prints a char
 * @args: the arguments
 * @buffer: string to be printed
 * @flags:  flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: printed chars
 */
int print_char(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(args, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string
 * @args: the arguments
 * @buffer: string
 * @flags:  flags
 * @width:  width
 * @precision: Precision
 * @size: Size
 * Return: printed string
 */
int print_string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (!str)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & FMINUS)
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

/**
 * print_percent - Prints a percent sign
 * @args: the arguments
 * @buffer: the string
 * @flags:  flags
 * @width: width.
 * @precision: Precision
 * @size: Size
 * Return: printed sign
 */
int print_percent(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * @args: the arguments
 * @buffer: the string
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: printed int
 */
int print_int(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an binary number
 * @args: the arguments
 * @buffer: the
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: printed binary num
 */
int print_binary(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int next, int_max, i, sum = 0;
	unsigned int arr[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	next = va_arg(args, unsigned int);
	int_max = 2147483648;
	arr[0] = next / int_max;
	for (i = 1; i < 32; i++)
	{
		int_max /= 2;
		arr[i] = (next / int_max) % 2;
	}
	for (i = 0, count = 0; i < 32; i++)
	{
		sum += arr[i];
		if (sum || i == 31)
		{
			char z = '0' + arr[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
