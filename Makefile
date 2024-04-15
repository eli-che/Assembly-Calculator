all: build_lexyacc calc3.exe

calc3.exe: bin/calc3i.exe

bin/%.exe: lexyacc-code/%.c build_lexyacc
	gcc -I lexyacc-code lexyacc-code/y.tab.o lexyacc-code/lex.yy.o $< -o $@

build_lexyacc:
	bison -y -d lexyacc-code/calc3.y -o lexyacc-code/y.tab.c
	flex -o lexyacc-code/lex.yy.c lexyacc-code/calc3.l
	gcc -I lexyacc-code -c lexyacc-code/y.tab.c -o lexyacc-code/y.tab.o
	gcc -I lexyacc-code -c lexyacc-code/lex.yy.c -o lexyacc-code/lex.yy.o
	@$(CC) -c -o src/fact.o src/fact.s
	@ar rcs lib/lib.a src/fact.o
	@$(CC) -c -o lib/fact.o src/fact.s
	@ar rcs lib/lib.a lib/fact.o



clean:
	rm -f -v outputexe/*

