CPPFILES = main systeminfo
FILES = $(addsuffix .cpp, $(CPPFILES) )
OBJS  = $(addsuffix .o, $(CPPFILES) )

CXX 		= g++
CXXFLAGS = -std=c++11 -O2 --static

compile: $(FILES)
	$(MAKE) $(OBJS)
	$(CXX) -std=c++11 -o sysinfo $(CXXFLAGS)  $(OBJS)

clean:
	rm -rf sysinfo $(OBJS)
