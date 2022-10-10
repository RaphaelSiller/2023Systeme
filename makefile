clearCompiledFiles: 
	-rm -f ./00-fork/main ./_00-fork

	-rm -f ./01-fork-with-wait/main ./_01-fork-with-wait

	-rm -f ./02-fork-with-pipe/main ./_02-fork-with-pipe

	-rm -f ./03-threads/main ./_03-threads

	-rm -f ./04-threads-zaehlen-abwaerts/main ./_04-threads-zaehlen-abwaerts

	-rm -f ./05-threads-berechnen/main ./_05-threads-berechnen

	-rm -f ./06-timer-signal/main ./_06-timer-signal

FORCE:


all: 
	make clearCompiledFiles
	make 00-fork 
	make 01-fork-with-wait
	make 02-fork-with-pipe
	make 03-threads
	make 04-threads-zaehlen-abwaerts
	make 05-threads-berechnen
	make 06-timer-signal
	

00-fork: FORCE
	gcc -o ./_00-fork ./00-fork/main.c

01-fork-with-wait: FORCE
	gcc -o ./_01-fork-with-wait ./01-fork-with-wait/main.c

02-fork-with-pipe: FORCE
	gcc -o ./_02-fork-with-pipe ./02-fork-with-pipe/main.c

03-threads: FORCE
	gcc -o ./_03-threads ./03-threads/main.c

04-threads-zaehlen-abwaerts: FORCE
	gcc -o ./_04-threads-zaehlen-abwaerts ./04-threads-zaehlen-abwaerts/main.c

05-threads-berechnen: FORCE
	gcc -o ./_05-threads-berechnen ./05-threads-berechnen/main.c

06-timer-signal: FORCE
	gcc -o ./_06-timer-signal ./06-timer-signal/main.c
