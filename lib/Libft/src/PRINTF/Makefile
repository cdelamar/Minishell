NAME = libftprintf.a

SRC = 	ft_p.c \
	ft_puthexa.c \
	ft_putchar.c \
	ft_putnbr.c \
	ft_putstr.c \
	ft_putunbr.c \
	ft_printf.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar rc

OBJS = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean $(NAME)
