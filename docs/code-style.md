# Code style

There are a lot of coding conventions for the C language out there, but none really seem to prevail. Sure, there are very common ones, but none is considered the standard. On top of that, there are slightly different variants of all of them, which leads me to the conclusion that it doesn't matter which style you choose, the main thing is that you keep it. So here I would like to summarize again how things are named and which style the project uses, without referring to a specific existing style.

**Attention**: This style is different from the style used so far. However, since it is important to define a sufficiently complex coding convention at an early stage, in order not to run into difficulties as the project grows in size.

| Element           | Description                                                               |
|-------------------|---------------------------------------------------------------------------|
| Struct            | `TitleCase`                                                               |
| Struct Members    | `lower_case` or `lowerCase`                                               |
| Enum              | `ETitleCase`                                                              |
| Enum Members      | `ALL_CAPS` or `lowerCase`                                                 |
| Public functions  | `pfx_TitleCase` (`pfx` = two or three letter module prefix)               |
| Private functions | `TitleCase`                                                               |
| Local variables   | `lower_case` or `lowerCase`                                               |
| Global variables  | Just don't use global variables. They are evil.                           |
| Obscure functions | Functions, that should not be called directly begin with an `_underscore` |
| Constant macros   | Macros describing constants in `ALL_CAPS`                                 |
| Function macros   | Function macros same as public functions                                  |

## Comments

Comments are used in two scenarios: they describe what the following function does or they explain why something unusual is done exactly the way it is. In any case, it is not their job to explain the instructions around it. If this is necessary, consider whether it is possible to code it in a more comprehensible way.

```c
// BAD:
int ts(char in[]) {
	// Counter
        int n;
	for (...
	
	...
	// Append 0
	s[n+1] = '\0';
	return n;
}


// BETTER:
/*
 * str_TrimStr
 * Removes leading and trailing whitespace from @str.
 */
int str_TrimStr(char str[]) {
	int new_strlen;
	for (...
	
	...
	str[new_strlen + 1] = '\0';
	return new_strlen;
}

```
Especially in the header the description should also be mirrored in front of the functions declared as `extern`. This way the headers can be used like a list of all available functions with a short documentation.

## Control structures
The formats of the control structures in a quick run:

Parenthesis-less ifs may be used provided that the meaning is sufficiently apparent. However, if the body consists of several statements, parentheses must be used.

```c
	// Multi statement bodies
	if (expr) {
	    ...
	} else {
	    ...
	}
	
	// Single statement bodies
	if (expr)
	    ...
	else
	    ...
```

If you use inline ifs, please split the two cases into separate lines.

```c
	// Inline if
	return (expr)
		? case1
		: case2;
```

The individual cases of the switch case are separated by a blank line.

```c
	// switch case
	switch (val) {
	case 'a':
		...
		break;
		
	case 'b':
		...
		breaK;
		
	default:
		...
		break;
	}
```

For-signatures are broken up to three lines if they become too long. 

```c
	// Short for signature
	for (int count = 0; count < ...) {
		...
	}
	
	// Long for signature
	for (int count = (foo() & complex_calc()) & 0xffff; 
		complex_check(count, ...;
		count--) {
		...
	}
```

Loop blocks are opened directly without a line break.

```c	
	// While loop
	while (expr) {
		...
	}
	
	// Do-while loop
	do {
		...
	} while (expr);
```

## Functions

Function names should clearly express what the function does. If it is difficult to find a name, it should be considered whether the function might do too much. A division according to the SRP should be aimed for. Abbreviations in function names other than the most common should be avoided at best. These include: 

- `attr` for 'attribute'
- `buff` for 'buffer'
- `cfg` for 'configuration'
- `ch` for 'character'
- `col` for 'column'
- `conf` for 'configuration'
- `dec` for 'decimal'
- `hex` for 'hexadecimal'
- `len` for 'length'
- `ptr` for 'pointer'
- `str` for 'string'
- `tab` for 'tabulator'

### Signatures
Method signatures are at best on one line with a curly bracket immediately following (without a line break). If the parameter list is uncomfortably long, all parameters are wrapped line by line. It is better to have meaningful parameter names than short method signatures.

```c
// BAD:
...
void cfg_g(int *fbuff, *bbuff, int c, int r, int t) 
{
	...
}


// BETTER;
...
void gfx_ConfigureGraphics(int *frontbuff_ptr,
                        int *backbuff_ptr,
                        int columns,
                        int rows,
                        int tabsize) {
   ...
}
```

If the parameter lists become too long, consider whether it is worth combining them into a complex data type.

### Function bodies

Generally, deeply nested parentheses should be avoided. A real religious war seems to have broken out around this topic on the web. Some say 'it makes the program more readable if the function is left only at one point', others say 'the function should be left as soon as possible'. I as a friend of the Clean Code thought, find that deeply nested control structures are a smell. You should split functions so that they do **one** thing and do it well. Most of the time you don't even get into embarrassment of dealing with big functions if you strictly stick to it. If it should come to it nevertheless, leave the function as early as possible.

```c
// BAD:
void mod_Foo(int val) {
	int result = 0;
	if (val > 0) {
		if (val % 8 == 0) {
		  ...
		} else {
			result = 1;
		}
	} else {
		result = -1;
	}
	return result;
}


// BETTER:
void mod_Foo( int val) {
	if (val == -1) 
		return -1;
	if (val % 8 != 0)
		return 1;
		
	return ...
}

```

## Preprocessor directives

Preprocessor directives also provide simple control structures such as `if-else`. This inevitably leads to the need to indent things when files reach a certain size. I follow the principle of simply using two spaces per indentation depth.

```C
// BAD:
#ifdef ABC
#include ...
#include ...
#define ...
#endif
#define ...
#ifndef EDF
#define EDF
#endif
...


// BETTER:
#ifdef ABC
#  include ...
#  include ...
#  define ...
#endif // ABC

#define ..

#ifdef EDF
#  define EDF
#endif // EDF

```
