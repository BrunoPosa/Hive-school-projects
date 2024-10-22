#include <stdio.h>

#define GREEN "\033[1;32m"
#define RED   "\033[0;31m"
#define PINK "\033[1;95m"
#define END   "\033[0m"

int main()
{
	    printf("%sThis is pink text.%s\n", PINK, END);

	    printf(RED"This text is red.\n" END);
	        return 0;
}
