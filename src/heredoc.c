/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:59:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/23 21:38:56 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO croire en ses reves

// comment ca marche
// un fichier temporaire > open et unlink
// basic command sur la redi

/*

char *ft_realloc(char *str, int size)
{
    char *new_str;
    
    new_str = malloc(size);
    strcpy(new_str, str);
    free(str);
    return new_str;
}

int main(char *delim)
{
    char* line;
    readline(line);
    char *final_str;
    while(strcmp(line, delim))
    {
        realloc(final_str, strlen(final_str) + strlen(line));
        strcat(final_str, line);
    }
    
    //executer final_str | command

    
    return 0;
}

*/