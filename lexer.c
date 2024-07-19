/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:13:52 by csouita           #+#    #+#             */
/*   Updated: 2024/07/19 19:52:59 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(t_tokens token)
{
	if (token == 0)
		return ("WORD");
	else if (token == 1)
		return ("PIPE");
	else if (token == 2)
		return ("REDIR_IN");
	else if (token == 3)
		return ("REDIR_OUT");
	else if (token == 4)
		return ("HEREDOC");
	else if (token == 5)
		return ("APPEND");
	else if (token == 6)
		return ("WHITESPACE");
	return ("A");
}

void	display_token_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("value (%s) \t key (%s)\n", lexer->str,get_token(lexer->tokens));
		lexer = lexer->next;
	}
}
void display_token_command(t_command *command)
{
    int node = 1;
    
        while (command)
        {
            printf("command[%d]:\n", node);

            if (command->cmd)
            {
                int i = 0;
                while (command->cmd[i])
                {
                    printf("\tcontent[%d]: %s\n", i + 1, command->cmd[i]);
                    i++;
             
                }
            }
            while (command->file)
            {
                // printf("\tquotes : %d \n",command->file->quotes);
                printf("\tfile name: %s \tfile type: %s\n", command->file->file_name,get_token(command->file->file_type));   
                command->file = command->file->next;
            }
            node++;
            command = command->next;
        }

}

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
// void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
// {
// 	t_lexer	*last;

// 	last = *lst;
// 	if (lst == NULL || new == NULL)
// 	{
// 		return ;
// 	}
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	while (last->next != NULL)
// 	{
// 		last = last->next;
// 	}
// 	last->next = new;
// }

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

void lexer(t_data *data)
{
    
    int i = 0;
    add_spaces(data);
    
    data->head = NULL;
    while(data->line[i])
    {
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
            {
                while(data->line[i] != '>' && data->line[i] != '<' && data->line[i] != '|' && data->line[i])
                    i++;
                write(1,"Word\n",5);
            }
    }
}

