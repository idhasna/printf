#include "main.h"

/**
 * write_char - writes the character .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  active flags calculated .
 * @width: the width .
 * @precision: specifies the precision .
 * @size: specifies the size .
 * Return: the number of characters printed .
 */
int write_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_print_char(c, buffer, flags, width, precision, size));
}
/**
 * write_string - writes the string .
 * @types: the list of arguments .
 * @buffer: the buffer array to be printed .
 * @flags:  the active flags calculated .
 * @width: the width.
 * @precision: the precision specification .
 * @size: the size specifier .
 * Return: the number of characters to be printed .
 */
int write_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & flag_minus)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/**
 * write_percent - writes the percent sign .
 * @types: the list of arguments .
 * @buffer: the buffer array to be printed .
 * @flags:  it calculates active flags .
 * @width: get the width.
 * @precision: the precision specification .
 * @size: the Size specification .
 * Return: the number of characters to be printed .
 */
int write_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * write_int - write the integer .
 * @types: the list of arguments .
 * @buffer: a buffer array for printing .
 * @flags:  calculating the active flags .
 * @width: get the width.
 * @precision: the precision specification .
 * @size: the size specifier .
 * Return: the number of characters to be printed .
 */
int write_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = conv_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (print_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * write_binary - writes an unsigned number .
 * @types: a list of the arguments .
 * @buffer: the buffer array for printing .
 * @flags:  active flags calculated .
 * @width: get the width .
 * @precision: the precision specifier .
 * @size: the size specification .
 * Return: the numbers of characters to be printed .
 */
int write_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
