compile: main.o  pwd.o readline.o launch_execute.o cd.o ls.o pinfo.o  echo.o split.o clock.o setenv.o unsetenv.o jobs.o overkill.o redirect.o pipe.o fg.o bg.o kjob.o
	gcc main.o  pwd.o readline.o launch_execute.o cd.o ls.o pinfo.o  echo.o split.o clock.o setenv.o unsetenv.o jobs.o overkill.o redirect.o pipe.o fg.o bg.o kjob.o

main.o: main.c
	gcc -c main.c

cd.o: cd.c
	gcc -c cd.c

pwd.o: pwd.c
	gcc -c pwd.c

readline.o: readline.c
	gcc -c readline.c

launch_execute.o: launch_execute.c
	gcc -c launch_execute.c


ls.o:ls.c
	gcc -c ls.c

clock.o:clock.c
	gcc -c clock.c

pinfo.o: pinfo.c
	gcc -c pinfo.c

echo.o: echo.c
	gcc -c echo.c

split.o: split.c
	gcc -c split.c

setenv.o: setenv.c
	gcc -c setenv.c

unsetenv.o: unsetenv.c
	gcc -c unsetenv.c

jobs.o: jobs.c
	gcc -c jobs.c

overkill.o: overkill.c
	gcc -c overkill.c

redirect.o: redirect.c
	gcc -c redirect.c

pipe.o: pipe.c
	gcc -c pipe.c

fg.o: fg.c
	gcc -c fg.c

bg.o: bg.c
	gcc -c bg.c

kjob.o: kjob.c
	gcc -c kjob.c
	
clean: cd.o pwd.o readline.o launch_execute.o ls.o pinfo.o  echo.o split.o clock.o setenv.o unsetenv.o jobs.o overkill.o redirect.o pipe.o fg.o bg.o kjob.o
	rm *.o
