NAME = philo_bonus
SRCS = philo_bonus.c\
	ft_atoi.c semulation.c

CFLAGS =  -lpthread

bonus : $(NAME)

$(NAME) : $(SRCS)
	cc $(CFLAGS) $(SRCS) -o $(NAME)
clean :
	rm -f $(NAME)
fclean : clean
re : fclean bonus
.PHONY: clean bonus clean re fclean