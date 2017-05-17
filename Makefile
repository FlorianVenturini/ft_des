#
# FT_DES, made by fventuri.
#

#### COMPILATION VARS ####
NAME = ft_des
CC = gcc

CFLAGS = -Wall -Wextra -Werror
C_FILES =	crypt.c \
			ft_ulitoa_base.c \
			main.c \
			print.c

SRCS = $(addprefix srcs/,$(C_FILES))
O_FILES = $(C_FILES:.c=.o)
OBJ = $(addprefix obj/,$(O_FILES))
H_FILES = ft_des.h
INCLUDES = $(addprefix includes/,$(H_FILES))
COMPILE_FLAGS = -I includes

#### COLORS ####
NC		= \033[0m
BLACK	= \033[0;30m
RED		= \033[0;31m
GREEN	= \033[0;32m
ORANGE	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
LGRAY	= \033[0;37m
DGRAY	= \033[1;30m
LRED	= \033[1;31m
LGREEN	= \033[1;32m
YELLOW	= \033[1;33m
LBLUE	= \033[1;34m
LPURPLE	= \033[1;35m
LCYAN	= \033[1;36m
WHITE	= \033[1;37m

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@printf "[FT_DES]: Compiling $(GREEN)$(NAME)$(NC)... "
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@printf "$(LGREEN)OK$(NC)\n"
	@printf "[FT_DES]: $(RED)ALL DONE$(NC)\n"

obj/%.o: srcs/%.c $(INCLUDES)
	@mkdir -p obj
	@printf "[FT_DES]: Compiling $(BLUE)$<$(NC) --> $(BLUE)$@$(NC)... "
	@$(CC) $(CFLAGS) -o $@ -c $< $(COMPILE_FLAGS)
	@printf "$(LGREEN)OK$(NC)\n"

clean:
	@if [ -d obj ]; then \
		printf "[FT_DES]: Removing $(PURPLE).o files$(NC)... "; \
		rm -rf obj; \
		printf "$(LGREEN)OK$(NC)\n"; \
	fi;

fclean: clean
	@printf "[FT_DES]: Removing $(PURPLE)$(NAME)$(NC)... "
	@rm -f $(NAME)
	@printf "$(LGREEN)OK$(NC)\n"

re: fclean all
