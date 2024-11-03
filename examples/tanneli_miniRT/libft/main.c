#include "libft.h"
#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    //int a = 5;
    //int b = 'C';
    setlocale(LC_ALL, "");
    wint_t wideChar = L'é';
    const char *s1 = "asd";
    const char *s2 = "asd\0asd";
    const char *s3 = "asd\0\0\0";
    const char *s4 = "\0\0\0";
    const char *s5 = "\0";
    const char *s6 = "";

    printf("TESTING FT_ISALPHA \n");
    printf("with yours: %d\n", ft_isalpha('a'));
    printf("with OG: %d\n", isalpha('a'));
    printf("\n");
    printf("with yours: %d\n", ft_isalpha('Z'));
    printf("with OG: %d\n", isalpha('Z'));
    printf("\n");
    printf("with yours: %d\n", ft_isalpha('0'));
    printf("with OG: %d\n", isalpha('0'));
    printf("\n");
    printf("with yours: %d\n", ft_isalpha(0));
    printf("with OG: %d\n", isalpha(0));
    printf("\n");
    printf("with yours: %d\n", ft_isalpha('\0'));
    printf("with OG: %d\n", isalpha('\0'));
    printf("\n");
    printf("with yours: %d\n", ft_isalpha(wideChar));
    printf("with OG: %d\n", isalpha(wideChar));
    printf("END OF TESTING WITH FT_ISALPHA \n");

    printf("TESTING FT_ISDIGIT \n");
    printf("with yours: %d\n", ft_isdigit('a'));
    printf("with OG: %d\n", isdigit('a'));
    printf("\n");
    printf("with yours: %d\n", ft_isdigit('\0'));
    printf("with OG: %d\n", isdigit('\0'));
    printf("\n");
    printf("with yours: %d\n", ft_isdigit('5'));
    printf("with OG: %d\n", isdigit('5'));
    printf("\n");
    printf("with yours: %d\n", ft_isdigit('5'));
    printf("with OG: %d\n", isdigit('5'));
    printf("END OF TESTING WITH FT_ISDIGIT \n");

    printf("TESTING FT_ISALNUM \n");
    printf("with yours: %d\n", ft_isalnum('a'));
    printf("with OG: %d\n", isalnum('a'));
    printf("\n");
    printf("with yours: %d\n", ft_isalnum('5'));
    printf("with OG: %d\n", isalnum('5'));
    printf("\n");
    printf("with yours: %d\n", ft_isalnum('\0'));
    printf("with OG: %d\n", isalnum('\0'));
    printf("\n");
    printf("with yours: %d\n", ft_isalnum(0));
    printf("with OG: %d\n", isalnum(0));
    printf("\n");
    printf("with yours: %d\n", ft_isalnum(255));
    printf("with OG: %d\n", isalnum(255));
    printf("END OF TESTING WITH FT_ISALNUM \n");

    printf("TESTING FT_ISASCII \n");
    printf("with yours: %d\n", ft_isascii('a'));
    printf("with OG: %d\n", isascii('a'));
    printf("\n");
    printf("with yours: %d\n", ft_isascii('@'));
    printf("with OG: %d\n", isascii('@'));
    printf("\n");
    printf("with yours: %d\n", ft_isascii('#'));
    printf("with OG: %d\n", isascii('#'));
    printf("\n");
    printf("with yours: %d\n", ft_isascii(-1));
    printf("with OG: %d\n", isascii(-1));
    printf("\n");
    printf("with yours: %d\n", ft_isascii(128));
    printf("with OG: %d\n", isascii(128));
    printf("\n");
    printf("with yours: %d\n", ft_isascii(255));
    printf("with OG: %d\n", isascii(255));
    printf("END OF TESTING WITH FT_ISASCII \n");

    printf("TESTING FT_ISPRINT \n");
    printf("with yours: %d\n", ft_isprint('#'));
    printf("with OG: %d\n", isprint('#'));
    printf("\n");
    printf("with yours: %d\n", ft_isprint('1'));
    printf("with OG: %d\n", isprint('1'));
    printf("\n");
    printf("with yours: %d\n", ft_isprint(-1));
    printf("with OG: %d\n", isprint(-1));
    printf("\n");
    printf("with yours: %d\n", ft_isprint(128));
    printf("with OG: %d\n", isprint(128));
    printf("\n");
    printf("with yours: %d\n", ft_isprint(255));
    printf("with OG: %d\n", isprint(255));
    printf("END OF TESTING WITH FT_ISPRINT \n");

    printf("TESTING FT_STRLEN \n");
    printf("with yours: %lu\n", ft_strlen(s1));
    printf("with OG: %lu\n", strlen(s1));
    printf("\n");
    printf("with yours: %lu\n", ft_strlen(s2));
    printf("with OG: %lu\n", strlen(s2));
    printf("\n");
    printf("with yours: %lu\n", ft_strlen(s3));
    printf("with OG: %lu\n", strlen(s3));
    printf("\n");
    printf("with yours: %lu\n", ft_strlen(s4));
    printf("with OG: %lu\n", strlen(s4));
    printf("\n");
    printf("with yours: %lu\n", ft_strlen(s5));
    printf("with OG: %lu\n", strlen(s5));
    printf("\n");
    printf("with yours: %lu\n", ft_strlen(s6));
    printf("with OG: %lu\n", strlen(s6));
    printf("END OF TESTING WITH FT_STRLEN \n");
/*
    printf("TESTING FT_MEMSET \n");
    unsigned char buffer[10];
    //unsigned char emptyBuffer[1];
    printf("with yours: %s\n", ft_memset(buffer, 42, 10));
    printf("with OG: %s\n", memset(buffer, 42, 10));
    printf("\n");
    //printf("with yours: %s\n", ft_memset(emptyBuffer, 42, 10));
    //printf("with OG: %s\n", memset(emptyBuffer, 42, 10));
    printf("END OF TESTING WITH FT_MEMSET \n");*/
}
