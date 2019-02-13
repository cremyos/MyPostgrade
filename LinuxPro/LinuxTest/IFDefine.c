#include <stdio.h>
#include <stdlib.h>

int main()
{
#if defined a==1
	printf("a = 1");
#elif defined a==2
	printf("a = 2\n");
#endif
	return 0;
}
