all: intrin

intrin: intrinsics.c intrin_des.c intrin_des.h intrin_deseval.c Makefile intrin_operators.c
	$(CXX) -O3 -msse2 -march=core2 -ftree-vectorize intrinsics.c intrin_des.c intrin_deseval.c intrin_des.h intrin_operators.c -o intrin

asm: intrinsics.c intrin_des.c intrin_des.h intrin_deseval.c Makefile intrin_operators.c
	$(CXX) -fdump-tree-optimized -ftree-vectorize -S -O3 -msse2 -march=core2 intrinsics.c intrin_des.c intrin_deseval.c intrin_des.h intrin_operators.c

test:
	./intrin -P
	./intrin -S
clean:
	rm intrin
	rm *.optimized
	rm *.s
