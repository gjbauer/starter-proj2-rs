
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
HDRS := $(wildcard *.h)

CFLAGS := -g 
LDLIBS := 

nufs:
	cargo build

clean: unmount
	rm -f nufs *.o test.log data.nufs mkfs/mkfs
	rmdir mnt || true

hex:
	vim data.nufs

mount: nufs
	mkdir -p mnt || true
	cargo run --quiet
#	./nufs -s -f mnt data.nufs

unmount:
	fusermount -u mnt || true

test: nufs
	perl test.pl

open:
	nvim -p src/*.rs

.PHONY: clean mount unmount gdb
