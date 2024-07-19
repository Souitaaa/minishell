/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:37:02 by csouita           #+#    #+#             */
/*   Updated: 2024/07/18 20:38:56 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while(str[i])
        i++;
    return i;
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd == -1)
	{
		return ;
	}
	write(fd, s, ft_strlen(s));
}
