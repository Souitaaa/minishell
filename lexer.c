/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:13:52 by csouita           #+#    #+#             */
/*   Updated: 2024/10/16 16:35:05 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_spaces(t_data *data) 
{
    int i = 0;
    int len = ft_strlen(data->line);

    while (i < len) 
    {
        while(data->line[i] == 32)
            i++;
        if ((data->line[i] == '>' && data->line[i + 1] == '>') || (data->line[i] == '<' && data->line[i + 1] == '<')) 
        {
            write(1, " ", 1);
            write(1, &data->line[i], 2);
            write(1, " ", 1);
            i += 2;
        }
        else if (data->line[i] == '>' || data->line[i] == '<' || data->line[i] == '|') 
        {
            write(1, " ", 1);
            write(1, &data->line[i], 1);
            write(1, " ", 1);
            i++;
        }
        else 
        {
            //men ba3d o n3awed had l3iba
            if (i > 0 && (data->line[i - 1] == '>' || data->line[i - 1] == '<' || data->line[i - 1] == '|') && data->line[i] == 32)
                write(1, &data->line[i], 1);
            else 
                write(1, &data->line[i], 1);
            i++;
        }
    }
}

void	ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new)
{
	t_lexer	*p  = *lst;

	if (lst == NULL || new == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while(p->next != NULL)
    {
        p = p->next;
    }
	p->next = new;
}

t_lexer *new_lexer_node(t_tokens type,char *str)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->str = str;
    new_node->tokens = type;
	new_node->next = NULL;
	return (new_node);
}

void add_node(t_lexer **head, t_tokens type ,char *str)
{
    t_lexer *node ;
    
    node = new_lexer_node(type ,str);
    ft_lstadd_back_lexer(head,node);
}

int word(t_data *data,int i)
{
    int start;
    char *line = NULL;
    start = i;
    
    if(data->line[i] == '"')
    {
            i++;
        while(data->line[i] && data->line[i] != '"')
            i++;
        if(data->line[i])
            i++;
    }
    else if (data->line[i] && data->line[i] == '\'')
    {
            i++;
        while(data->line[i] && data->line[i] != '\'')
            i++;
        if(data->line[i])
            i++;
    }
    else
        {
            while(data->line[i] && data->line[i] != '"' && data->line[i] != '\'' && data->line[i] != '>' && data->line[i] != '<' && data->line[i] != '|' && data->line[i] != 32)
                i++;
        }
        line = ft_substr(data->line, start,i - start);
        add_node(&data->head,WORD,line);
    return i;
}
int	add_whitespace(int i, t_data **data)
{
	add_node(&(*data)->head, WHITESPACE, " ");
	while ((*data)->line[i] && ((*data)->line[i] == ' ' || (*data)->line[i] == '\t'))
		i++;
	if (!(*data)->line[i])
		return (-1);
	return (i);
}

void lexer(t_data *data)
{
    
    int i = 0;
    // add_spaces2(data);
    
    data->head = NULL;
    while(data->line[i])
    {
        if (data->line[i] == ' ' || data->line[i] == '\t')
		{
			i = add_whitespace(i, &data);
			if (i == -1)
				break ;
		}
        if (data->line[i] == '|')
        {
           add_node(&data->head,PIPE,"|");
           i++;
        }
        else if (data->line[i] == '>' && data->line[i + 1] == '>')
        {
            add_node(&data->head,HEREDOC,">>");
            i = i+2;
        }
        else if (data->line[i] == '<' && data->line[i + 1] == '<')
        {
            add_node(&data->head,APPEND,"<<");
            i = i+2;
        }
        else if (data->line[i] == '>')
        {
            add_node(&data->head,REDIR_IN,">");
            i++;
        }
        else if (data->line[i] == '<')
        {
            add_node(&data->head,REDIR_OUT,"<");
            i++;
        }
        else 
            i = word(data,i);
        // i++;
    }
}

// int check_quotes(t_data *data)
// {
//     int i = 0;
//     if(data->line[i] == '\'' || data->line[i] == '\"')
//     {
//         while(data->line[i] && (data->line[i] != '\'' || data->line[i] != '\0'))
//             i++;
//         if(data->line[i] == '\0')
//             return 0;
//         if(data->line[ft_strlen(data->line) - 1] != '\'')
//             return 0;
//         else
//             return 1;
//     }
//     return 1;
// }

// int is_pair(int number) 
// {
//     return number % 2 == 0 ? 1 : 0;
// }

// int check_pair(t_data *data) 
// {
//     int i = 0; 
//     int single_quote = 1;
//     int double_quote = 1;
//     while (data->line[i]) 
//     {
//         if (data->line[i] == '\'') 
//                 single_quote++;
//         else if (data->line[i] == '\"')
//                 double_quote++;
//         i++;
//     }
//     if (is_pair(single_quote) == 1|| is_pair(double_quote) == 1) 
//         return 0;
//     else if (is_pair(single_quote) == 0 || is_pair(double_quote) == 0)
//         return 1;
//     return 1;
// }
int check_quotes(t_data *data)
{
    int i = 0;
    int quote_char = 0;

    // if (check_pair(data))
    //     return 1;
    while (data->line[i])
    {
        while (data->line[i] && (data->line[i] != '\'' && data->line[i] != '\"'))
            i++;
        if (!data->line[i])
            return 1;
        quote_char = data->line[i];
        i++;
        while (data->line[i] && data->line[i] != quote_char)
            i++;
        if (!data->line[i])
            return 0;
        i++;
    }
    return 1;
}

int is_whites_spaces(char c)
{
    return (c == 32 || (c >= 9 && c <= 13));
}

int check_pipe(char *s)
{
    int i;

    if (!s)
        return (1);
    i = 0;
    while (s[i])
    {
        if (s[i] && s[i] == '|')
        {
            if (s[i])
                i++;
            while (s[i] && is_whites_spaces(s[i]))
                i++;
            if (s[i] && s[i] == '|')
                return (1);
        }
        i++;
    }
    return (0);
}


int check_redirection(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
        {
            while (line[i] == '>' || line[i] == '<')
                i++;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            if (line[i] == '\0' || line[i] == '|')
                return 0;
        }
        i++;
    }
    return 1;
}

int syntax_error(t_data *data)
{
    if (!data->line[0])
        return (1);
    if (data->line[0] == '|' || data->line[ft_strlen(data->line) - 1] == '|' || check_pipe(data->line))
        return (0);
    if (data->line[ft_strlen(data->line)] == '>' 
        ||  data->line[ft_strlen(data->line)]  == '<')
        return (0);
    if (check_redirection(data->line) == 0)
        return 0;
    if (check_quotes(data) == 0)
        return 0;
    return (1);
}
