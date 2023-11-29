HADOOP_DEV_HOME = $(HADOOP_HOME)
CC=g++
CPPFLAGS = -m64 
SRCS = readhdfs.cpp
PROGRAM = readhdfs

INC_PATH = -I$(HADOOP_DEV_HOME)/include
LIB_PATH = -L$(HADOOP_DEV_HOME)/lib/native
LIBS = -lhdfs -lpthread

$(PROGRAM):$(SRCS)
	$(CC) $(CPPFLAGS) $(INC_PATH) $< -Wall $(LIB_PATH) $(LIBS)  -g -o $@
clean:
	rm -f *.o readhdfs