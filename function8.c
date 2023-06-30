#include "shell.h"

/**
 * get_env_vars - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: The array of environment variables
 */
char **get_env_vars(info_t *info)
{
	if (!info->env_var || info->env_changed)
	{
		free_str_array(info->env_var);
		info->env_var = list_str(info->env);
		info->env_changed = 0;
	}

	return (info->env_var);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, const char *var)
{
	list_t **node = &(info->env);
	size_t i = 0;

	if (!*node || !var)
		return (0);

	while (*node)
	{
		if (_startswith((*node)->str, var) && (*node)->str[_strlen(var)] == '=')
		{
			info->env_changed = rm_node(node, i);
			i = 0;
			continue;
		}
		*node = (*node)->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _setenv(info_t *info, const char *var, const char *value)
{
	char *buf = NULL;
	list_t *node;
	int overwrite = 0;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		if (_startswith(node->str, var) && node->str[_strlen(var)] == '=')
		{
			if (!overwrite)
			{
				free(buf);
				return (0);
			}
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

