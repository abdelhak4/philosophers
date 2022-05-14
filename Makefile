NAME = philo
SRCS = philo.c\
	ft_atoi.c philo_utlis.c
$(NAME) : $(SRCS)
	CC -pthread -fsanitize=address  $(SRCS) -g -o $(NAME)
all : $(NAME)
clean :
	rm $(NAME)
re : clean all