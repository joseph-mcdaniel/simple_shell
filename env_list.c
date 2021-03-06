#include "shell.h"
/**
 * add_nodeenv_end - adding an environment variable to the end of the
 * linked list
 * @envlist: struct pointer to struct env_t
 * @env: contains environment information to break down
 *
 * Return:none
 */
void add_nodeenv_end(env_t **envlist, char *env)
{
	env_t *newNode;
	char *key, *value;
	env_t *temp;

	if (env == NULL)
	{
		return;
	}
	newNode = malloc(sizeof(env_t));
	if (newNode == NULL)
		return;
	key = strtok(env, "=");
	/**
	 * need to fix this, there is a more elegant way to do this
	 */
	if (_strcmp(key, "LS_COLORS") == 0)
		value = strtok(NULL, "");
	else
		value = strtok(NULL, "=");
	newNode->key =  _strdup(key);
	newNode->value = _strdup(value);
	if (*envlist == NULL)
	{
		*envlist = newNode;
		newNode->next = NULL;
		(*envlist)->count += 1;
		return;
	}
	temp = *envlist;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->next = NULL;
	(*envlist)->count += 1;
}
/**
 * print_listenv - function to print the linked list of environment variables
 * @envlist: struct pointer to struct env_t
 *
 * Return:size_t, number of nodes in the list
 */
size_t print_listenv(env_t *envlist)
{
	int i;
	int len = 0;
	env_t *temp;
	char *buff;

	i = 0;
	temp = envlist;
	while (temp != NULL)
	{
		buff = concat_env(temp->key, temp->value, &len);
		write(1, buff, len);
		write(1, "\n", 1);
		temp = temp->next;
		free(buff);
	}
	return (i);
}

/**
 * concat_env - function to concat the env list together from
 * linked list
 * @key: the key
 * @value: the value
 * @len: the length of both
 * Return: string, concat
 */
char *concat_env(char *key, char *value, int *len)
{
	char *env;

	*len = _strlen(key) + _strlen(value) + 2;
	env = malloc((*len) * sizeof(char));
	env = _strcpy(env, key);
	env = _strcat(env, "=");
	env = _strcat(env, value);
	env = _strcat(env, "\0");
	return (env);
}
