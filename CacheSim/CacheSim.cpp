#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheLine.h"

int main()
{
	std::vector<class CacheLine> temp(5, {10, 32});
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", temp[i].GetTagLength());

	}
	system("pause");
}



