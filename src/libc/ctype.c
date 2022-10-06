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
	return -1;
}

int isGraph(int c){
	//not shure here	
}

int isLower(int c) {
	if(c >= 97 && c <= 122)
		return 0;
	return -1;
}

int isUpper(int c){
	if(c >= 65 && c <= 90)
		return 0;
	return -1;
}

int isPrint(int c){
	if( c >= 33 && c <= 254 && c != 127)
		return 0;
	return -1;
}

int isPunct(int c){
	//not shure here as well
}

int isSpace(int c){
	if(c == 32)
		return 0;
	return -1;
}

int isXDigit(int c){
	if(isDigit(c) == 0 || (c >= 65 && c <= 70) || (c >= 97 && c <= 102))
		return 0;
	return -1;
}

int toLower(int c){
	if(isUpper(c) == 0){
		c += 32;
        return c;
	}
    return -1;
}

int toUpper(int c){
	if(isLower(c) == 0){
        c -= 32;
        return c;
    }
    return -1;
}
