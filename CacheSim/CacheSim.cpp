#include <stdlib.h>
#include <stdio.h>
#include <vector>
//#include "CacheLine.h"
#include "CacheSet.h"
#include "Cache.h"

void level2(int&a)
{
	a = a * 2;
	printf("a = %d\n", a);
}

void level1(int&b)
{
	//b = b * 3;
	level2(b);
	printf("b = %d\n", b);
}

int main()
{
	int x = 1;
	level1(x);
	printf("x = %d\n", x);
	system("pause");
}



