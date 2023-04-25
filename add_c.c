#include "main.h"
/**
 * add_c - assign character to the buffer.
 * @index: Index.
 * @buffer: Buffer
 * @post_c: Extra character
 * Return: Buffer
 */
char *add_c(int *index, char buffer[], char post_c)
{
if (post_c)
buffer[--*index] = post_c;
return (buffer);
}
