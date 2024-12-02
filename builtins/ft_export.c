/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:29:31 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/08 21:00:25 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_var_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	add_env_var(char *var, t_cmd *cmd)
{
	int		i;
	char	*name_end;
	char	**cpy;

	i = 0;
	name_end = ft_strchr(var, '=');
	if (!name_end || !is_valid_var_name(var))
		return (EXIT_FAILURE);
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], var, name_end - var) == 0
			&& cmd->env[i][name_end - var] == '=')
		{
			cmd->env[i] = (free(cmd->env[i]), ft_strdup(var));
			return (EXIT_SUCCESS);
		}
		i++;
	}
	cpy = malloc(sizeof(char *) * (i + 2));
	cpy_tab(cpy, cmd->env);
	cpy[i] = ft_strdup(var);
	cpy[i + 1] = NULL;
	ft_freetab(cmd->env);
	cmd->env = cpy;
	return (0);
}

void	print_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		printf("%s\n", cmd->env[i]);
		i++;
	}
}

int	ft_export(char **args, t_cmd *cmd)
{
	int	i;
	int	result;

	i = 1;
	result = EXIT_SUCCESS;
	if (!args[1])
	{
		print_env(cmd);
		return (EXIT_SUCCESS);
	}
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			printf("export: `%s`: not a valid identifier\n", args[i]);
			result = EXIT_FAILURE;
		}
		else if (add_env_var(args[i], cmd) == EXIT_FAILURE)
			result = EXIT_FAILURE;
		i++;
	}
	g_signal = result;
	return (result);
}
