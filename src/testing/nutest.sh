make
for part in *_test; do ./$part; done  | fold -s -w 80 | pr -l $(($LINES -1)) \
	    -h "Unit testing results" \
	    -o 5 \
	    -w 80\
    | less -r

make clean
