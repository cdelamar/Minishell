/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:02:11 by lucasaubry        #+#    #+#             */
/*   Updated: 2024/08/19 19:04:38 by laubry           ###   ########.fr       */
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

extern volatile int	g_var;
/* ========== ENUM ================= */

typedef enum token_num
{
	WORD, //commande
	SPACES,
	PIPE, // |
	REDIRECTION, // <<
	VAR, // $
	DOUBLE_QUOTE, //
	SIMPLE_QUOTE,
	LAST_VERIF,
	GLOBAL, // $?
	ERROR, // erreur
	END, // \0
}	t_token_enum;

/* ========== STRUCTURE ============= */

typedef struct s_token
{
	t_token_enum	type; // COMMANDE 
	char			*content; // LS..cd ex...
	int				index; // 1 2 3
	struct s_token	*next; // next
}	t_token;

//typedef struct s_list
//{
//	t_list_enum		type;
//	char			*content;
//	int				index;
//	struct s_list	*next;
//}	t_list;

/* ========== Error =================*/

# define ERROR_NODE 1
# define ERROR_ARGS 2
# define ERROR_QUOTE 3
//# define RESET "\033[0m"
//# define ORANGE "\033[38;5;208m"

/* ========== FONCTION ============= */

/*-------------error-----------------*/
int			check_error(int code_error);
int			check_error_before_split(char *line);
int			badchar(char **split_line);

/*-------------libft-----------------*/
t_token		*token_lstnew(void *content);
void		token_lstadd_back(t_token **lst, t_token *new);
void		token_lstclear(t_token **lst, void (*del)(void*));
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
size_t		ft_strlen(const char *str);
int			ft_strlen2(char	*word);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strchr(char *s, int c);
int			ft_strchr2(char *s, char c);
char		*ft_strncpy(char *dst, char *src, size_t n);
void		ft_bzero(void *s, size_t n);
char		**ft_split_boosted(char *s);
int			check_char(char *s, int i, char **lst, int j);
int			ft_isalpha(int c);
char		*ft_strjoin(char *s1, char *s);
char		*ft_strdup(const char *src);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strcpy(char *dest, char *src);
void		ft_lstdelone(t_token *lst, void (*del)(void*));
char		*ft_strdup_for_quote(const char *src);

/*------------tools------------------*/
void		print_node(t_token *token);
int			nbr_of_strs(char **strs);
void		print_path(char **evnp);
void		print_snail(void);
int			is_qte(char c);


/*------tools of environement--------*/
int			find_the_dollar(t_token *token);
int			skip_prefix(char *word);
char		*skip_sufix(char *word);
void		is_dollar_interogation(t_token *token_list);
void		path_other(char **envp, t_token *token_list, int place_of_dollar);
char		**minisplit_dollar(char *word);
int			nbr_of_dollar(t_token *token_list, int place_of_dollar);
int			which_node(int nbr_dollar, t_token *token_list);
char		**delet_space_to_tab(char **tab_token);

/*new*/
void		path_main(t_token *token_list, char **envp);

/*------------parsing----------------*/
void		lexer(t_token *token);
void		path_main(t_token *token_list, char **envp);
int			skip_prefix(char *word);
int			find_the_dollar(t_token *token);


/*------------cat_quote--------------*/
void		before_node_cat(t_token **token, int i, int verif);
void		after_node_cat(t_token **token, int i, int verif);
int			copy_node(t_token *head, t_token *new_node);
int			copy_node_after(t_token *head, t_token *new_node, int i_content);
int			copy_mid_node(t_token *head, t_token *new_node, int i_content);
int			copy_mid_after_node(t_token *head, t_token *new_node);
void		advance_to_node(t_token **head, t_token **before, int *i);
char		**delet_quote_inword(t_token **token, t_token *place);
/*----------lstnew_with_cat---------*/
char		**mouve_str(char **str, int i);
int			check_is_space_node(char **str, int i);
int			lstnew_with_cat(char **str, int i);
char		**main_cat(t_token **token);
/*----------tools_for_cat----------*/
char		**malloc_tab(t_token **token);
void		cat_quote(char **tab_token, t_token **token);


/*--------------free-----------------*/
void		free_split(char **strs);
void		free_head(t_token *head);
void		print_free_tab(char **final_token);


size_t		count_word(char *s);
int			is_char(char s);
int			skip_space(char *s, int i);
void		print_split(char **split_line);
int			solo_quote(char **split_line);

void		signals(void);
void		sigint_handler(int sig);
#endif
