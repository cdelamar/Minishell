/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:02:37 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/12 16:56:30 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_ctx {
	char **env;
	char **path;
	char *prompt; // gnl pffff
	int	infile;
	int outfile;
} t_ctx;

typedef struct s_token {
	enum type;
	char *value;
	struct s_token *next;
	//jsp
}	t_token;