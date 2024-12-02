/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:11:04 by laubry            #+#    #+#             */
/*   Updated: 2024/11/23 00:06:58 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

char	*ft_realloc_string(char *str, int new_size)
{
	char	*res;
	int		old_len;

	if (!str)
		return (NULL);
	old_len = ft_strlen(str);
	res = malloc(old_len + new_size + 1);
	if (!res)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(res, str, old_len);
	res[old_len] = '\0';
	free(str);
	return (res);
}

void	process_command(t_cmd *cmd, t_token **token_list)
{
	process_input(cmd, token_list);
	token_lstclear(&cmd->tokens, free);
	free(cmd->final_line);
}

void	setup_signal(void)
{
	rl_outstream = stderr;
	signal(SIGPIPE, SIG_IGN);
	signals();
}

char	**copy_env(char	**envp)
{
	int		len;
	char	**result;

	len = 0;
	while (envp[len])
		len += 1;
	result = malloc((len + 1) << 3);
	cpy_tab(result, envp);
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	char	**tab;
	int		res;
	t_token	*token_list;
	t_cmd	*cmd;

	token_list = NULL;
	cmd = NULL;
	(void)argv;
	setup_signal();
	tab = copy_env(envp);
	if (handle_arguments(argc))
		return (1);
	while (1)
	{
		res = handle_loop(&cmd, &token_list, &tab);
		if (res == 1)
			continue ;
		else if (res == 0)
			return (0);
		process_command(cmd, &token_list);
		token_lstclear(&token_list, free);
		tab = cmd->env;
	}
	return (0);
}
