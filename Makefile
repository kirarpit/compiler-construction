all:	src

src:	FORCE
	make -C src

clean:	topclean
	make -C src clean

realclean:	topclean
	make -C src realclean

test:	FORCE
	make -C src test

tar:	topclean
	make -C src tar

topclean:	FORCE
	rm -f *~
	rm -f notes/*~

.PHONY:	FORCE
