FLAGS = g++ -pedantic-errors -std=c++11
data.o: data.cpp data.h
	$(FLAGS) -c data.cpp
display_start.o: display_start.cpp display_start.h
	$(FLAGS) -c display_start.cpp
play.o: play.cpp play.h
	$(FLAGS) -c play.cpp
2048.o: 2048.cpp play.h data.h display_start.h
	$(FLAGS) -c 2048.cpp
2048: play.o 2048.o display_start.o data.o
	$(FLAGS) play.o 2048.o display_start.o data.o -o 2048
clean:
	rm -f play.o 2048.o display_start.o data.o 2048
.PHONY: clean
