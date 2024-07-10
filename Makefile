#-----------------------Flags_and_Name---------------------
NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread -Iinclude -g
CREAD	=	-lreadline

#-L/opt/homebrew/lib 
#------------------------Source-----------------------------

# Sources and objects
FILES = main \
		parsing \
		error \
		tools \
		libft/all_lst \
		libft/ft_strcmp \
		libft/ft_split \
		libft/ft_strlen \
		free_all \
		libft/ft_bzero \
		libft/ft_isalpha \
		libft/ft_strjoin \
		path/environement \
		path/tool_of_environement \
		split_dop/ft_split_boosted \
		split_dop/count_word

SRCS = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix obj/, $(addsuffix .o, $(FILES)))

#------------------------Colors-----------------------------

define generate_random_color
python3 -c "import random; \
print(''.join(['\033[38;5;' + str(random.randint(16, 255)) + 'm' + c + '\033[0m' for c in '$(1)']))"
endef

#------------------------Rules------------------------------

all:	${NAME}

obj:
	mkdir -p obj
	mkdir -p obj/libft
	mkdir -p obj/split_dop
	mkdir -p obj/path

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(CREAD)

$(NAME): obj ${OBJS}
		@$(call generate_random_color, $(CC) $(CFLAGS) -o $@ $(OBJS))
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CREAD)


obj/%.o: src/%.c
	@$(call generate_random_color, $(CC) $(CFLAGS) -c $< -o $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}
		rm -rf obj
	#	rm -f lib/libft.a
	#	make clean -C lib

re:	fclean all

.PHONY: all clean fclean re
