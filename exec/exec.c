/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:50:12 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 16:14:34 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_ctx {
	char **envp;
} t_ctx;

typedef struct s_exec {
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	bool	infile_ok;
	bool	outfile_ok;
	int		infile;
	int		outfile;
	char	*paths;
	char	**split_paths;
	int		cmd_nb;
} t_exec;

int main (int argc, char **argv, char **envp)
{
	
}