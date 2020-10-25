CFLAGS=
LIBS=-lroot -lbe
CC=g++
OBJS = LibreOfficeLauncher.o

all: LibreOffice

LibreOffice: $(OBJS)
	# Calc
	$(CC) -o "LibreOffice Calc" $^ $(LIBS)
	rc libreoffice-calc-res.rdef
	xres -o "LibreOffice Calc" libreoffice-calc-res.rsrc
	mimeset -f "LibreOffice Calc"
	# Writer
	$(CC) -o "LibreOffice Writer" $^ $(LIBS)
	rc libreoffice-writer-res.rdef
	xres -o "LibreOffice Writer" libreoffice-writer-res.rsrc
	mimeset -f "LibreOffice Writer"
	# Draw
	$(CC) -o "LibreOffice Draw" $^ $(LIBS)
	rc libreoffice-draw-res.rdef
	xres -o "LibreOffice Draw" libreoffice-draw-res.rsrc
	mimeset -f "LibreOffice Draw"
	# Impress
	$(CC) -o "LibreOffice Impress" $^ $(LIBS)
	rc libreoffice-impress-res.rdef
	xres -o "LibreOffice Impress" libreoffice-impress-res.rsrc
	mimeset -f "LibreOffice Impress"
	# Math
	$(CC) -o "LibreOffice Math" $^ $(LIBS)
	rc libreoffice-math-res.rdef
	xres -o "LibreOffice Math" libreoffice-math-res.rsrc
	mimeset -f "LibreOffice Math"
	# Database
	$(CC) -o "LibreOffice Database" $^ $(LIBS)
	rc libreoffice-database-res.rdef
	xres -o "LibreOffice Database" libreoffice-database-res.rsrc
	mimeset -f "LibreOffice Database"

.cpp.o:
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f LibreOffice\ {Calc,Database,Draw,Impress,Math,Writer} *.rsrc $(OBJS)
