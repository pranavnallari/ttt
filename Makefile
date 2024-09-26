all:
	gcc ttt.c -o ttt -lncurses -Wall -Wextra -pedantic

clean:
	rm -rf ttt && clear

run:
	./ttt
