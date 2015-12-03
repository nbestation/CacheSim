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

private:
	int size_of_cache_;	//KB
	int length_of_data_;
	int num_of_set_;
	int length_of_addr_;
	int length_of_tag_;
	int size_of_cache_set_;
	std::vector<class CacheSet> cache_;
};

