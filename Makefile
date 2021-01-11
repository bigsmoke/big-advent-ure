DAY_SUBDIRS := $(wildcard day*.c)
DAY_BINARIES := $(patsubst %.c,%.c/solve,$(DAY_SUBDIRS))

all: $(DAY_BINARIES)

day%.c/solve: day%.c day%.c/main.c
	$(MAKE) -C "$<"


.PHONY: all
