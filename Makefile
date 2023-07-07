CC=g++
CFLAGS=
LIBS=
EXEC=usession
SOURCE=source/main.cpp

all:
  $(CC) $(SOURCE) $(CFLAGS) $(LIBS) -o bin/$(EXEC) 
  
clean:
  rm -f bin/$(EXEC) 