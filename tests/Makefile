PROJECT_NAME = tests
OBJS = sample.o
CFLAGS = -Wall -std=c++17 -g
LDFLAGS = -pthread
DBUILD = ../build/linux/x86/
DINC = ../include/
DSRC = ./

.ONESHELL:

all: $(OBJS) link

%.o: $(DSRC)%.cpp
	$(CXX) $(CFLAGS) -I $(DINC) -o $(DBUILD)$@ -c $<

link: $(OBJS)
	cd $(DBUILD)
	$(CXX) $(LDFLAGS) -L. -o $(PROJECT_NAME) $^ -ltalker
