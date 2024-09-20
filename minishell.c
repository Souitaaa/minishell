/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:53:48 by csouita           #+#    #+#             */
/*   Updated: 2024/09/20 17:58:01 by csouita          ###   ########.fr       */
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

int	search_in(char *str, char c)
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

void not_expandable(t_lexer **lexer)
{
    while((*lexer)->next && (*lexer)->tokens != WORD)
        *lexer = (*lexer)->next;
    *lexer = (*lexer)->next;
}
void after_quotes(t_lexer **lexer , int *i, char **expanded)
{
    if(!((*lexer)->next))
    {
        // printf("ssssssssssssssssssssssss\n");
        *expanded = ft_strdup("$");
        return;
    }
    else if((*lexer)->next->str[*i] == '\'' || (*lexer)->next->str[*i] == '\"')
    {
        // printf("ssssssssssssssssssssssss\n");
        *expanded = ft_strdup("f");
    }
    (*lexer) = (*lexer)->next;
    return ;
}
    // }
// }

void *get_key(char *str)
{
    int i = 0;
    int start = 0;
    int end;
    
    while(str[i])
    {
        printf("str[i] ==== %c\n",str[i]);
        if(ft_isalnum(str[i]))
        {
            i++;
            if(ft_strlen(str) < 2)
                return NULL;
        }
        // printf("lexer position = %c\n",lexer->str[i]);
        if(str[i] == '$')
        {
            // printf("vvvvvvvvvvvvvvvv\n");
            start = i + 1;
            i++;
        }
        end = i; 
        if(!(ft_isalnum(str[i])))
        {
            char *string = ft_substr(str, start, end - start);
            return string;
        }
    }
    return NULL;
}

char *get_value(char *key ,t_env *env)
{
    while(env)
    {
        // printf("env->keysssssss%s\n",env->key)
        if(ft_strcmp(key,env->key) == 0)
        {
            if(!env->value)
                return "";
            return env->value;
        }
        env = env->next;
    }
    return NULL;
}

void cheking_the_expand(t_lexer *lexer ,t_env *env,int *i ,char **expanded)
{
    char *key ;
    char *value;
    // int z = 0;

    // printf("test==> %s\n",lexer->str);
    key = get_key(&lexer->str[*i]);
    value = get_value(key ,env);
    // *expanded = value;
    printf("key----> %s \n",key);
    *i = ft_strlen(value); 
    if(value)
        *expanded = ft_strjoin(*expanded,value);
    printf("value----> %s \n",*expanded);
    return ;
}

void expandables(t_lexer **lexer, t_env *env, char **str_to_expand)
{
    int i = 0 ;
    char	tmp[2];
    while((*lexer)->str[i])
    {
        if(ft_strcmp((*lexer)->str,"$") == 0)
        {
            after_quotes(lexer,&i , str_to_expand);
            break;
        }
        if((*lexer)->str[i] == '$' && ft_isdigit((*lexer)->str[i + 1]) && ft_strlen((*lexer)->str) >= 2)
        {
            i = i + 2;
            *str_to_expand = ft_strdup("");
        }
        else if((*lexer)->str[i] == '$' && ft_isalnum((*lexer)->str[i + 1]))
            cheking_the_expand((*lexer) , env, &i, str_to_expand);
        else
        {
            tmp[0] = (*lexer)->str[i++];
            tmp[1] = '\0';
            *str_to_expand = ft_strjoin(*str_to_expand  ,tmp);
        }
        // i++;
    }
    return ;
} 

void expand(t_lexer *lexer  , t_env *env )
{
    int i = 0;
    char *expanded = NULL;
    while(lexer)
    {
        if(lexer->tokens == HEREDOC)
        {   
            not_expandable(&lexer);
            continue;
        }
        else if(lexer->tokens == WORD && lexer->str[i] != '\'')
        {
            expandables(&lexer , env, &expanded);
            lexer->str = expanded;            
        }
        lexer = lexer->next;
    }
    printf("----->%s\n",expanded);
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
        expand(data.head, env);
        
        // write(1,"\n",1);
    }
    clear_history();
    return 0;
}
