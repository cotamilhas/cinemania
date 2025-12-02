default:
	gcc -Wall main.c movies.c input.c -o prog.exe && prog.exe

debug:
	gcc -Wall -g main.c movies.c input.c -o prog.exe && prog.exe

clean:
	del prog.exe