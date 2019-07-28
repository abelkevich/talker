DBUILD = ./build/
DBUILD_LINUX = $(DBUILD)linux/x86/
DSRC = ./src/
DTESTS = ./tests/


all: prepare talker tests run_tests

talker: $(DSRC)Makefile
	$(MAKE) -C $(DSRC)

tests: $(DTESTS)Makefile
	$(MAKE) -C $(DTESTS)

clean: $(DBUILD)
	rm -rf $^

prepare:
	mkdir -p $(DBUILD_LINUX)

run_tests:
	#export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(DBUILD_LINUX)
	#print $(LD_LIBRARY_PATH)
	$(DBUILD_LINUX)tests
