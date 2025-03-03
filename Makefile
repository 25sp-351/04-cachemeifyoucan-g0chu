all: rod_cut_a rod_cut_b

OBJS = main.o rod.o
OBJS_A = cache_policy_a.o
OBJS_B = cache_policy_b.o

CC = gcc
CFLAGS = -Wall

rod_cut_a: $(OBJS) $(OBJS_A)
	gcc -o rod_cut_a $(CFLAGS) $(OBJS) $(OBJS_A)

rod_cut_b: $(OBJS) $(OBJS_B)
	gcc -o rod_cut_b $(CFLAGS) $(OBJS) $(OBJS_B)

main.o: main.c rod.h cache.h

rod.o: rod.c rod.h

cache_policy_a.o: cache_policy_a.c cache.h rod.h

cache_policy_b.o: cache_policy_b.c cache.h rod.h

clean:
	rm -f rod_cut_a rod_cut_b pieces_test_auto.txt $(OBJS) $(OBJS_A) $(OBJS_B)
