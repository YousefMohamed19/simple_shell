#include "holberton.h"

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	while (1)
	{
		write(1, "$ ", 2);
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			break;
		}
		args = tokenize(line);
		execute(args);
		free(args);
	}
	free(line);
	return (0);
}

/**
 * tokenize - Tokenizes the input string into an array of arguments
 * @line: Input string from getline
 *
 * Return: Array of arguments
 */
char **tokenize(char *line)
{
	char **tokens = NULL;
	char *token;
	int i = 0;

	tokens = malloc(sizeof(char *) * (BUFFER_SIZE));
	if (!tokens)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, " \t\n\r");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t\n\r");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute - Executes the command entered by the user
 * @args: Array of arguments
 *
 * Return: No return value
 */
void execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Error");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		do {
			wait(&status);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

