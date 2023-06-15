objfiles = main.o panel.o samba.o network.o user.o
curses = -lncurses -lpanel -lmenu


main.out : $(objfiles)
	gcc -g -o main.out $^ $(curses)


main.o : main.c main.h
	gcc -c -g $^ $(curses)


network.o : network.c main.h
	gcc -c -g $^ $(curses)


samba.o : samba.c main.h
	gcc -c -g $^ $(curses)


panel.o : panel.c main.h
	gcc -c -g $^ $(curses)


user.o : user.c main.h
	gcc -c -g $^ $(curses)


clean:
	rm *.o *.gch
