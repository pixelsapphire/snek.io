.PHONY: all build client server run-client run-server clean

all:
	$(error No target selected. Please select a target by running one of the following: 'make client' or 'make server')

build:
	mkdir -p build

client: build
	$(MAKE) -f make-client

server: build
	$(MAKE) -f make-server

run-client: client
	./build/client/client

run-server: server
	./build/server/server

clean:
	rm -rf build