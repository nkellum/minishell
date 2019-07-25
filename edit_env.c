/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:37:25 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/25 15:46:01 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int var_exists(t_shell *shell, char *var)
{
	int i;
	char *name;

	i = 0;
	while(var[i])
	{
		if(var[i] == '=')
		break;
		i++;
	}
	name = ft_strsub(var, 0, i);
	i = check_env(shell, name);
	free(name);
	return (i);
}

void del_env_var(t_shell *shell, int index)
{
	char **new_array;
	int length;
	int i;
	int j;

	length = 0;
	i = 0;
	j = 0;
	while(shell->environ[length])
		length++;
	if((new_array = malloc(sizeof(char**) * length)) == NULL)
		return ;
	while(i < length - 1)
	{
		if(j == index)
			j++;
		new_array[i] = ft_strdup(shell->environ[j]);
		i++;
		j++;
	}
	new_array[i] = NULL;
	free(shell->environ);
	shell->environ = new_array;
}

void add_env_var(t_shell *shell, char *var)
{
	char **new_array;
	int length;
	int i;

	length = 0;
	i = 0;
	if(var_exists(shell, var) != -1)
	{
		free(shell->environ[var_exists(shell, var)]);
		shell->environ[var_exists(shell, var)] = ft_strdup(var);
	}
	else
	{
		while(shell->environ[length])
		length++;
		if((new_array = malloc(sizeof(char**) * (length + 2))) == NULL)
		return ;
		while(i < length)
		{
			new_array[i] = ft_strdup(shell->environ[i]);
			i++;
		}
		new_array[i] = ft_strdup(var);
		new_array[length + 1] = NULL;
		free(shell->environ);
		shell->environ = new_array;
	}
}

char **string_arr_cpy(char **array)
{
	char **new_array;
	int length;
	int i;

	length = 0;
	i = 0;
	while(array[length])
		length++;
	if((new_array = malloc(sizeof(char *) * (length + 1))) == NULL)
		return (NULL);
	while(i < length)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = 0;
	return (new_array);
}
