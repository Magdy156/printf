#include "main.h"
/**
 * write_number - prints a number
 * @is_negative: whether a - value exist.
 * @index: index.
 * @buffer: Buffer array.
 * @flags: flags.
 * @width: width.
 * @precision: precision.
 * @length: length modifier.
 * Return: Number of the printed characters.
 */
int write_number(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int length)
{
int size = BUFF_SIZE - index - 1;
char padd = ' ', ch = 0;
UNUSED(length);
if ((FZERO & flags) && !(FMINUS & flags))
padd = '0';
if (is_negative)
ch = '-';
else if (FPLUS & flags)
ch = '+';
else if (FSPACE & flags)
ch = ' ';
return (write_num(index, buffer, flags, width, precision,
size, padd, ch));
}
/**
 * handle_write_char - Prints a character.
 * @c: character.
 * @buffer: Buffer array.
 * @flags:  flags.
 * @width: width.
 * @precision: precision.
 * @length: length modifier.
 * Return: Number of the printed characters.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision,
	int length)
{
int i = 0;
char padd = ' ';
UNUSED(precision);
UNUSED(length);
buffer[1] = '\0';
if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
i = 0;
for (; i < width - 1; i++)
buffer[BUFF_SIZE - i - 2] = padd;
if (FMINUS & flags)
return (write(1, &c, 1) +
write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
write(1, &c, 1));
}
return (write(1, &c, 1));
}
/**
 * write_num - Write a number.
 * @index: Index.
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @precision: Precision specifier
 * @length: Number length
 * @padd: Padding
 * @post_c: Extra character
 * Return: Number of printed chars.
 */
int write_num(int index, char buffer[], int flags, int width,
	int precision, int length, char padd, char post_c)
{
int i = 1, padd_start = 1;
if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
{
if (width == 0)
return (0);
buffer[index] = padd = ' ';
}
if (precision > 0 && precision < length)
padd = ' ';
while (precision > length)
buffer[--index] = '0', length++;
if (post_c != 0)
length++;
if (width > length)
{
for (; i < width - length + 1; i++)
buffer[i] = padd;
buffer[i] = '\0';
if (flags & FMINUS && padd == ' ')
{
buffer = add_c(--index, buffer, post_c);
return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
}
else if (!(flags & FMINUS) && padd == ' ')
{
buffer = add_c(--index, buffer, post_c);
return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
}
else if (!(flags & FMINUS) && padd == '0')
{
buffer = add_c(--padd_start, buffer, post_c);
return (write(1, &buffer[padd_start], i - padd_start) +
	write(1, &buffer[index], length - (1 - padd_start)));
}
}
if (post_c)
buffer[--index] = post_c;
return (write(1, &buffer[index], length));
}
/**
 * write_pointer - Write an address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @post_c: Char representing extra char
 * @padd_start: Index at which padding should start
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char post_c, int padd_start)
{
int i;
if (width > length)
{
i = 3;
for (; i < width - length + 3; i++)
buffer[i] = padd;
buffer[i] = '\0';
if (flags & FMINUS && padd == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (post_c)
buffer[--ind] = post_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
}
else if (!(flags & FMINUS) && padd == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (post_c)
buffer[--ind] = post_c;
return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
}
else if (!(flags & FMINUS) && padd == '0')
{
if (post_c)
buffer[--padd_start] = post_c;
buffer[1] = '0';
buffer[2] = 'x';
return (write(1, &buffer[padd_start], i - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start) - 2));
}
}
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (post_c)
buffer[--ind] = post_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
/* The number is stored at the bufer's right and starts at position i */
int length = BUFF_SIZE - index - 1, i = 0;
char padd = ' ';
UNUSED(is_negative);
UNUSED(size);
if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
return (0);
while (precision > length)
{
buffer[--index] = '0';
length++;
}
if ((flags & FZERO) && !(flags & FMINUS))
padd = '0';
if (width > length)
{
for (i = 0; i < width - length; i++)
buffer[i] = padd;
buffer[i] = '\0';
if (flags & FMINUS)
{
return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
}
else
{
return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
}
}
return (write(1, &buffer[index], length));
}

