/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:54:21 by csouita           #+#    #+#             */
/*   Updated: 2024/10/16 16:35:18 by csouita          ###   ########.fr       */
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
 char  	*key;
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


typedef struct s_file
{
	char				*file_name;
	t_tokens			file_type;
	bool				quotes;
	struct s_file		*next;
}			t_file;


typedef struct s_command
{
	char				**cmd;//[0] command [1] argument
	t_file				*file;
	struct s_command	*next;
}			t_command;


int				ft_isalnum(int c);
char			*ft_strjoin(char *s1, char *s2);
int				ft_isdigit(int c);
int				ft_strcmp(char *s1, char *s2);
size_t 			ft_strlen(char *str);
void			ft_putstr_fd(char *s, int fd);
void 			add_spaces(t_data *data);
char			**ft_split(char *s, char c);
t_list			*ft_lstlast(t_list *lst);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
t_list			*ft_lstnew(int content);
void 			lexer(t_data *line);
void			ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);
void			ft_lstadd_back_file(t_file **lst, t_file *new);
void			ft_lstadd_back_command(t_command **lst, t_command *new);
t_lexer 		*new_lexer_node(t_tokens type,char *str);
void 			add_node(t_lexer **head, t_tokens type ,char *str);
char			*ft_strdup(char *s1);
char			*ft_substr(char *s, unsigned int start, size_t len);
char 			*add_spaces2(t_data *data) ;
int 			syntax_error(t_data *data);
void 			expand(t_lexer *lexer, t_env *env);
void			the_expandables(t_lexer **lexer, t_env *env, char **str_to_expand);
int				check_quotes_in_expand(char *str);
char			*get_key(char *str);
char			*get_value(t_env *env, char *key);
void			expand_in_heredoc(char **str, t_env *env);
void			not_expandables(t_lexer **lexer);
int				cheking_the_expand(char *str, t_env *env, int *i, char **str_to_expand);
char			*add_escape_characters(char *str);
int				after_quote(t_lexer **lexer, char **str_to_expand);
void			special_case(t_lexer *lexer, char **str_to_expand, int *i);
char			**get_key_before_expand(void);
void			special_case_in_heredoc(char *str, char **str_to_expand, int *i);
void			dollar_and_quote(char **str_to_expand, int *i);
t_command 		*parser(t_data *data);
void 			parser_works(char **command, t_lexer **head, t_file **file_name);
int 			is_redirection(t_tokens token);
void 			handle_redirection(t_lexer **head, t_file **file_name ,int redirection_type);
void 			handle_word(char **command, t_lexer **head);
char 			*handle_quotes(char *str);
int 			check_redirection(char *line);





/////////////////still for test mn hna /////////
void 			display_token_command(t_command *command);
void			display_token_lexer(t_lexer *lexer);
char			*get_token(t_tokens token);
/////////////////7tal hna ///////////////

#endif
