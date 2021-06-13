CC=gcc
CFLAGS=-Wall
LDFLAGS=

BUILD_FOLDER=build/

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS +=
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS +=
endif

EXEC=$(BUILD_FOLDER)webc.exe
SRC= $(wildcard src/*.c)
OBJ= $(patsubst %.c,%.o,$(subst src/,$(BUILD_FOLDER),$(SRC)))


all:
	@mkdir -p build
ifeq ($(DEBUG),yes)
	@echo "Generating in debug mode"
else
	@echo "Generating in release mode"
endif
	@echo "$(OBJ)"
	@$(MAKE) $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_FOLDER)%.o: src/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY : clean
clean:
	@rm -rf $(BUILD_FOLDER)*.o


