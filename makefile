COMPILER = gcc
FILES = myshell.c prompt.c runfile.c runner.c sigmanager.c jobid.c piperunner.c
NAME = prueba
FLAGS = -Wall -pedantic -Werror

all :
	$(COMPILER) $(FLAGS) -o $(NAME) $(FILES)
	./prueba