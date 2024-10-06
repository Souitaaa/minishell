
void parser_works(char command , t_lexer head)
{
    char file_name = NULL;
    if((head) && (*head)->tokens  == WORD)
    {
        command = ft_strjoin(command,(head)->str);
        if((head)->tokens == WHITESPACE)
            command = ft_strjoin(command," ");
        head = (head)->next;
    }
    else if((head)->tokens != WORD)
    { 
        if((head)->tokens == REDIR_IN || (head)->tokens == REDIR_OUT || (head)->tokens == HEREDOC || (head)->tokens == APPEND)  
            {
                while((head) && (head)->tokens == WHITESPACE)
                    (head) = (head)->next;
                while((head)->tokens == WORD)
                    {
                        if((head)->tokens == WHITESPACE)
                            break;
                    }
                    file_name = ft_strjoin(file_name,(head)->str);
                printf("file_name = %s\n",file_name);
            }
    }
        else
            head = (head)->next;
}   

void  parser(t_data *data)
{
    t_lexer *head = data->head;
    char *command;
    t_file *file_name;

    file_name = NULL;
    command = NULL;

    while(head)
    {
        while(head->next && head->tokens != PIPE)
        {
            parser_works(&command,&head);
        }
    }
}