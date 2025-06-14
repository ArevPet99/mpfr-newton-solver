CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lmpfr -lgmp

# Targets
TARGETS = newton_single newton_system mpfr_examples

all: $(TARGETS)

newton_single: newton_single.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

newton_system: newton_system.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

mpfr_examples: mpfr_examples.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(TARGETS)

test: all
	@echo "Testing MPFR examples:"
	./mpfr_examples
	@echo "\n" 
	@echo "Testing single variable Newton method:"
	./newton_single
	@echo "\n" 
	@echo "Testing system Newton method:"
	./newton_system

.PHONY: all clean test 