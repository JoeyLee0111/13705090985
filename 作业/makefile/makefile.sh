VPATH=src include
main = server.o db.o net.o ui.o
	gcc -o $@ $<
server.o : server.c server.h 
	gcc -o $@ $^
ui.o : ui.c ui.h 
	gcc -o $@ $<

database =  db.o
	gcc -o $@ $<
db.o : db.c db.h
	gcc -o $@ $^
	
net = net.o
	gcc -o $@ $<
net.o :net.c net.h
	gcc -o $@ $^
	
ui = ui.o
	gcc -o $@ $<
ui.o: ui.c ui.h
	gcc -o $@ $^
net.o :net.c net.h
	gcc -o $@ $<
db.o : db.c db.h
	gcc -o $@ $<

.PHONY: clean
clean:
	-rm -f edit $(objects) 
