# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 21:54:20 by cdelamar          #+#    #+#              #
#    Updated: 2024/06/03 17:15:37 by cdelamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = lib/libft.a

CC = cc
CFLAGS =	-g -Iincludes -Ilib/includes
LFLAGS =	-Llib -lft -lreadline

SRC_DIR = src/
OBJ_DIR = obj/
FILES =	main exec memory path token

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

VALGRIND_SUPP = valgrind.supp

all: $(NAME)

clean :
	@rm -rf $(OBJ_DIR)
	@echo "\033[35m✔ Cleaned object files.\033[37m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[35m✔ Cleaned all files.\033[37m"

re: fclean $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[35m✔ Compilating sources files...\033[37m"
	@$(CC) -o $@ $(OBJS) $(LFLAGS)
	@echo "\033[0;35m✔ Executable created.\033[37m"

$(LIBFT):
	@make -C lib

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m✔ Compiled $<.\033[37m"

# Run with Valgrind
# readline() leaks disabled
valgrind: $(NAME)
	valgrind --leak-check=full --track-origins=yes --suppressions=$(VALGRIND_SUPP) ./$(NAME)

rl_on: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re valgrind

# Avoid to rebuild the lib
$(OBJS) : | $(LIBFT)
