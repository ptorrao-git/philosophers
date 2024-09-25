# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 11:02:10 by ptorrao-          #+#    #+#              #
#    Updated: 2024/09/25 15:52:32 by ptorrao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror
NAME			= philo

INC				= -I./include

GENERAL			= philo.c
UTILS			= init.c libft.c create.c free.c
VALIDATIONS		= check_args.c

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH 			= src\
					src/utils\
					src/validations\
					src/init\
					src/free\

SRC				= $(GENERAL)\
					$(UTILS)\
					$(VALIDATIONS)\
				
OBJ_DIR			= obj

OBJ 			= $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all:			$(NAME)

$(OBJ_DIR):
				mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME):		$(OBJ_DIR) $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
				$(RM) $(OBJ)

fclean: 		clean
				$(RM) $(NAME) $(OBJ_DIR)

re: 			fclean all

.PHONY: 		all clean fclean re