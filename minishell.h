/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:54:21 by csouita           #+#    #+#             */
/*   Updated: 2024/07/23 21:13:36 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>

typedef enum e_num
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	WHITESPACE,
	QUOTES
}						t_tokens;

typedef struct s_env
{
 char   *value;
 struct s_env *next;
}    t_env;

typedef struct s_lexer
{
	char				*str;
	t_tokens			tokens;
	struct s_lexer		*next;
}					t_lexer;

typedef struct s_data
{
    char *line;
    struct s_data *next;
	t_lexer		*head;
}   t_data;

typedef struct list
{
	int			content;
	struct list	*next;
}				t_list;

////////////////////only for test mn hna 

typedef struct s_file
{
	char				*file_name;
	t_tokens			file_type;
	bool				quotes;
	struct s_file		*next;
}			t_file;


typedef struct s_command
{
	char				**cmd;
	t_file				*file;
	struct s_command	*next;
}			t_command;

////////////////////////7tal hna


size_t 			ft_strlen(char *str);
void			ft_putstr_fd(char *s, int fd);
void 			add_spaces(t_data *data);
t_list			*ft_lstlast(t_list *lst);
// void			ft_lstadd_back(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
t_list			*ft_lstnew(int content);
void 			lexer(t_data *line);
void			ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);
t_lexer 		*new_lexer_node(t_tokens type,char *str);
void 			add_node(t_lexer **head, t_tokens type ,char *str);
char			*ft_strdup(char *s1);
char			*ft_substr(char *s, unsigned int start, size_t len);
char 			*add_spaces2(t_data *data) ;
int 			syntax_error(t_data *data);

/////////////////still for test mn hna /////////
void 			display_token_command(t_command *command);
void			display_token_lexer(t_lexer *lexer);
char			*get_token(t_tokens token);
/////////////////7tal hna ///////////////

#endif
