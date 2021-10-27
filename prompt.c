#include "shell.h"

#define TK_BUFF_SIZE 64
#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"

/**
 *dash_execute - executing commands
 *@args: return the function dash_exit
 *Return: 1 for seccessfull executing
 */
int dash_execute(char **args)
{
	pid_t cpid;
	int status;

	if (strcmp(args[0], "exit") == 0)
	{
		return dash_exit(args);
	}
	
	cpid = fork();

	if (cpid == 0)
	{
		if (execvp(args[0], args) < 0)
			printf("dash: command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);

	}
	else if (cpid < 0)
	{
		printf(RED "Error forking" RESET "\n");
	}
	else
	{
		waitpid(cpid, & status, WUNTRACED);
	}
	return (1);
}


/**
 *dash_exit - Existing the shell
 *@args: check the user has entered exit
 *Return: 0 exit the program
 */
int dash_exit(char **args)
{
	return (0);
}

/**
 *split_line - Tokenizing input
 *@line: memory managment
 *Return: returns the tokens variable
 */
char **split_line(char * line)
{
	int buffsize = TK_BUFF_SIZE, position = 0;
	char **tokens = malloc(buffsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buffsize)
		{
			buffsize += TK_BUFF_SIZE;
			tokens = realloc(tokens, buffsize * sizeof(char *));

			if (!tokens)
			{
				fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;

	return (tokens);
}

/**
 *read_line - reading users command
 *Description: gets the character enterd by the user and stores it in c.
 *             if it is and EOF or \n, a null terminator is returned.
 *             if not, the character is stored in hte buffer char pointer.
 */
char *read_line()
{
	int buffsize = 1024;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffsize);
	int c;

	 if (!buffer)
	 {
		 fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
		 exit(EXIT_FAILURE);
	 }

	 while (1)
	 {
		 c = getchar();
		 if (c == EOF || c == '\n')
		 {
			 buffer[position] = '\0';
			 return buffer;
		 }
		 else
		 {
			 buffer[position] = c;
		 }
		 position++;

		 if (position >= buffsize)
		 {
			 buffsize += 1024;
			  buffer = realloc(buffer, buffsize);

			  if (!buffer)
			  {
				  fprintf(stderr, "dash: Allocation error\n");
				  exit(EXIT_FAILURE);
			  }
		 }
	 }
}


/**
 *loop - starting of the shell
 */
void loop()
{
	char *line;
	char **args;
	int status = 1;

	do
	{
		printf("> ");
		line = read_line();
		args = split_line(line);
		status = dash_execute(args);
		free(line);
		free(args);
	} while (status);
}
					  
