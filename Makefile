main:
	g++ -g simulator.cpp phone.cpp environment.cpp basestation.cpp utils.cpp \
		-lboost_program_options -o simulator
clean:
	rm -f *.gch *.txt simulator
