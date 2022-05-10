NAME = philo
SRCS = philo.c\
	ft_isdigit.c
$(NAME) : $(SRCS)
	CC -pthread $(SRCS) -g -o $(NAME)
all : $(NAME)
clean :
	rm $(NAME)
re : clean all