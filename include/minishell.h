/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <laubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:02:11 by lucasaubry        #+#    #+#             */
/*   Updated: 2024/06/12 20:16:19 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== INCLUDE ============= */

# include "unistd.h"
# include "stdlib.h"
# include "signal.h"

/* ========== ENUM ================= */

enum token_type
{
	WORD, //commande
	PIPE // |
	REDIRECION, // <<
	VAR, // $[un truc]  ? //dans le truc que jenvoie a clement enlever la var et la remplacer par ce quelle va chercher et metre enum word
	DOUBLE_QUOTE, // ""
	END, // \0
} token_enum;

/* ========== STRUCTURE ============ */

typedef struct s_token
{
	token_enum type; // COMMANDE 
	char *content; // LS..cd ex...
	int	index; // 1 2 3
	struct s_token *next; // next
} t_token;

/* ========== Error =================*/

# define ERROR_NODE 1

/* ========== FONCTION ============= */

int	check_error(int code_error);

#endif
