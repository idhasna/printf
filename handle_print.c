#include "main.h"
/**
 * handle_print - writes the argument depending on its type .
 * @fmt: a formatted string for printing the arguments .
 * @list: the list of printed arguments .
 * @ind: the ind .
 * @buffer: a buffer array for managing print .
 * @flags: it calculates the flags activated .
 * @width: Get  the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', write_char}, {'s', write_string}, {'%', write_percent},
		{'i', print_num}, {'d', write_int}, {'b', write_binary},
		{'u', write_unsigned}, {'o', write_octal}, {'x', write_hexad},
		{'X', write_Hexa}, {'p', write_pointer}, {'S', write_non_printable},
		{'r', write_rev}, {'R', write_rot13}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fun(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
