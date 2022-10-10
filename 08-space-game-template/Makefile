all: spaceServer spaceClient

spaceServer: spaceServer.c spaceHeader.h
	cc -Wall -Werror -pedantic -g -o spaceServer spaceServer.c -lrt -pthread

spaceClient: spaceClient.c spaceHeader.h
	cc -Wall -Werror -pedantic -g -o spaceClient spaceClient.c -lrt -pthread

clean:
	rm -f spaceServer spaceClient
