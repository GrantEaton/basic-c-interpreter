interpreter_out: interpreter.o
	g++ -o interpreter interpreter.o
interpreter.o: interpreter.cpp
	g++ -g -c interpreter.cpp
clean:
	rm -f *.o
	rm -f interpreter_out
