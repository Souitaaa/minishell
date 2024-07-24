/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:53:48 by csouita           #+#    #+#             */
/*   Updated: 2024/07/24 11:04:54 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void    handle_sigint(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    rl_replace_line("",0);
    rl_on_new_line();
    rl_redisplay();
}

int main(int ac ,char *av[])
{
    (void)av;
    t_data data;
    // char *t_data->line;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    if (ac != 1)
    {
        write(1,"Error in arguments",19);
        exit(1);
    }
    while(1)
    {
        data.line = readline("minishell> ");
        // exit(1);
        // printf("%s\n",t_data.line);
        if(!data.line)
            break;
        add_history(data.line);
        lexer(&data);
        display_token_lexer(data.head);
        if (syntax_error(&data) == 0)
            ft_putstr_fd("syntax error\n",2);
        // write(1,"\n",1);
    }
    clear_history();
    return 0;
}
