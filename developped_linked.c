/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   developped_linked.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:18:13 by csouita           #+#    #+#             */
/*   Updated: 2024/07/19 18:27:32 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// t_lexer	*ft_lstnew(int content)
// {
// 	t_list	*new_node;

// 	new_node = malloc(sizeof(t_list));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->content = content;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*p;

// 	if (lst == NULL || new == NULL)
// 	{
// 		return ;
// 	}
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	p = ft_lstlast(*lst);
// 	p->next = new;
// }