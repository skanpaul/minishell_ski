# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 16:27:19 by gudias            #+#    #+#              #
#    Updated: 2022/04/13 18:36:24 by gudias           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -lreadline
INCL	= -I incs
RM		= rm -f

LIBFT	= libft/libft.a

SRCSDIR	= srcs
OBJSDIR	= objs

SRCS	= minishell.c lexing.c run_cmd.c errors.c 

OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@echo "$(YELLOW)Compiling $(DEFAULT)$<"
	@mkdir -p $(OBJSDIR)
	@$(CC) $(CLFAGS) $(INCL) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Creating executable..$(DEFAULT)"
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)---> ./$@ is ready$(DEFAULT)"

$(LIBFT):
	@echo "$(YELLOW)Preparing Libft..$(DEFAULT)"
	@make -C libft 1>/dev/null 2>/dev/null
	@echo "$(CYAN)---> Libft ready$(DEFAULT)"

clean:
	@$(RM) -r $(OBJSDIR)
	@echo "$(RED)Removed $(CYAN)objs/$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(CYAN)./$(NAME)$(DEFAULT)"

libclean: 
	@make fclean -C libft 1>/dev/null 2>/dev/null
	@echo "$(RED)Removed $(CYAN)Libft$(DEFAULT)"

fullclean: fclean libclean

bonus: re

re: fclean all

.PHONY: all clean fclean re bonus libclean fullclean

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
