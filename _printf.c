#include "main.h"

/**
 * print_buffer - Prints String
 * @buffer: string to be printed
 * @length: no of chars that will be printed from the string
 */
void print_buffer(char buffer[], int *length)
{
	if (*length > 0)
		write(1, &buffer[0], *length);

	*length = 0;
}

/**
 * _printf - produces output according to a format
 * @format: format
 * Return: string
 */
int _printf(const char *format, ...)
{
	int i = 0, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list args;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, args, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
		i++;
	}
	print_buffer(buffer, &buff_ind);
	va_end(args);
	return (printed_chars);
}
