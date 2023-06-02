#include "main.h"

/**
 * get_size - determines the argument casted size .
 * @format: a formatted string for printing the arguments .
 * @i: the list of printed arguments .
 *
 * Return: the precision .
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = size_LONG;
	else if (format[curr_i] == 'h')
		size = size_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
