all: run

run: main.cxx EffTool.cxx
	g++ $^ -o $@ `root-config --cflags --libs` -std=c++11