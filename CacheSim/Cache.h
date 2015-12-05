#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheSet.h"
class Cache
{
public:
	Cache(int size_of_cache, int length_of_data, int num_of_set, int length_of_addr);
	Cache(const Cache& );
	~Cache();

	bool ReadDataLRU(int addr, int& data);
	bool WriteDataLRU(int addr, int data);
	int ReadDataMRU(int addr, int& data);
	int WriteDataMRU(int addr, int data);
	int ReadDataMC(int addr, int& data);
	int WriteDataMC(int addr, int data);


private:

	void SwapCacheData(int id, int set_addr);
	void AddrAnalysis(int addr, int& tag, int& set_addr);

	int size_of_cache_;	//KB
	int length_of_data_;
	int num_of_set_;
	int length_of_addr_;
	int length_of_tag_;
	int size_of_cache_set_;
	std::vector<class CacheSet> cache_;
};

