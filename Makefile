NAME			= Minishell

SRCS	= 	minishell.c lexer.c utils.c linked.c \

CC				= cc
RM				= rm -f
#CFLAGS			= -Wall -Wextra   -g3 -fsanitize=address
CFLAGS			= -Wall -Wextra -Werror #-g3 -fsanitize=address
OBJS			= $(SRCS:.c=.o)

all:			$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline


clean:
	$(RM) $(OBJS) 

fclean:clean 
	$(RM) $(NAME) 

re: fclean all