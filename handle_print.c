#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @format:  Array of arguments formatted as a string.
 * @args: List of arguments to be printed.
 * @index: current index of the format string.
 * @buffer: Buffer array to handle print.
 * @flags: flags
 * @width: Field width.
 * @precision: Precision.
 * @length: Length modifier.
 * Return: 1 or 2;
 */
int handle_print(const char *format, int *index, va_list args, char buffer[],
int flags, int width, int precision, int length)
{
int j = 0, ret_len = 0;
conv_t fmt_types[] = {
{'c', print_char}, {'s', print_string}, {'%', print_percent},
{'i', print_int}, {'d', print_int}, {'b', print_binary},
{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
};
while (fmt_types[j].fmt != '\0')
{
if (format[*index] == fmt_types[j].fmt)
{
return (fmt_types[j].fn(args, buffer, flags, width, precision, length));
}
j++;
}
if (format[*index] == '\0')
{
return (-1);
}
ret_len += write(1, "%%", 1);
if (format[*index - 1] == ' ')
ret_len += write(1, " ", 1);
ret_len += write(1, &(format[*index]), 1);
return (ret_len);
}
