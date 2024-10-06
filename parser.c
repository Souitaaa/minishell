/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:01:46 by csouita           #+#    #+#             */
/*   Updated: 2024/10/05 18:57:53 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void handle_word(char **command, t_lexer **head)
{
    char *temp = ft_strjoin(*command, (*head)->str);
    *command = temp;
    if ((*head)->next && (*head)->next->tokens == WHITESPACE)
    {
        temp = ft_strjoin(*command, " ");
        *command = temp;
    }
    *head = (*head)->next;
}

t_file *ft_create_node(char *file_name, int redirection_type)
{
    t_file *node = malloc(sizeof(t_file));
    node->file_name = file_name;
    node->file_type = redirection_type;
    node->next = NULL;
    return node;
}

void handle_redirection(t_lexer **head, char **file_name ,int redirection_type)
{
    t_file *node;
    *head = (*head)->next;
    while (*head && (*head)->tokens == WHITESPACE)
        *head = (*head)->next;
    if (*head && (*head)->tokens == WORD)
    {
        char *temp = ft_strjoin(*file_name, (*head)->str);
        *file_name = temp;
        *head = (*head)->next;
    }
    node = ft_create_node(*file_name, redirection_type);
    ft_lstadd_back_file(file_name, node);
    printf("Redirection type: %d, file_name = %s\n", redirection_type, *file_name);
}
bool is_redirection(t_tokens token)
{
    return (token == REDIR_IN || token == REDIR_OUT || 
            token == HEREDOC || token == APPEND);
}

void parser_works(char **command, t_lexer **head, t_file **file_name)
{
    if (*head == NULL)
        return;
    if ((*head)->tokens == WORD)
        handle_word(command, head);
    else if (is_redirection((*head)->tokens))
        handle_redirection(head, &file_name,(*head)->tokens);
    else
        *head = (*head)->next;
}

void parser(t_data *data)
{
    t_file *file = NULL;
    t_lexer *head = data->head;
    char *command = NULL;
    
    while (head)
    {
        while (head && head->tokens != PIPE)
            parser_works(&command, &head,  &file);
        printf("Command: %s\n", command);
        command = NULL;
        if (head && head->tokens == PIPE)
            head = head->next;
    }
}
