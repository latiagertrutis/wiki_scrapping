#******************************************************************************#
#                                                                              #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
#    By: Mateo <teorodrip@protonmail.com>                                      #
#                                                                              #
#    Created: 2018/11/19 16:54:49 by Mateo                                     #
#    Updated: 2018/11/20 14:36:05 by Mateo                                     #
#                                                                              #
#******************************************************************************#

.PHONY: all clean fclean re

SHELL = /bin/bash

NAME = scrap

C_FLAGS = -Wall -Werror -Wextra -lcurl -lxlnt

CC = g++

FUNCS = main.cpp \
		get_search.cpp

SRCS_DIR = srcs/

INC_DIR = includes/

OBJ_DIR = objects/

OBJ = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(FUNCS))

INC = $(wildcard $(INC_DIR)*.hpp)

I := 1

N_SRCS = $(shell ls srcs | wc -l)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@$(CC) $(OBJ) -o $(NAME) $(C_FLAGS)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	@echo -n "Compiling [$(shell echo ${I})/${N_SRCS}] => $(@F)"
	@if $(CC) -c -I $(INC_DIR) $< -o $@ $(C_FLAGS) ; then \
		 echo	" ===>[OK]"; \
	 fi
	@$(eval I=$(shell echo $$(($(I)+1))))

clean:
	@echo "***Cleaning Objects***"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "***Cleaning Executables & Libraries***"
	@rm -f $(NAME)

re: fclean
	@make
