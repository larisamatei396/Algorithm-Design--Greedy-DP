build:
	gcc -g -Wall frati.c -o frati
	gcc -g -Wall ursi.c -o ursi -lm
	gcc -g -Wall planificare.c -o planificare -lm
	gcc -g -Wall numaratoare.c -o numaratoare
run-p1:
	./frati
run-p2:
	./ursi
run-p3:
	./planificare
run-p4:
	./numaratoare
clean:
	rm -f frati ursi planificare numaratoare
