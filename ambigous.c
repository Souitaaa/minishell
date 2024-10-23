/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigous.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:29:04 by csouita           #+#    #+#             */
/*   Updated: 2024/10/23 17:17:32 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_elem_var(char *s)
{   
    int     i;
    char    **lst;
    
    if (!s)
        return (0);
    i = 0;
    lst = ft_split00(s);
    while (lst[i])
        i++;
    return (i);
}

int ft_check_ambigous(t_lexer *lxr)
{
    while (lxr)
    {
        if (lxr && (lxr->tokens == REDIR_IN || lxr->tokens == REDIR_OUT ||lxr->tokens == APPEND))
        {
            lxr = lxr->next;
            if (!lxr->str[0] || ft_count_elem_var(lxr->str) != 1)
            {
                printf("minishell : ambiguous redirection\n");
                return (1);
            }
        }
        else
            lxr = lxr->next;
    }
    return (0);
}
