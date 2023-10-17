#include "shell.h"

/**
 * isInteractive - Checks if the shell is in interactive mode.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int isInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delimiters: The delimiter string.
 *
 * Return: 1 if it is a delimiter, 0 if not.
 */
int isDelimiter(char c, char *delimiters)
{
	int i;

	for (i = 0; delimiters[i] != '\0'; i++)
	{
		if (delimiters[i] == c)
			return (1);
	}

	return (0);
}

/**
 * isAlphabetic - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is an alphabetic character, 0 otherwise.
 */
int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * stringToInteger - Converts a string to an integer.
 * @inputString: The string to be converted.
 *
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int stringToInteger(char *inputString)
{
	int index, sign = 1, flag = 0, result;
	unsigned int convertedValue = 0;

	for (index = 0; inputString[index] != '\0' && flag != 2; index++)
	{
		if (inputString[index] == '-')
			sign *= -1;

		if (inputString[index] >= '0' && inputString[index] <= '9')
		{
			flag = 1;
			convertedValue *= 10;
			convertedValue += (inputString[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -convertedValue;
	else
		result = convertedValue;

	return (result);
}
