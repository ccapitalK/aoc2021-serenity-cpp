PROGRAM = day05
OBJS = main.o
CXXFLAGS = -g -std=c++2a

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $(OBJS) -lmain -lcore

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm $(OBJS) $(PROGRAM)

run:
	./$(PROGRAM)
