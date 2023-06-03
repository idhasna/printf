#include "main.h"

/**
 * print_unsigned - writes an unsigned number .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the active flags .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the number of characters printed .
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = conv_size_unsigned(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (print_unsign(0, i, buffer, flags, width, precision, size));
}

/**
 * write_octal - writes an unsigned number in octal .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the number of printed characters .
 */
int write_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = conv_size_unsigned(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & flag_hashtag && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (print_unsign(0, i, buffer, flags, width, precision, size));
}

/**
 * write_hexa - writes an unsigned number in hexadecimal .
 * @types: the list of arguments .
 * @buffer: a buffer array to print .
 * @flags:  it calculates active flags .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: a number of printed charcters .
 */
int write_hexa(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (write_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * write_Hexa - writes an unsigned number in upper hexadecimal .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @width: get width
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the number of printed characters .
 */
int write_Hexa(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (write_Hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * write_heXa - writes a hexadecimal number in lower or upper notations .
 * @types: the list of arguments .
 * @map_to: an array of values for mapping the number to .
 * @buffer: a buffer array for printing .
 * @flags:  it calculates the flags activated .
 * @flag_ch: Calculating flags activated .
 * @width: get the width
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the number of printed characters .
 */
int write_heXa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = conv_size_unsigned(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & flag_hashtag && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (print_unsign(0, i, buffer, flags, width, precision, size));
}
