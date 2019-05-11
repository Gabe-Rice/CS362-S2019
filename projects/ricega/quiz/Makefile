CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	./testme &> testresult.out


#########

runtests: testme
	gcov testme.c >> testresult.out
	cat testme.c.gcov >> testresult.out
	
	
clean:
	rm -f *.o testme testme.exe  *.gcov *.gcda *.gcno *.so *.out