# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 15:13:39 by cdelamar          #+#    #+#              #
#    Updated: 2024/10/03 03:07:46 by cdelamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

FILES = ft_atoi \
	ft_bzero \
	ft_itoa \
	ft_isalnum \
	ft_isalpha \
	ft_isascii \
	ft_isdigit \
	ft_isprint \
	ft_tolower \
	ft_toupper \
	ft_split \
	ft_strtrim \
	ft_strjoin \
	ft_strlcpy \
	ft_strdup \
	ft_strnstr \
	ft_strlcat \
	ft_strrchr \
	ft_strchr \
	ft_substr \
	ft_memcpy \
	ft_strmapi \
	ft_striteri \
	ft_strncmp \
	ft_strcmp \
	ft_freetab \
	ft_strlen \
	ft_memcpy \
	ft_memchr \
	ft_memmove \
	ft_memset \
	ft_calloc \
	ft_memcmp \
	ft_putchar_fd \
	ft_putnbr_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_binary \
	ft_error_message \
	ft_strcat \
	ft_realloc_string \
	ft_flood_fill

BONUS =	ft_lstnew \
	ft_lstadd_front \
	ft_lstadd_back \
	ft_lstsize \
	ft_lstlast \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_BONUS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(BONUS)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(BONUS)))

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus : $(OBJS_BONUS)
	$(AR) $(NAME) $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
