GCC = gcc -Wall -Werror

.PHONY: all 

all: bush

bush: bush.c 
	$(GCC) bush.c -o bush
		


