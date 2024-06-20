/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:02:11 by lucasaubry        #+#    #+#             */
/*   Updated: 2024/06/20 18:59:33 by lucasaubry       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== INCLUDE ============= */

# include "unistd.h"
# include "stdlib.h"
# include "signal.h"
# include "stdio.h"
# include "readline/readline.h"
# include "readline/history.h"
//# include "./../lib/include/libft.h"

/* ========== ENUM ================= */

enum token_enum
{
	WORD, //commande
	PIPE, // |
	REDIRECTION, // <<
	VAR, // $[un truc]  ? //dans le truc que jenvoie a clement enlever la var et la remplacer par ce quelle va chercher et metre enum word
	DOUBLE_QUOTE, // ""
	END, // \0
};

/* ========== STRUCTURE ============= */

typedef struct s_token
{
	enum token_enum type; // COMMANDE 
	char *content; // LS..cd ex...
	int	index; // 1 2 3
	struct s_token *next; // next
} t_token;

/* ========== Error =================*/

# define ERROR_NODE 1
# define ERROR_ARGS 2
# define ERROR_QUOTE 3

/* ========== FONCTION ============= */

/*-------------error-----------------*/
int	check_error(int code_error);
int	check_error_before_split(char *line);
/*-------------libft-----------------*/
t_token	*token_lstnew(void *content);
void	token_lstadd_back(t_token **lst, t_token *new);
void	token_lstclear(t_token **lst, void (*del)(void*));
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
int		ft_strlen2(char	*word);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
char	*ft_strncpy(char *dst, char *src, size_t n);

/*------------tools------------------*/
void	print_node(t_token *token);
int		nbr_of_argv(char **argv);
void	print_path(char **evnp);
/*------------parsing----------------*/
void	lexer(t_token *token, char **argv);
void	path_main(t_token *token_list, char **envp);



#endif
