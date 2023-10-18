/**
 * _strncpy - Copy a string with a specified length.
 * @dest: Destination string to be copied to.
 * @src: Source string.
 * @n: The number of characters to copy.
 *
 * Return: The concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *s = dest;
	int i = 0;

	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return s;
}

/**
 * _strncat - Concatenate two strings with a specified length.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	char *s = dest;
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
		i++;

	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
		dest[i] = '\0';

	return s;
}

/**
 * _strchr - Locate a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area s, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return s;
		s++;
	} while (*s != '\0');

	return (NULL);
}
