#include "shell.h"

int b_history(info_t *info)
{
	print_list(info->history);
	return (0);
}
int unset_alias(info_t *info, char *str)
{
	char *p;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	*p = '\0';
	ret = rm_node(&(info->alias),
		get_index(info->alias, node_prefix(info->alias, str, -1)));
	*p = '=';
	return (ret);
}
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

int print_alias(list_t *node)
{
	char *p, *a;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


int b_alias(info_t *info)
{
	int i;
	char *p;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}

