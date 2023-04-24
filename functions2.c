#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @args: the arguments
 * @buffer: the string
 * @flags:  flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: pinter
 */
int print_pointer(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @args: the arguments
 * @buffer: the string
 * @flags:  flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: printed ascii
 */
int print_non_printable(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(args, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @args: the arguments
 * @buffer: the string
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: printed reversed string
 */

int print_reverse(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int length, sum = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);

	str = va_arg(args, char *);

	if (str)
	{
	for (length = 0; *str; str++)
		length++;

	for (length = length - 1; length > 0; length--)
	{
		char z = str[length];

		write(1, &z, 1);
		sum++;
	}
	}
	return (sum);
}

/**
 * print_rot13string - Print a string in rot13(rotate)
 * @args: the arguments
 * @buffer: th string
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: printed string
 */
int print_rot13string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i = 0, j;
	int count = 0;
	char arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char rot[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);


	while (str[i])
	{
		for (j = 0; arr[j]; j++)
		{
			if (arr[j] == str[i])
			{
				x = rot[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!arr[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
		i++;
	}
	return (count);
}
