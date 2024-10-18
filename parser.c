/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:01:46 by csouita           #+#    #+#             */
/*   Updated: 2024/10/16 18:31:33 by csouita          ###   ########.fr       */
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

t_file *ft_create_node(char *file_name, t_tokens redirection_type)
{
    t_file *node = malloc(sizeof(t_file));
    
    char *unquoted_name = handle_quotes(file_name);
    node->file_name = unquoted_name;
    node->file_type = redirection_type;
    node->next = NULL;
    return node;
}
char *handle_quotes(char *str)
{
    int i = 0;
    int j = 0;
    char *tmp_str = NULL;
    char tmp_char;
    
    if(!str)
        return NULL;
    tmp_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i])
    {
        if(str[i] == '\'' || str[i] == '\"')
        {
            tmp_char = str[i++];
            while(str[i] && str[i] != tmp_char)
                tmp_str[j++] = str[i++];
            if (str[i]) i++;
        }
        else
            tmp_str[j++] = str[i++];
    }
    tmp_str[j] = '\0';
    return tmp_str;
}

void handle_redirection(t_lexer **head, t_file **file_name ,int redirection_type)
{
    t_file *node;
    char *temp = NULL;
   
    *head = (*head)->next;
    while (*head && (*head)->tokens == WHITESPACE)
        *head = (*head)->next;
    while (*head && (*head)->tokens == WORD)
    {
        temp = ft_strjoin(temp, (*head)->str);
        *head = (*head)->next;
    }
    node = ft_create_node(temp, redirection_type);
    ft_lstadd_back_file(file_name, node);
}

int is_redirection(t_tokens token)
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
        handle_redirection(head, file_name,(*head)->tokens);
    else
        *head = (*head)->next;
}

t_command *ft_add_command(char *command, t_file **file)
{
    t_command *node;
    int i = 0;
    char **commands = ft_split(command, ' ');
    if (!commands)
       return NULL;
    node = malloc(sizeof(t_command));
    while(commands[i])
        i++;
    node->cmd = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while(commands[i])
    {
        node->cmd[i] = handle_quotes(commands[i]);
        i++;
    }
    node->cmd[i] = NULL;
    node->file = *file;
    node->next = NULL;
    return node;
}

void ft_create_command(t_command **command_list, char *command, t_file **file)
{
  
    t_command *node ;
    node = ft_add_command(command, file);
    ft_lstadd_back_command(command_list, node);
}

t_command *parser(t_data *data)
{
    t_file *file = NULL;
    t_lexer *head = data->head;
    char *command = NULL;
    t_command *command_list;

    command_list = NULL;
    while (head)
    {
        
        while (head && head->tokens != PIPE)
            parser_works(&command, &head,  &file);
        ft_create_command(&command_list,command,&file);
        command = NULL;
		file = NULL;
        if (head && head->tokens == PIPE)
            head = head->next;
    }
    return command_list;
}

