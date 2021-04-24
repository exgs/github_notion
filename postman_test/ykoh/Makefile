SRCS		=	main.cpp\
			HttpMessage.cpp
NAME		=	webserv
CC		=	clang++
CFLAGS		= -std=c++98 -g2 -fsanitize=address # -Wall -Wextra -Werror
RM		=	rm -f

$(NAME)		:
			$(CC) $(CFLAGS) $(SRCS) $^ -o $@

all		:	$(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
