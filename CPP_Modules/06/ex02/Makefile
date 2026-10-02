NAME = ex02
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Base.cpp

OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
MAKEFLAGS += --no-print-directory

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CPPFLAGS) $(OBJ) -o $@
	@echo "ex02 ready"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Cleaned"

fclean:
	@rm -rf $(NAME) $(OBJ_DIR)
	@echo "Fcleaned"

c: all clean

re: fclean all

.PHONY: clean fclean re all