#include "main.h"

/**
 * get_flags - Calculates flags
 * @format: string
 * @i: input
 * Return: Flags
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_i = *i + 1;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	while (format[curr_i] != '\0')
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_i] == FLAGS_CH[j])
			{
				flags = flags | FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
		curr_i++;
	}

	*i = curr_i - 1;

	return (flags);
}
