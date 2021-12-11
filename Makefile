DAY_SUBDIRS := $(wildcard 2021/day*.c)
DAY_BINARIES := $(patsubst %.c,%.c/solve,$(DAY_SUBDIRS))

all: $(DAY_BINARIES)

2020/day%.c/solve: 2020/day%.c 2020/day%.c/main.c
	$(MAKE) -C "$<"

2021/day%.c/solve: 2021/day%.c 2021/day%.c/main.c
	$(MAKE) -C "$<"


.PHONY: all
