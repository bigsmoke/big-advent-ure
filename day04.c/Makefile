solve: main.c
	gcc -o $@ $^

.PHONY: test
test: solve
	$(CURDIR)/solve < test-input.txt
