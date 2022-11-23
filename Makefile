CC = gcc
FLAGS =-Wall -Werror -Wextra -std=c11
LIB =
DEBUG =-g -DDEBUG
DEBUGS =-fsanitize=address
NAME =sprintf

all: $(NAME)

$(NAME): $(NAME).c $(NAME).h
	$(CC) $(FLAGS) $< $(LIB) -o $@

rebuild: clean all

clean:
	rm -rf $(NAME) $(NAME)_debug $(NAME)_debug_san

debug: $(NAME).c $(NAME).h
	$(CC) $(FLAGS) $(DEBUG) $(NAME).c -o $(NAME)_debug

debugsan:
	$(CC) $(FLAGS) $(DEBUG) $(DEBUGS) $(DEBUG) $(NAME).c -o $(NAME)_debug_san

.PHONY: all clean rebuild debug debugsan