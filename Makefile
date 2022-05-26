NAME = philo
SRCS = philo.c\
	ft_atoi.c philo_utlis.c habits.c
$(NAME) : $(SRCS)
	CC   $(SRCS)  -g -o $(NAME)
all : $(NAME)
clean :
	rm $(NAME)
re : clean all