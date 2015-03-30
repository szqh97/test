#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* compose(const char* name, const char* domain)
{
    char* res = malloc(strlen(name) + strlen(domain) + 2);
    memset(res, 0, strlen(res));
    char *p = strcpy(res, name);
    p += strlen(name);
    *p = '@';
    strcpy(p+1, domain);
    p += (strlen(domain)+1);
    return res;
}


int main ( int argc, char *argv[] )
{
    char *addr = compose("gre", "research.att.com");
    printf("%s", addr);
    free(addr);
    return 0;
}			/* ----------  end of function main  ---------- */

