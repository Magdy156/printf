#include "main.h"
/**
 * get_size - indicate the size of the argument.
 * @format: Array of arguments formatted as a string.
 * @index: current index of the format string.
 * Return: length modifier.
 */
int get_size(const char *format, int *index)
{
int lenght = 0;
if (format[*index + 1] == 'l')
lenght = 2;
else if (format[*index + 1] == 'h')
lenght = 1;
if (lenght)
*index += 1;
return (lenght);
}
