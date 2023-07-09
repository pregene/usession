CC=g++

# BUILD NUMBER를 파일에서 가져온다.
FILE=BUILDNO
BNO := $(shell cat ${FILE})
# VERSION 정보를 파일에서 가져온다..
VER=VERSION
VNO := $(shell cat ${VER})

# BUILD NUMBER와 VERSION정보를 DEFINE을 이용하여 빌드 할 때 사용한다.
# BUILDNO_INFO: BUILD NUMBER
# VERSION_INFO: VERSION 정보
CFLAGS=-Wall -DBUILDNO_INFO=$(BNO) -DVERSION_INFO=\"$(VNO)\"

LIBS=
EXEC=usession
SOURCE=source/main.cpp

all:
	$(CC) $(SOURCE) $(CFLAGS) $(LIBS) -o bin/$(EXEC) 
	
# BUILD가 완료되었으므로, 다음 빌드을 위해 BUILD NUMBER를 1 증가한다..
	@echo $$(($$(cat $(FILE)) + 1)) > $(FILE)
  
clean:
	rm -f bin/$(EXEC) 