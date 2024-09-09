NAME	:= philo_bonus
FILES   := philo.c philo_utils.c philo_utils_II.c ft_routine.c
CFLAGS	:= -Wextra -Wall -Werror
HEADER  := philo.h
OFILES  := $(FILES:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -rf $(NAME)

re: clean all