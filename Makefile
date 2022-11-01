.PHONY: build clean all profile clean-log

TARGETS := $(patsubst impl/%.c, %, $(wildcard impl/*.c)) $(patsubst impl/%.c, %.unroll, $(wildcard impl/*.c))

all: profile
impl/%.s: impl/%.c
	riscv64-unknown-elf-gcc -O3 -S -o $@ $<

impl/%.unroll.s: impl/%.c
	riscv64-unknown-elf-gcc -O3 -funroll-loops -S -o $@ $<

log/%.log: impl/%.s
	@mkdir -p log
	@echo "======================== $<"
	@riscv64-unknown-elf-gcc -O3 -o matrix matrix.c $<
	@spike pk ./matrix 2>&1 | tee $@


profile: $(patsubst %, log/%.log, $(TARGETS))

clean-log:
	rm -rf log

clean:
	rm -f matrix
	rm -f impl/*.s
	rm -rf log

