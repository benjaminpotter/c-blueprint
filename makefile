all: main

main: 
	gcc src/main.c -o bin/main
	chmod +x bin/main

clean:
	rm bin/main
