objects = list.o zmalloc.o main.o
header  = list.h zmalloc.h

cc = /usr/local/Cellar/gcc/7.3.0/bin/g++-7

edit : $(objects)
	$(cc) -o edit $(objects)

$(objects) : $(header)

.PHONY : clean
clean :
	rm edit $(objects)