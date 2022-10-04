clearCompiledFiles: 
	-rm ./00-fork/main ./00-fork_

	-rm ./01-fork-with-wait/main ./01-fork-with-wait_

	-rm ./02-fork-with-pipe/main ./02-fork-with-pipe_

	-rm ./03-threads/main ./03-threads_

	-rm ./04-threads-zaehlen-abwaerts/main ./04-threads-zaehlen-abwaerts_

	-rm ./05-threads-berechnen/main ./05-threads-berechnen_

	-rm ./06-timer-signal/main ./06-timer-signal_

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
	gcc -o ./00-fork_ ./00-fork/main.c

01-fork-with-wait: FORCE
	gcc -o ./01-fork-with-wait_ ./01-fork-with-wait/main.c

02-fork-with-pipe: FORCE
	gcc -o ./02-fork-with-pipe_ ./02-fork-with-pipe/main.c

03-threads: FORCE
	gcc -o ./03-threads_ ./03-threads/main.c

04-threads-zaehlen-abwaerts: FORCE
	gcc -o ./04-threads-zaehlen-abwaerts_ ./04-threads-zaehlen-abwaerts/main.c

05-threads-berechnen: FORCE
	gcc -o ./05-threads-berechnen_ ./05-threads-berechnen/main.c

06-timer-signal: FORCE
	gcc -o ./06-timer-signal_ ./06-timer-signal/main.c
