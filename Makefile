all:
	gcc ttt.c -lncurses -o ttt -Wall -Wextra -pedantic

clean:
	rm -rf ttt && clear

run:
	./ttt
