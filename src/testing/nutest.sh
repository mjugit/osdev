
gcc include/test.c

./a.out | fold -s -w 80 | pr -l $LINES \
	    -h "Unit testing results" \
	    -o 5 \
	    -w 80\
	    -1\
	    -f\
    | less -r
