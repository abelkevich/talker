PROJECT_NAME = libtalker.so
OBJS = router.o client.o msg.o 
CFLAGS = -Wall -fPIC -std=c++17 -g
LDFLAGS = -pthread -shared -Wl,-soname,libtalker.so
DBUILD = ../build/linux/x86/
DINC = ../include/
DSRC = ./

.ONESHELL:

all: $(OBJS) link

%.o: $(DSRC)%.cpp
	$(CXX) $(CFLAGS) -I $(DINC) -o $(DBUILD)$@ -c $<

link: $(OBJS)
	cd $(DBUILD)
	$(CXX) $(LDFLAGS) -o $(PROJECT_NAME) $^ 
