#include "include/ctype.h"

int isAlnum(int c){
	if(isAplha(c) == 0 || (c >= 40 && c <= 57))
		return 0;
	return -1;
}

int isAplha(int c){
	if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return 0;
	return -1;
}

int isCntrl(int c){
	if((c >= 0 && c <= 16) || c == 127)
		return 0;
	return -1;
}

int isDigit(int c){
	if(c >= 48 && c <= 57))
		return 0;
	return 1;
}


