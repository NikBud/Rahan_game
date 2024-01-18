CC = gcc
OPTIONS = -Wall -ansi -pedantic
EXECUTABLE = rahan
SOURCE = $(wildcard *.c)
OBJ_DIR = obj_dir
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCE:.c=.o)))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPTIONS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(OPTIONS) -MMD -c $< -o $@

-include $(OBJ_DIR)/*.d

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d