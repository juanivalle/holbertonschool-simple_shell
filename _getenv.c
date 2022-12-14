#include "header.h"
/**
 *_getenv - get value from a enviroment variable
 *
 *@name: string with VAR name
 *
 * Return: on success a duplicate from the VAR value, NULL if fails.
 */
char *_getenv(const char *name)
{
	int cnt, cnt2;
	int status;

	for (cnt = 0; environ[cnt]; cnt++)
	{
		status = 1;
		for (cnt2 = 0; environ[cnt][cnt2] != '='; cnt2++)
		{
			if (name[cnt2] != environ[cnt][cnt2])
			{
				status = 0;
				break;
			}
		}

		if (status == 1)
			return (_strdup(&environ[cnt][cnt2 + 1]));
	}

	return (NULL);
}
/**
 *addPath_node - add a node ona path_list list
 *@str: string coming for main's getline
 *@head: ptr to head node
 *@data: data
 * Return: @new node on success, NULL if fails.
 */
path_list *addPath_node(path_list **head, const char *data, char *str)
{
	char *aux = NULL;
	path_list *new = NULL, *last = NULL;

	new = malloc(sizeof(path_list));
	if (!new)
		return (NULL);

	aux = malloc((strlen(data) + 2 + strlen(str)));

	strcpy(aux, data);
	strcat(aux, "/");
	strcat(aux, str);

	new->data = aux;
	new->next = NULL;

	if (!*head)
	{
		*head = new;
		return (new);
	}

	else
	{
		last = *head;

		while (last->next != NULL)
		{
			last = last->next;
		}

		last->next = new;

		return (new);
	}
}
/**
 *get_path - initalizes a path_list list
 *
 *@str: string coming for main's getline
 * Return: @head ptr.
 */
path_list *get_path(char *str)
{
	char *path = NULL, *tok = NULL, *str_aux;
	path_list *head = NULL;

	if (!str)
		return (NULL);

	str_aux = _strdup(str);

	path = _getenv("PATH");

	tok = strtok(path, ":");

	while (tok)
	{
		addPath_node(&head, tok, str_aux);
		tok = strtok(NULL, ":");
	}

	free(str_aux), free(path);

	return (head);
}
/**
 *free_path - free's a path_node list
 *
 *@head: @head ptr
 * Return: nothing.
 */
void free_path(path_list *head)
{
	path_list *crt_node = NULL;

	while (head)
	{
		crt_node = head;
		head = head->next;

		free(crt_node->data);
		free(crt_node);
	}
}
