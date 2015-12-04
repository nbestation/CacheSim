#include <stdlib.h>
#include <stdio.h>
#include <vector>
//#include "CacheLine.h"
#include "CacheSet.h"
#include "Cache.h"


int main()
{
	class Cache temp(1, 32, 1, 32);
	int data;
	bool hit;
	hit = temp.ReadData(4, data);
	printf("%d\n", hit);
	hit = temp.ReadData(4, data);
	printf("%d\n", hit);
	hit = temp.ReadData(4, data);
	printf("%d\n", hit);
	hit = temp.ReadData(4, data);
	printf("%d\n", hit); 
	system("pause");
}



