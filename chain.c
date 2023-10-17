#include "shell.h"

/**
 * is_chain - Check if the current character is a chain delimiter.
 * @info: Parameter struct.
 * @buf: Character buffer.
 * @p: Address of current position.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	while (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	while (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	while (buf[j] == ';') /* End of this command */
	{
		buf[j] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	*p = j;
	return (1);
}

/**
 * check_chain - Check if we should continue chaining based on the last status.
 * @info: Parameter struct.
 * @buf: Character buffer.
 * @p: Address of current position.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Replace aliases in the tokenized string.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replace variables in the tokenized string.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	while (info->argv[i])
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			i++;
			continue;
	}

	if (!_strcmp(info->argv[i], "$?"))
	{
		replace_string(&(info->argv[i]),
			_strdup(convert_number(info->status, 10, 0)));
	}
	else if (!_strcmp(info->argv[i], "$$"))
	{
		replace_string(&(info->argv[i]),
			_strdup(convert_number(getpid(), 10, 0)));
	}
	else
	{
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
		}
		else
		{
			replace_string(&info->argv[i], _strdup(""));
		}
	}
	i++;
}
	return (0);
}

/**
 * replace_string - Replace a string.
 * @old: Address of the old string.
 * @new: The new string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

