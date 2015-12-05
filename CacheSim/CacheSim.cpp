#include <stdlib.h>
#include <stdio.h>
#include <vector>
//#include "CacheLine.h"
#include "CacheSet.h"
#include "Cache.h"


int main()
{
	class Cache temp(1, 32, 4, 32);
	int data;
	int hit;
	hit = temp.ReadDataMRU(0, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(512, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(1024, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(0, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(512, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(1024, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(0, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(512, data);
	printf("%d\n", hit);
	hit = temp.ReadDataMRU(1024, data);
	system("pause");
}



