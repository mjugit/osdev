#ifndef CTYPE_H
#  define CTYPE_H

/*
 *check whether the passed character is alphanumeric
 */
extern int isAlnum(int c);

/*
 *checks whether the passed character is alphabetic.
 */
extern int isAlpha(int c);

/*
 *checks whether the passed character is control character
 */
extern int isCntrl(int c);

/*
 *checks whether the passed character is decimal digit
 */
extern int isDigit(int c);

/*
 *checks whether the passed character has graphical representation using locale
 */
extern int isGraph(int c);

/*
 *checks whether the passed character is lowercase letter
 */
extern int isLower(int c);

/*
 *checks whether the passed character is an uppercase letter.
 */
extern int isUpper(int c);

/*
 *checks whether the passed character is printable
 */
extern int isPrint(int c);

/*
 *checks whether the passed character is a punctuation character
 */
extern int isPunct(int c);

/*
 *checks whether the passed character is white-space
 */
extern int isSpace(int c);

/*
 *checks whether the passed character is a hexadecimal digit
 */
extern int isXDigit(int c);

/*
 *converts uppercase letters to lowercase
 */
extern int toLower(int c);

/*
 *converts lowercase letters to uppercase
 */
extern int toUpper(int c);

#endif //  CTYPE_H
