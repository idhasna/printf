#include "main.h"

/**
 * _isprintable - rates if a character is able to be printed .
 * @c: character to be rated .
 *
 * Return: 1 if c is printable, 0 if not .
 */
int _isprintable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - appending ASCII in hexadecimal code to the buffer .
 * @buffer: an array of characters .
 * @i: the index at which to begin appending .
 * @ascii_code: the ASCII code .
 * Return: at all times 3 .
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * _isdigit - confirmed if the character is a digit .
 * @c: the character to be rated .
 *
 * Return: 1 if c is a digit, 0 otherwise .
 */
int _isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * conv_size_number - it casts the number for the designated size .
 * @num: the casted number .
 * @size: the number specifying the casted type .
 *
 * Return: a casted value of the number .
 */
long int conv_size_number(long int num, int size)
{
	if (size == size_LONG)
		return (num);
	else if (size == size_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * conv_size_unsigned - it casts the number for the designated size .
 * @num: the casted number .
 * @size: the number specifying the casted type .
 *
 * Return: the casted value of the number .
 */
long int conv_size_unsigned(unsigned long int num, int size)
{
	if (size == size_LONG)
		return (num);
	else if (size == size_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
