NAME			= minishell

SRCS	= 	main.c lexer.c utils.c linked.c test.c print_stuffs.c ft_isalnum.c ft_strcmp.c \
			ft_isdigit.c ft_strjoin.c expand.c expand_2.c expand_3.c parser.c \
			ft_split.c \

CC				= cc
RM				= rm -f
# CFLAGS			= -Wall -Wextra  -g3 -fsanitize=address
CFLAGS			= -Wall -Wextra -Werror -g3 -fsanitize=address
# CFLAGS			= -Wall -Wextra -Werror 
OBJS			= $(SRCS:.c=.o)

all: $(NAME)
	@clear 
	@./minishell

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline


clean:
	$(RM) $(OBJS) 

fclean:clean 
	$(RM) $(NAME) 

re: fclean all