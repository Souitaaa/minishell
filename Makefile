NAME			= minishell

SRCS	= 	minishell.c\

CC				= cc
RM				= rm -f
#CFLAGS			= -Wall -Wextra   -g3 #-fsanitize=address
CFLAGS			= -Wall -Wextra -Werror 
OBJS			= $(SRCS:.c=.o)

all:			$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline


clean:
	$(RM) $(OBJS) 

fclean:clean 
	$(RM) $(NAME) 

re: fclean all