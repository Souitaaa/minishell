/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:53:48 by csouita           #+#    #+#             */
/*   Updated: 2024/10/07 21:07:06 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// int z  = 0;

void    handle_sigint(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    rl_replace_line("",0);
    rl_on_new_line();
    rl_redisplay();
}

static int	search_in(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

t_env *create_node(char *env)
{
    int i = 0;
    t_env *lst;
    char *key ;
    char *value;
    lst = malloc(sizeof(t_env));
    key = ft_substr(&env[i],0,search_in(env,'='));
    lst->key = key;
    value = ft_substr(&env[i],search_in(env,'=') + 1,ft_strlen(env));
    lst->value = value;
    lst->next = NULL;
    return lst;
}

t_env *get_last_node(t_env *head)
{
    if (!head)
        return NULL;
    while(head->next)
        head = head->next;
    return head;
}

void add_back(t_env **head ,t_env *new_content)
{
    t_env *last;
    if(!head || !new_content)
        return;
    if(*head)
    {
        last = get_last_node(*head);
        last->next = new_content;
    }
    else
        *head = new_content;
}

t_env *cp_env_in_liste(char **env)
{
    int i = 0;
    t_env *lst = 0;
    while(env[i])
    {
        add_back(&lst,create_node(env[i]));
        i++;
    }
    return lst;
}

int main(int ac ,char *av[], char **envr)
{
    (void)av;
    t_data data;
    t_env *env;
    // char *t_data->line;

    // env = cp_env_to_list(&env);
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    if (ac != 1)
    {
        write(1,"Error in arguments",19);
        exit(1);
    }
    env = cp_env_in_liste(envr);
    // while(env)
    // {
    //     printf("%s=",env->key);
    //     printf("%s\n",env->value);
    //     env = env->next;
    // }
    
    while (data.line)
    {
        data.line = readline("minishell> ");
        // exit(1);
        // printf("%s\n",t_data.line);
        if (!data.line)
            break;
        add_history(data.line);
        lexer(&data);
        // display_token_lexer(data.head);
        if (syntax_error(&data) == 0)
        {
            ft_putstr_fd("syntax error\n",2);
            continue ;
        }
        expand(data.head, env);
        display_token_command(parser(&data));
        // handel_quotes()
        
        // write(1,"\n",1);
    }
    return 0;
}
