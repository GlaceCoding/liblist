#!/bin/sh

HEAD="./includes/"

make
if [[ $? == 0 ]]; then
	echo "========= LIST ========="
	gcc -fsanitize=address -g ./test/test.c ./srcs/*.c -I "$HEAD" && ./a.out && rm ./a.out
	echo "========================"
	norminette ./srcs/*.c ./includes/*.h list.c | grep -v ": OK!"
fi
