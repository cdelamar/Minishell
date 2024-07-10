# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 21:54:20 by cdelamar          #+#    #+#              #
#    Updated: 2024/07/03 14:11:29 by cdelamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = lib/libft.a

CC = cc
CFLAGS =	-g -Iincludes -Ilib/includes
LFLAGS =	-Llib -lft -lreadline

SRC_DIRS = src/ builtins/
OBJ_DIR = obj/

SRC_FILES =	command main exec memory path signal redirection heredoc#token

BUILTIN_FILES =	call_builtins ft_echo ft_env ft_pwd ft_unset ft_cd ft_export

SRC_SRCS = $(addprefix src/, $(addsuffix .c, $(SRC_FILES)))
BUILTIN_SRCS = $(addprefix builtins/, $(addsuffix .c, $(BUILTIN_FILES)))
SRCS = $(SRC_SRCS) $(BUILTIN_SRCS)

SRC_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
BUILTIN_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BUILTIN_FILES)))
OBJS = $(SRC_OBJS) $(BUILTIN_OBJS)

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
	@echo "\033[35m✔ Compiling source files...\033[37m"
	@$(CC) -o $@ $(OBJS) $(LFLAGS)
	@echo "\033[0;35m✔ Executable created.\033[37m"

$(LIBFT):
	@make -C lib

$(OBJ_DIR)%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m✔ Compiled $<.\033[37m"

$(OBJ_DIR)%.o: builtins/%.c
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
$(OBJS): | $(LIBFT)
