#include "shell.h"

size_t count_elements(const list_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return i;
}

char **list_str(list_t *head)
{
list_t *node = head;
size_t i = count_elements(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
