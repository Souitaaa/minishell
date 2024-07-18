/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:53:48 by csouita           #+#    #+#             */
/*   Updated: 2024/07/18 15:25:37 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int ac ,char *av[])
{
    (void)av;
    char *str;
    if (ac != 1)
    {
        write(1,"Error in arguments",19);
        exit(1);
    }
    while(1)
    {
        str = readline("minishell> ");
        printf("%s\n",str);
    }
    return 0;
}
