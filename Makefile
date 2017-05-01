SOURCE=src/*.cpp
MYPROGRAM=arpgyp
MYINCLUDES=includes
BIN=bin/Debug

CC = g++

CPPFLAGS = -g -Wall -fpermissive -std=gnu++11 -pthread -Iinclude

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) -I$(MYINCLUDES) $(SOURCE) -o$(BIN)/$(MYPROGRAM) $(CPPFLAGS)

clean:
	rm $(MYPROGRAM)



