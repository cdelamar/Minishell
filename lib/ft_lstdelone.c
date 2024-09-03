/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 23:00:59 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 23:08:19 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}

/*
void	ft_free(void *content)
{
	free (content);d
}
int	main()
{
    // Initialize a linked list with some sample data
    t_list *node1 = malloc(sizeof(t_list));
    node1->content = "Node 1 data";
    node1->next = NULL;

    // Initialize a pointer to the head of the list
    t_list *head = node1;

    // Call the t_lstdelone function to delete the first node
    t_lstdelone(&head, ft_free);

    // Verify that the first node is deleted
    if (head == NULL) {
        printf("Node 1 is successfully deleted.\n");
    }

    return 0;
}*/