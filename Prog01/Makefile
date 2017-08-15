CXX = g++-4.7 -std=c++11
OPTS = -g -O3
WARN = -Wall -Werror
DEPS = -MMD -MF $*.d
INCL =

OBJS = test_list.o test_vector.o test_stack.o test_queue.o timing.o timing_list.o timing_stack.o

default: $(OBJS)

docs:
	doxygen DoxygenSetup/doxyfile.prog01

clean:
	rm -rf Dependencies $(OBJS)

%.o: %.cpp
	$(CXX) $(OPTS) $(WARN) $(DEPS) $(INCL) $< -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

-include Dependencies

