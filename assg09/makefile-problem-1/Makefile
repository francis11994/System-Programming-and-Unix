SUMMARY=$(wildcard *.score)
OUTPUT=$(patsubst %.score, %.summary, $(SUMMARY))
all : $(OUTPUT)
%.summary : %.score %.total
	cat HDR $*.score $*.total > $@
clean : 
	/bin/rm -f *.summary
