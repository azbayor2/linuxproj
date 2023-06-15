objfiles = main.o panel.o samba.o network.o user.o reset.o
curses = -lncurses -lpanel -lmenu


main.out : $(objfiles)
	gcc -g -o main.out $^ $(curses)


main.o : main.c
	gcc -c -g $^ $(curses)


network.o : network.c
	gcc -c -g $^ $(curses)


samba.o : samba.c
	gcc -c -g $^ $(curses)


panel.o : panel.c
	gcc -c -g $^ $(curses)


user.o : user.c
	gcc -c -g $^ $(curses)

reset.o : reset.c
	gcc -c -g $^ $(curses)

clean:
	rm *.o *.gch
