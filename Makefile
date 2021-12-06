all:
	ls -1 | grep .c | grep -v utils | grep -v vec2 | grep -v allocator | grep -v list | cut -d. -f1 | xargs -I{} gcc -g {}.c -lm -o {}

release:
	ls -1 | grep .c | grep -v utils | grep -v vec2 | grep -v allocator | grep -v list | cut -d. -f1 | xargs -I{} gcc -O3 -march=native {}.c -lm -o {}

clean:
	ls -1 | grep .c | grep -v utils | grep -v vec2 | grep -v allocator | grep -v list | cut -d. -f1 | xargs -I{} rm -f {}

test: release
	ls -1 | grep .c | grep -v utils | grep -v vec2 | grep -v allocator | grep -v list | cut -d. -f1 | xargs -I{} bash -c "echo '---- {} ----' && time ./{}"

