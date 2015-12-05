#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheSet.h"
#include "Cache.h"
#include "Config.h"

int main()
{
	char c;
	int addr, data;
	int hit;
	int total_hit, first_hit, non_first_hit, total;
	FILE* fp = NULL;

	/*---------------Cache 1: DM---------------*/
	printf("\n---------------Cache 1: DM---------------\n");
	class Cache cache1(64, 32, 1, 32);
	fp = fopen("data_pattern.txt", "r");
	if (NULL == fp)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	FILE* fp1 = NULL;
	fp1 = fopen("log1.txt", "w");
	if (NULL == fp1)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	total = 0;
	total_hit = 0;
	fprintf(fp1, "ADDR\t\tSTATUS\n------------------------------\n");
	while (!feof(fp))
	{
		fscanf(fp, "%d", &addr);
		hit = cache1.ReadDataLRU(addr, data);
		if (hit == NOT_HIT)
		{
			fprintf(fp1, "%d\t\tnot hit\n", addr);
		}
		else
		{
			fprintf(fp1, "%d\t\thit\n", addr);
			total_hit++;
		}
		fscanf(fp, "%c", &c);
		total++;
	}
	printf("Hit ratio: %3.2f%%\n", float(total_hit) / float(total) * 100);
	fclose(fp);
	fclose(fp1);

	/*---------------Cache 2: SA,2-way---------------*/
	printf("\n---------------Cache 2: SA,2-way---------------\n");
	class Cache cache2(64, 32, 2, 32);
	fp = fopen("data_pattern.txt", "r");
	if (NULL == fp)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	FILE* fp2 = NULL;
	fp2 = fopen("log2.txt", "w");
	if (NULL == fp2)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	total = 0;
	total_hit = 0;
	fprintf(fp2, "ADDR\t\tSTATUS\n------------------------------\n");
	while (!feof(fp))
	{
		fscanf(fp, "%d", &addr);
		hit = cache2.ReadDataLRU(addr, data);
		if (hit == NOT_HIT)
		{
			fprintf(fp2, "%d\t\tnot hit\n", addr);
		}
		else
		{
			fprintf(fp2, "%d\t\thit\n", addr);
			total_hit++;
		}
		fscanf(fp, "%c", &c);
		total++;
	}
	printf("Hit ratio: %3.2f%%\n", float(total_hit) / float(total) * 100);
	fclose(fp);
	fclose(fp2);

	/*---------------Cache 3: SA,4-way---------------*/
	printf("\n---------------Cache 3: SA,4-way---------------\n");
	class Cache cache3(64, 32, 4, 32);
	fp = fopen("data_pattern.txt", "r");
	if (NULL == fp)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	FILE* fp3 = NULL;
	fp3 = fopen("log3.txt", "w");
	if (NULL == fp3)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	total = 0;
	total_hit = 0;
	fprintf(fp3, "ADDR\t\tSTATUS\n------------------------------\n");
	while (!feof(fp))
	{
		fscanf(fp, "%d", &addr);
		hit = cache3.ReadDataLRU(addr, data);
		if (hit == NOT_HIT)
		{
			fprintf(fp3, "%d\t\tnot hit\n", addr);
		}
		else
		{
			fprintf(fp3, "%d\t\thit\n", addr);
			total_hit++;
		}
		fscanf(fp, "%c", &c);
		total++;
	}
	printf("Hit ratio: %3.2f%%\n", float(total_hit) / float(total) * 100);
	fclose(fp);
	fclose(fp3);

	/*---------------Cache 4: SA,MRU,4-way---------------*/
	printf("\n---------------Cache 4: SA,MRU,4-way---------------\n");
	class Cache cache4(64, 32, 4, 32);
	fp = fopen("data_pattern.txt", "r");
	if (NULL == fp)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	FILE* fp4 = NULL;
	fp4 = fopen("log4.txt", "w");
	if (NULL == fp4)
	{
		printf("Can not open file!\n");
		return -1;//要返回错误代码
	}
	total = 0;
	first_hit = 0;
	non_first_hit = 0;
	total_hit = 0;
	fprintf(fp4, "ADDR\t\tSTATUS\n------------------------------\n");
	while (!feof(fp))
	{
		fscanf(fp, "%d", &addr);
		hit = cache4.ReadDataMRU(addr, data);
		if (hit == NOT_HIT)
		{
			fprintf(fp4, "%d\t\tnot hit\n", addr);
		}
		else
		{
			total_hit++;
			if (hit == FIRST_HIT)
			{
				first_hit++;
				fprintf(fp4, "%d\t\tfirst hit\n", addr);
			}
			else
			{
				non_first_hit++;
				fprintf(fp4, "%d\t\tnot first hit\n", addr);
			}
		}
		fscanf(fp, "%c", &c);
		total++;
	}
	printf("Hit ratio: %3.2f%%\n", float(total_hit) / float(total) * 100);
	printf("First-hit ratio: %3.2f%%\n", float(first_hit) / float(total) * 100);
	printf("Non-first-hit ratio: %3.2f%%\n", float(non_first_hit) / float(total) * 100);
	fclose(fp);
	fclose(fp4);

	system("pause");
}


