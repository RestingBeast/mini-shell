CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make
NAME = minishell
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDE = -Iinclude -I$(LIBFT_DIR)
SRC = src/minishell.c \
      src/lexer.c
OBJ = $(SRC:.c=.o)

TEST = run-tests
TEST_LIB_OBJ = $(filter-out src/minishell.o, $(OBJ))
TEST_SRC = tests/lexer.test.c \
	   tests/test_utils.c
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -f $(OBJ) $(TEST_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

image:
	docker build -t minishell-criterion .

# This target must be run inside the Docker container created by `make image`.
test: $(TEST_OBJ) $(TEST_LIB_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TEST) \
	$(TEST_OBJ) $(TEST_LIB_OBJ) -lcriterion && ./$(TEST) -f -S --color=always;

.PHONY: all clean fclean re image test
