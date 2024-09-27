/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:53:48 by csouita           #+#    #+#             */
/*   Updated: 2024/09/27 17:34:12 by csouita          ###   ########.fr       */
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
        *expanded = ft_strdup("$");
        return;
    }
    else if((*lexer)->next->str[*i] == '\'' || (*lexer)->next->str[*i] == '\"')
    {
        *expanded = ft_strdup("f");
    }
    (*lexer) = (*lexer)->next;
    return ;
}

char	*get_key(char *str)
{
	int	i;
	int	start;
	int	end;

	i = 1;
	start = i;
	while (str[i] && ft_isalnum(str[i]))   
		i++;
	end = i;
	return (ft_substr(str, start, end - start));
}


char *get_value(char *key ,t_env *env)
{
    while(env)
    {
        if(ft_strcmp(key,env->key) == 0)
        {
            if(!env->value)
                return "";
            return env->value;
        }
        env = env->next;
    }
    return ft_strdup("");
}

void cheking_the_expand(t_lexer *lexer ,t_env *env,int *i ,char **expanded)
{
    char *key;
    char *value;

    key = get_key(&lexer->str[*i]);
    value = get_value(key ,env);
    *i += ft_strlen(key);
    *expanded = ft_strjoin(*expanded,value);
}

void expandables(t_lexer **lexer, t_env *env, char **str_to_expand)
{
    int i = 0 ;
    char	tmp[2];
    while((*lexer)->str[i])
    {
        if(ft_strcmp((*lexer)->str,"$") == 0)
        {
            after_quotes(lexer,&i ,str_to_expand);
            break;
        }
        else if((*lexer)->str[i] == '$' && ft_isdigit((*lexer)->str[i + 1]) && ft_strlen((*lexer)->str) >= 2)
        {
            i = i + 2;
            *str_to_expand = ft_strdup("");
        }
        else if((*lexer)->str[i] == '$' && ft_isalnum((*lexer)->str[i + 1]))
        {
            cheking_the_expand((*lexer) , env, &i, str_to_expand);
            i++;
        }    
        else
        {
            tmp[0] = (*lexer)->str[i++];
            tmp[1] = '\0';
            *str_to_expand = ft_strjoin(*str_to_expand ,tmp);
        }
    }
    return ;
} 
char *handel_quotes(char *str)
{
    int i = 0;
    int j = 0;
    char *tmp_str = NULL;
    char tmp_char;
    tmp_str = malloc(sizeof(char) * ft_strlen(str) + 1);
    while (str[i])
    {
        if(str[i] == '\'' || str[i] == '\"')
        {
            tmp_char = str[i++];
            while(str[i] && str[i] != tmp_char )
                tmp_str[j++] = str[i++];
        }
        else
            tmp_str[j++] = str[i++];
    }
    tmp_str[j] = '\0';
    return tmp_str;
}

int check_dollar(char *str)
{
    int i = 0;
    int dollar_count = 0;

    while(str[i])
    {
        if(str[i] == '$')
            dollar_count++;
        i++;
    }
    if(dollar_count % 2 == 0)
        return 1;
    else
        return 0;
}

// char *remove_dollar(char *str)
// {
//     int i = 0;
//     int j = 0;
//     char *tmp_str = NULL;
//     tmp_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
//     while(str[i++])
//     {
//         if(str[i] && str[i] != '$')
//             tmp_str[j++] = str[i];
//         // j++;
//     }
//     tmp_str[j] = '\0';
//     return tmp_str;
// }

int lenght_before_dollar(char *str)
{
    int i = 0 ;
    while(str[i] && str[i] != '$')
        i++;
    printf("lenght === %d\n",i);
    return i ;
}

char *remove_add_dollar(char *str)
{
    int i = 0;
    int j = 0; 
    char *tmp_str;
    tmp_str = malloc(sizeof(char) * ft_strlen(str) + 2);
    if(!tmp_str)
        return NULL;    
    // i++;
    while(str[i] && str[i] != '$')
        tmp_str[j++] = str[i++];
    while(str[i] && str[i] == '$')
        i++;
    if(check_dollar(str) == 0)
        tmp_str[j++] = '$';
    while(str[i])
            tmp_str[j++] = str[i++];
    tmp_str[j] = '\0';
    printf("tmp ==== %s\n",tmp_str);
    return tmp_str;
}

// char *remove_add_dollar(char *str)
// {
//     int i = 0;
//     int j = 0; 
//     int dollar_pos = -1;
//     char *tmp_str;
//     tmp_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
//     if(!tmp_str)
//         return NULL;    

//     while(str[i])
//     {
//         if(str[i] == '$' && dollar_pos == -1)
//         {
//             dollar_pos = j;
//             i++;
//             continue;
//         }
//         tmp_str[j] = str[i];
//         i++;
//         j++;
//     }
//     tmp_str[j] = '\0';

//     if(dollar_pos != -1)
//     {
//         memmove(&tmp_str[dollar_pos + 1], &tmp_str[dollar_pos], strlen(&tmp_str[dollar_pos]) + 1);
//         tmp_str[dollar_pos] = '$';
//     }

//     printf("tmp ==== %s\n", tmp_str);
//     return tmp_str;
// }

void expand(t_lexer *lexer  , t_env *env )
{
    // (void) env;
    int i = 0;
    char *expanded = NULL;
    while(lexer)
    {
        if(check_dollar(lexer->str))
            lexer->str = remove_add_dollar(lexer->str);
        if(check_dollar(lexer->str) == 0)
            lexer->str = remove_add_dollar(lexer->str);
        printf("====>%s\n",lexer->str);
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
        lexer->str = handel_quotes(lexer->str);
        printf("expanded -:=> %s\n" ,lexer->str);
        lexer = lexer->next;
    }
    // printf("expanded -:=> %s\n" ,expanded);
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
        display_token_lexer(data.head);
        if (syntax_error(&data) == 0)
            ft_putstr_fd("syntax error\n",2);
        expand(data.head, env);
        
        // handel_quotes()
        
        // write(1,"\n",1);
    }
    clear_history();
    return 0;
}
