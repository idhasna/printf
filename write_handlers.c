#include "main.h"

/**
 * handle_print_char - writes the string .
 * @c: the type of characters .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @width: get the width .
 * @precision: the precision specification .
 * @size: the size specification .
 *
 * Return: the number of characters to be  printed.
 */
int handle_print_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and padding at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & flag_zero)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUF_SIZE - i - 2] = padd;

		if (flags & flag_minus)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}
/**
 * print_number - writes the string .
 * @is_negative: the list of arguments .
 * @ind: the character types .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 *
 * Return: the number of characters to be printed.
 */
int print_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & flag_zero) && !(flags & flag_minus))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & flag_plus)
		extra_ch = '+';
	else if (flags & flag_space)
		extra_ch = ' ';

	return (print_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * print_num - it prints the buffer used by the number .
 * @ind: the index at which the number begins on the buffer .
 * @buffer: the buffer .
 * @flags: the flags .
 * @width: the width .
 * @prec: the precision specification .
 * @length: the length of the number .
 * @padd: the character padded .
 * @extra_c: an extra character .
 *
 * Return: the number of printed characters.
 */
int print_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & flag_minus && padd == ' ')/* extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & flag_minus) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & flag_minus) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * print_unsigned - prints the unsigned number .
 * @is_negative: the number specifying if the number is negative .
 * @ind: an index at which the number begins in the buffer .
 * @buffer: the array of characters .
 * @flags: the flags specification .
 * @width: the width specification .
 * @precision: the precision specification .
 * @size: the size specification .
 *
 * Return: the number of the characters written .
 */
int print_unsigned(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position i */
	int length = BUF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & flag_zero) && !(flags & flag_minus))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & flag_minus) /* Assign extra char to of buffer’s left [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * print_pointer - prints address of the memory .
 * @buffer: the arrays of characters .
 * @ind: the index at which the number begins in the buffer .
 * @length: the length of the number .
 * @width: the width specification .
 * @flags: the flags specification .
 * @padd: the padding represented by the character .
 * @extra_c: the extra character represented by the character .
 * @padd_start: the index at which padding may begins .
 *
 * Return: the number of written characters .
 */
int print_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & flag_minus && padd == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & flag_minus) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & flag_minus) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUF_SIZE - ind - 1));
}
