CC = gcc
#CFLAGS = -g -Wall -DDEBUG
CFLAGS = -g -Wall

DEST = compile

HFILES = error.h  global.h  protos.h symbol-table.h  syntax-tree.h

CFILES = error.c \
	lex.yy.c \
	main.c\
	print.c \
	symbol-table.c\
        syntax-tree.c \
	util.c\
	y.tab.c\
	TAC_generator.c\
	MIPS_generator.c\
	peephole_o1.c\
	basic_block.c\
	liveness_local.c\
	bitvector.c\
	reaching_def.c\
	liveness_global.c\
	live_range.c

OFILES = error.o \
	lex.yy.o \
	main.o \
	print.o \
	symbol-table.o \
        syntax-tree.o \
	util.o \
	y.tab.o \
	TAC_generator.o\
	MIPS_generator.o\
	peephole_o1.o\
	basic_block.o\
	liveness_local.o\
	bitvector.o\
	reaching_def.o\
	liveness_global.o\
	live_range.o

.c.o :
	$(CC) $(CFLAGS) -c $<

$(DEST) : $(OFILES)
	$(CC) -o $(DEST) $(OFILES) -ll

error.o : error.h global.h syntax-tree.h error.c y.tab.h

main.o : global.h main.c

symbol-table.o : global.h symbol-table.h symbol-table.c

syntax-tree.o : global.h syntax-tree.h syntax-tree.c

TAC_generator.o : global.h TAC_generator.c

peephole_o1.o : global.h peephole_o1.c

basic_block.o : global.h basic_block.c

liveness_local.o : global.h liveness_local.c

MIPS_generator.o : global.h MIPS_generator.c

bitvector.o : global.h bitvector.c

reaching_def.o : global.h reaching_def.c

liveness_global.o : global.h liveness_global.c

live_range.o : global.h live_range.c

util.o : global.h util.h util.c

lex.yy.o : global.h error.h syntax-tree.h symbol-table.h lex.yy.c

y.tab.c : parser.y 
	yacc -d -v parser.y

lex.yy.c : y.tab.h scanner.l 
	flex scanner.l

y.tab.h : parser.y
	yacc -d -v parser.y

.PHONY: clean
clean :
	/bin/rm -f *.o $(DEST) *.BAK lex.yy.c y.tab.* y.output
