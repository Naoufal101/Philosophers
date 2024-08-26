NAME	:= philo
FILES   := philo.c philo_utils.c phio_utils_II.c
CFLAGS	:= -Wextra -Wall -Werror
HEADER  := philo.h
OFILES  := $(FILES:.c=.o)

all: $(NAME)


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) -fsanitize=address

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -rf $(NAME)

re: clean all