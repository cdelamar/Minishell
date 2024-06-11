NAME = libft.a


CC =	cc
CFLAGS	=	-Wall -Wextra -Werror -Iinclude

LIB = ft_isalpha ft_toupper ft_isdigit ft_tolower \
ft_isalnum ft_strchr ft_isascii ft_strrchr \
ft_isprint ft_strncmp ft_strlen ft_memchr \
ft_memset ft_memcmp ft_bzero ft_strnstr \
ft_memcpy ft_atoi ft_memmove ft_strlcpy \
ft_strlcat ft_calloc ft_strdup ft_substr \
ft_strjoin ft_strtrim ft_itoa ft_strmapi \
ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd \
ft_putnbr_fd ft_split

BONUS = ft_lstsize ft_lstnew ft_lstmap ft_lstlast \
ft_lstiter ft_lstdelone ft_lstclear ft_lstadd_front \
ft_lstadd_back

PRINTF = ft_printf ft_p ft_putchar ft_puthexa ft_putnbr ft_putstr ft_putunbr

GET_NEXT_LINE = get_next_line get_next_line_utils


SRC_FILES = $(addprefix src/LIBFT/, $(LIBFT)) \
$(addprefix src/GET_NEXT_LINE/, $(GET_NEXT_LINE)) \
$(addprefix src/PRINTF/, $(PRINTF))

FILES = $(LIBFT) $(GET_NEXT_LINE) $(PRINTF) 

AR = ar rcs
OBJ_DIR = obj/

		
SRCS = $(addsuffix .c, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

BONUSOBJS	= ${BONUS:.c=.o}

define generate_random_color
python3 -c "import random; \
print(''.join(['\033[38;5;' + str(random.randint(16, 255)) + 'm' + c + '\033[0m' for c in '$(1)']))"
endef


all:	$(OBJ_DIR) $(OBJS)
	@echo "\033[32m✔ Compilation des fichiers sources...\033[31m"
	@ar -rcs $(NAME) $(OBJS)
	@echo "\033[1;34m✔ ---------------------- \033[37m"
	@$(call generate_random_color, ✔ ✨Bibliothèque créée✨)
	@echo "\033[1;34m✔ ---------------------- \033[37m"

clean:
		@echo "\033[32m✔ Suppression des fichiers sources...\033[35m"
		rm -rf $(OBJ_DIR) $(BONUSOBJS)
		@echo "\033[32m✔ Fichier sources supprimer...\033[37m"

fclean:	clean
		@echo "\033[32m✔ Suppression de la bibliothèque en cours...\033[31m"
		rm -f ${NAME}
		@echo "\033[32m✔ Bibliothèque supprimer...\033[37m"

re:	fclean all

bonus : ${OBJS} ${BONUSOBJS}
		ar rc ${NAME} ${OBJS} ${BONUSOBJS}
		
obj/%.o: src/*/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ_DIR):
	@mkdir -p $@

.PHONY: all clean fclean re
