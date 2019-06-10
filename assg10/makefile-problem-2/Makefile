SUMMARY=$(wildcard *.files)
OUTPUT=$(patsubst %.files, %.tar, $(SUMMARY))
all : $(OUTPUT)
%.tar : %.files
	tar -cf $*.tar $*.files
clean : 
	/bin/rm -f *.tar
