#include "main.h"
/**
 * is_digit - check if a character is a digit
 * @charac: Character
 * Return: 1 if charac is a digit, 0 otherwise
 */
int is_digit(char charac)
{
if (charac <= '9' && charac >= '0')
return (1);
return (0);
}
/**
 * is_printable - check if a char is printable
 * @charac: Character.
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char charac)
{
if (charac < 127 && charac >= 32)
return (1);
return (0);
}
/**
 * convert_size_unsgnd - casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
if (size == SLONG)
return (num);
else if (size == SSHORT)
return ((unsigned short)num);
return ((unsigned int)num);
}
/**
 * append_hexa_code - Append ascci in hexadecimal code
 * @buffer: Array of characters.
 * @index: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int index)
{
char map_to[] = "0123456789ABCDEF";
if (ascii_code < 0)
ascii_code *= -1;
buffer[index++] = '\\';
buffer[index++] = 'x';
buffer[index++] = map_to[ascii_code / 16];
buffer[index] = map_to[ascii_code % 16];
return (3);
}
/**
 * convert_size_number - cast a number to a specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 * Return: Casted of num
 */
long int convert_size_number(long int num, int size)
{
if (size == SLONG)
return (num);
else if (size == SSHORT)
return ((short)num);
return ((int)num);
}
