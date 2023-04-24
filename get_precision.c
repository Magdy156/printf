#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: string
 * @i: input
 * @args: the arguments
 * Return: Precision
 */
int get_precision(const char *format, int *i, va_list args)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
		return (precision);

	precision = 0;
	curr_i += 1;

	while (format[curr_i] != '\0')
	{
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
		curr_i++;
	}

	*i = curr_i - 1;

	return (precision);
}

