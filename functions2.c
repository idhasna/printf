#include "main.h"

/**
 * print_pointer - writes the value of a pointer  .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the number of printed characters .
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & flag_sero) && !(flags & flag_minus))
		padd = '0';
	if (flags & flag_plus)
		extra_c = '+', length++;
	else if (flags & flag_space)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - writes ASCII codes in hexa for non printable chars .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the number of printed characters .
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - writes the string reversed .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the numbers of printed characters .
 */

int print_rev(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}


/**
 * print_rot13 - writes a string in rot13 .
 * @types: the list of arguments .
 * @buffer: Buffer array to handle print
 * @flags:  it calculates the flags activated .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the numbers of printed characters .
 */
int print_rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
