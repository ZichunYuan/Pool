
#YOU MUST HAVE YOUR NAME IN YOUR MAKEFILE!
#Name: Zichun Yuan
#Makefile for lab 1-4.  You need to add you name to this file in the comments
# You will need to add a entry to create your zip file

#change the last dependency for each new lab
all:  tags headers lab3

#this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files

lab3: lab3.o table.o memo.o io.o
	gcc -g -o $@ $^ -lncurses -L. -llinkedlist -l8ball -lm



#this is where you create an entry to build yuour zip file
#it will also update with new labs
lab3.zip:	makefile *.c *.h README_LAB3 
	zip lab3.zip makefile *.c *.h README_LAB3 lib8ball.a liblinkedlist.a
	# optional below here - remove old install folder
	rm -rf install
	# create the install folder
	mkdir install
	# unzip to the install folder
	unzip lab3.zip -d install
# make ONLY the lab1 target, not lab1.zip	
	make -C install lab3	

#Please grade this. Test how struct works.
testStructs:testStructs.o
	gcc -ansi -pedantic -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lm
#Please grade this. Test how reflection works.
testReflection:testReflection.o
	gcc -ansi -pedantic -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lm
#Please grade this. Test how friction works.
testFriction:testFriction.o
	gcc -ansi -pedantic -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lm
#Please grade this. Test how linked list works.
testList:testList.o
	gcc -ansi -pedantic -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lm

#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh

# a new target called "stuff"
stuff: makefile
	date>stuff
	ls -lt>>stuff

# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@


