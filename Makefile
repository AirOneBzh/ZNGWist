##########################################################

CFLAGS = -g -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`



prog: cleanprog wist
	-rm -rf *.o

all: prog progpropre pdf

wist: wist.o menu.o interface.o
	$(CC) wist.o menu.o interface.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o wist

wist.o: wist.c wist.h
	$(CC) -c wist.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

menu.o: menu.c menu.h
	$(CC) -c menu.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

interface.o: interface.c interface.h
	$(CC) -c interface.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

pdf: latex cleanlatex

latex: rapport.tex
	pdflatex rapport.tex

clean:
	rm -rf *.o wist *.aux *.fdb_latexmk *.fls *.log *.synctex.gz *~

cleanprog:
	rm -rf *.o wist *~

progpropre:
	-rm -rf *.o *~

cleanlatex:
	rm -rf *.aux *.fdb_latexmk *.fls *.log *.synctex.gz *~
