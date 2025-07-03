CLIBS = -lssl -lcrypto
all: mp4

mp4:
	$(CC) $(CLIBS) -g -Wall enc.o phrases.o part_b.c -o mp4b

clean:
	$(RM) mp4b
