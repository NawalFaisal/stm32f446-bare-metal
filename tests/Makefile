CC     := gcc
CFLAGS := -g -O0 -Wall -Wextra -I../include -Iunity
UNITY  := unity/unity.c

BINS := test_queue test_ringbuffer

all: $(BINS)

test_queue: test_queue.c ../utils/queue.c $(UNITY)
	$(CC) $(CFLAGS) $^ -o $@

test_ringbuffer: test_ringbuffer.c ../utils/ringbuffer.c $(UNITY)
	$(CC) $(CFLAGS) $^ -o $@

test: $(BINS)
	./test_queue
	./test_ringbuffer

clean:
	rm -f $(BINS)

.PHONY: all test clean