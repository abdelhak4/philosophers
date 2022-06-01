NAME = philo
SRCS = philo.c\
	ft_atoi.c philo_utlis.c habits.c

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(SRCS)
	cc  $(SRCS) -g -o $(NAME)
clean :
	rm -f $(NAME)
fclean : clean
re : fclean all
.PHONY: clean all clean re fclean
