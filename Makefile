# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 21:54:20 by cdelamar          #+#    #+#              #
#    Updated: 2024/11/30 02:29:01 by cdelamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = lib/libft.a

CC = cc
CFLAGS = -g -Iincludes -Ilib/includes -pthread -Wall -Wextra -Werror
LFLAGS = -Llib -lft -lreadline

SRC_DIRS = src_executing/ builtins/ src_parsing/
OBJ_DIR = obj/

EXECUTING_FILES = command main_exec pipe_args copy_token ft_builtins exec memory pipe_syntax pipe_path path signal pipe_exits basic_safety signal_2 redirection redirect_handler heredoc fd basic_exec basic_exec_2 pipe_exec safety pipe_commands
BUILTIN_FILES = call_builtins ft_echo ft_env ft_pwd ft_unset ft_cd ft_export ft_exit
PARSING_FILES = main parsing error tools \
				libft/all_lst free_all \
                libft/ft_isalpha libft/sub_chr_cpy libft/ft_strtrim \
                split_dop/ft_split_boosted split_dop/count_word \
                split_dop/check_char split_dop/verif_error \
                cat_quote/tools_for_cat cat_quote/main_cat_2 \
                cat_quote/to_tab cat_quote/lstnew_with_cat \
                cat_quote/tools_lstnew print_ascii \
				path/tools_of_path path/main_envp \
                libft/ft_strjoin libft/ft_lstdelone \
                libft/ft_strlcpy libft/ft_strlen libft/ft_strcmp \
                libft/ft_bzero libft/ft_strdup \
				split_dop/modif_pipe \
				gestion_list \
				verif_result \
				main_loop \

EXEC_SRCS = $(addprefix src_executing/, $(addsuffix .c, $(EXECUTING_FILES)))
BUILTIN_SRCS = $(addprefix builtins/, $(addsuffix .c, $(BUILTIN_FILES)))
PARSE_SRCS = $(addprefix src_parsing/, $(addsuffix .c, $(PARSING_FILES)))
SRCS = $(EXEC_SRCS) $(BUILTIN_SRCS) $(PARSE_SRCS)

EXEC_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(EXECUTING_FILES)))
BUILTIN_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BUILTIN_FILES)))
PARSE_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSING_FILES)))
OBJS = $(EXEC_OBJS) $(BUILTIN_OBJS) $(PARSE_OBJS)

VALGRIND_SUPP = valgrind.supp

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[35m✔ Cleaned object files.\033[37m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[35m✔ Cleaned all files.\033[37m"

re: fclean $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[35m✔ Compiling source files...\033[37m"
	@$(CC) -o $@ $(OBJS) $(LFLAGS)
	@echo "\033[0;35m✔ Executable created.\033[37m"

$(LIBFT):
	@make -C lib

$(OBJ_DIR)%.o: src_executing/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m✔ Compiled $<.\033[37m"

$(OBJ_DIR)%.o: builtins/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m✔ Compiled $<.\033[37m"

$(OBJ_DIR)%.o: src_parsing/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m✔ Compiled $<.\033[37m"

# Run with Valgrind
# readline() leaks disabled
valgrind: $(NAME)
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=$(VALGRIND_SUPP) ./$(NAME)

rl_on: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# Run the test script
tester: $(NAME)
	@chmod +x test_minishell_commands.sh
	@./test_minishell_commands.sh

# Debug with GDB
gdb: $(NAME)
	@echo "\033[35m✔ Launching GDB...\033[37m"
	@gdb -tui --args ./$(NAME)

.PHONY: all clean fclean re valgrind tester gdb

# Avoid to rebuild the lib
$(OBJS): | $(LIBFT)


