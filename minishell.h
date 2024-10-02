/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:54:21 by csouita           #+#    #+#             */
/*   Updated: 2024/10/01 17:24:11 by csouita          ###   ########.fr       */
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

int				ft_isalnum(int c);
char			*ft_strjoin(char *s1, char *s2);
int				ft_isdigit(int c);
int				ft_strcmp(char *s1, char *s2);
size_t 			ft_strlen(char *str);
void			ft_putstr_fd(char *s, int fd);
// int				search_in(char *str, char c);
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
// void 			cheking_the_expand(t_lexer *lexer ,t_env *env,int *i , char **expanded);
// char 			*get_value(char *key ,t_env *env);
// char 			*get_key(char *str);
// void 			after_quotes(t_lexer **lexer , int *i, char **expanded);
// void			expandables(t_lexer **lexer, t_env *env, char **str_to_expand);
// void 			not_expandable(t_lexer **lexer);
// int 			check_dollar(char *str);
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



/////////////////still for test mn hna /////////
void 			display_token_command(t_command *command);
void			display_token_lexer(t_lexer *lexer);
char			*get_token(t_tokens token);
/////////////////7tal hna ///////////////

#endif
