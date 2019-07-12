/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:59:25 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/12 12:35:20 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void print_char_array(char **array)
{
	int i = 0;
	while(array[i])
	{
		ft_printf("array[%d] : %s\n", i, array[i]);
		i++;
	}
}

int run(char *filename, char **args, char **environ)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0)
	{
    if (execve(filename, args, environ) == -1)
      ft_printf("Error while executing command.\n");
    exit(0);
  }
	else if (pid < 0)
	{
    ft_printf("Error creating new process.\n");
		return (0);
  }
	else
    while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wait(&status);
  return (1);
}


char **get_exec_paths(char **environ)
{
	int i;
	int found;

	i = 0;
	found = 0;
	while(environ[i])
	{
		if(ft_strnstr(environ[i], "PATH", 5))
		{
			found = 1;
			break;
		}
		i++;
	}
	if(found)
		return (ft_strsplit(environ[i] + 5, ':'));
	else
		return (NULL);
}

int main()
{
	char *line;
	char cwd[1024];
	extern char **environ;

	getcwd(cwd, 1024);
	ft_printf("%s --> ", cwd);
	while(1)
	{
			if(get_next_line(0, &line))
			{
				char **input = ft_strsplit(line, ' ');
				if(input[0])
					parse_command(input, environ);
				getcwd(cwd, 1024);
				ft_printf("%s --> ", cwd);
				//return 0;
			}
			free(line);
	}
	return 0;
}
