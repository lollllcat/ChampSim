bin := ./bin

cc := g++


src = $(shell find ./ -name "*.cpp" -exec basename {} \;)

dep = $(shell find ./ -name "*.h")

obj = $(src:%.cpp=%)

.PHONY: all

all: $(obj)

%: %.cpp $(dep)
	$(cc) -std=c++11 -g -O3 $< -DORG -o $(bin)/$@

clean:
	rm -rf $(bin)/*
