#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#define UNUSED(x) ((void)x)
#define BUF_SIZE 1024


/* FLAGS */
#define flag_minus 1
#define flag_plus 2
#define flag_zero 4
#define flag_hashtag 8
#define flag_space 16

/* SIZES */
#define size_LONG 2
#define size_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fun: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fun)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);


/* Functions to print chars and strings */
int write_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int write_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int write_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int write_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int write_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int write_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int write_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int write_hexa(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int write_Hexa(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int write_heXa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int write_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Function to print memory address */
int write_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*Function to print string in reverse*/
int write_rev(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int write_rot13(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int handle_print_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int print_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int print_num(int ind, char buffer[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int print_pointer(char buffer[], int ind, int length, int width,
	int flags, char padd, char extra_c, int padd_start);
int print_unsign(int is_negative, int ind,
char buffer[], int flags, int width, int precision, int size);

/* utils */
int _isprintable(char);
int append_hexa_code(char, char[], int);
int _isdigit(char);

long int conv_size_number(long int num, int size);
long int conv_size_unsigned(unsigned long int num, int size);

#endif
