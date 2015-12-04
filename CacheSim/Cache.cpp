#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheSet.h"
#include "Cache.h"
#include "MyMathFunc.h"
Cache::Cache(int size_of_cache, int length_of_data, int num_of_set, int length_of_addr)
{
	size_of_cache_ = size_of_cache;
	length_of_data_ = length_of_data;
	num_of_set_ = num_of_set;
	length_of_addr_ = length_of_addr;
	size_of_cache_set_ = size_of_cache * 1024 /*Byte*/ / 4 /*offset*/ / num_of_set;
	length_of_tag_ = length_of_addr_ - log2(size_of_cache_set_) - 2;
	class CacheSet temp(size_of_cache_set_, length_of_tag_, length_of_data_);
	cache_.resize(num_of_set_, temp);
	//cache_.resize(num_of_set_, { size_of_cache_set_, length_of_tag_, length_of_data_ });
}

Cache::Cache(const Cache& c)
{
	size_of_cache_ = c.size_of_cache_;
	length_of_data_ = c.length_of_data_;
	num_of_set_ = c.num_of_set_;
	length_of_addr_ = c.length_of_addr_;
	size_of_cache_set_ = c.size_of_cache_set_;
	length_of_tag_ = c.length_of_tag_;
	class CacheSet temp(c.size_of_cache_set_, c.length_of_tag_, c.length_of_data_);
	cache_.resize(c.num_of_set_, temp);
	//cache_.resize(num_of_set_, { size_of_cache_set_, length_of_tag_, length_of_data_ });
}

Cache::~Cache()
{
	for (int i = 0; i < cache_.size(); i++)
	{
		cache_[i].~CacheSet();
	}
}