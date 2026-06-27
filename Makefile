CC = gcc
CFLAGS := -MMD -Wall -Wextra -pedantic -std=c17 -I inc
 
SRC=$(wildcard src/*.c)
OBJ=$(SRC:%.c=%.o)
DEP=$(OBJ:%.o=%.d)

EXE=bristle
TEST=tests/test-runner
TARGET=/usr/local
 
all: $(EXE)
 
clean:
	$(RM) $(OBJ) $(DEP) $(EXE) $(TEST)
 
install: all
	install -D -m 755 $(EXE) $(TARGET)/bin/$(EXE)
 
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

-include $(DEP)
