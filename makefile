compile:
	gcc dirinfo.c -o dirtest
run: dirtest
	./dirtest $(ARGS) 
clean:
	rm dirtest 
	rm *~