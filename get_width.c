#include "main.h"
/**
 * get_width - specify the minimum number of characterst to be printed.
 * @format: Array of arguments formatted as a string.
 * @index: current index of the format string.
 * @args: arguments list.
 * Return: Field width.
 */
int get_width(const char *format, int *index, va_list args)
{
int current = *index + 1;
int width_field = 0;
while (format[current] != '\0')
{
if (is_digit(format[current]))
{
width_field *= 10;
width_field += format[current] - '0';
}
else if (format[current] == '*')
{
current++;
width_field = va_arg(args, int);
break;
}
else
break;
current++;
}
*index = current - 1;
return (width_field);
}
