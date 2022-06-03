NAME = philo_bonus
SRCS = philo_bonus.c\
	ft_atoi.c\
	semulation_bonus.c\
	utils_bonus.c

CFLAGS =  -Wall -Werror -Wextra -lpthread

bonus : $(NAME)

$(NAME) : $(SRCS)
	cc $(CFLAGS) $(SRCS) -o $(NAME)
clean :
	rm -f $(NAME)
fclean : clean
re : fclean bonus
.PHONY: clean bonus clean re fclean