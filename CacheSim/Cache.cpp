#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheSet.h"
#include "Cache.h"
#include "MyMathFunc.h"
#include "Config.h"
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

void Cache::AddrAnalysis(int addr, int& tag, int& set_addr)
{
	set_addr = (int)(addr / 4) % size_of_cache_set_;
	tag = (addr - set_addr * 4) / (size_of_cache_set_ * 4);
}

void Cache::SwapCacheData(int id, int set_addr)
{
	int data;
	int tag = cache_[id - 1].GetTag(set_addr);
	cache_[id - 1].ReadData(set_addr, 0, data);
	cache_[id].WriteData(set_addr, tag, data);
}

bool Cache::ReadDataLRU(int addr, int& data)
{
	int tag, set_addr;
	AddrAnalysis(addr, tag, set_addr);
	int non_valid_id = cache_.size();
	bool hit = false;
	for (int i = cache_.size() - 1; i >= 0; i--)
	{
		if (cache_[i].GetValid(set_addr) == 0)
		{
			non_valid_id = i;
		}
		else if (tag == cache_[i].GetTag(set_addr))
		{
			hit = true;
		}
	}
	if (hit)
	{
		int hit_set_id;
		for (int i = cache_.size() - 1; i >= 0; i--)
		{
			if (tag == cache_[i].GetTag(set_addr))
			{
				hit_set_id = i;
			}
		}
		cache_[hit_set_id].ReadData(set_addr, tag, data);//read data
		for (int i = hit_set_id; i > 0; i--)//replace
		{
			SwapCacheData(i, set_addr);
		}
		cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
	}
	else
	{
		if (non_valid_id == cache_.size())//cache is full
		{
			for (int i = cache_.size() - 1; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
		else
		{
			for (int i = non_valid_id; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
	}
	return hit;
}

bool Cache::WriteDataLRU(int addr, int data)
{
	int tag, set_addr;
	AddrAnalysis(addr, tag, set_addr);
	int non_valid_id = cache_.size();
	bool hit = false;
	for (int i = cache_.size() - 1; i >= 0; i--)
	{
		if (cache_[i].GetValid(set_addr) == 0)
		{
			non_valid_id = i;
		}
		else if (tag == cache_[i].GetTag(set_addr))
		{
			hit = true;
		}
	}
	if (hit)
	{
		int hit_set_id;
		for (int i = cache_.size() - 1; i >= 0; i--)
		{
			if (tag == cache_[i].GetTag(set_addr))
			{
				hit_set_id = i;
			}
		}
		for (int i = hit_set_id; i > 0; i--)//replace
		{
			SwapCacheData(i, set_addr);
		}
		cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
	}
	else
	{
		if (non_valid_id == cache_.size())//cache is full
		{
			for (int i = cache_.size() - 1; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
		else
		{
			for (int i = non_valid_id; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
	}
	return hit;
}

int Cache::ReadDataMRU(int addr, int& data)
{
	int tag, set_addr;
	AddrAnalysis(addr, tag, set_addr);
	int non_valid_id = cache_.size();
	bool hit = false;
	int hit_set_id;
	for (int i = cache_.size() - 1; i >= 0; i--)
	{
		if (cache_[i].GetValid(set_addr) == 0)
		{
			non_valid_id = i;
		}
		else if (tag == cache_[i].GetTag(set_addr))
		{
			hit = true;
		}
	}
	if (hit)
	{
		for (int i = cache_.size() - 1; i >= 0; i--)
		{
			if (tag == cache_[i].GetTag(set_addr))
			{
				hit_set_id = i;
			}
		}
		cache_[hit_set_id].ReadData(set_addr, tag, data);//read data
		for (int i = hit_set_id; i > 0; i--)//replace
		{
			SwapCacheData(i, set_addr);
		}
		cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
	}
	else
	{
		if (non_valid_id == cache_.size())//cache is full
		{
			for (int i = cache_.size() - 1; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
		else
		{
			for (int i = non_valid_id; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
	}
	if (hit)
	{
		if (hit_set_id == 0)
		{
			return FIRST_HIT;
		}
		else
		{
			return NOT_FIRST_HIT;
		}
	}
	else
	{
		return NOT_HIT;
	}
}

int Cache::WriteDataMRU(int addr, int data)
{
	int tag, set_addr;
	AddrAnalysis(addr, tag, set_addr);
	int non_valid_id = cache_.size();
	bool hit = false;
	int hit_set_id;
	for (int i = cache_.size() - 1; i >= 0; i--)
	{
		if (cache_[i].GetValid(set_addr) == 0)
		{
			non_valid_id = i;
		}
		else if (tag == cache_[i].GetTag(set_addr))
		{
			hit = true;
		}
	}
	if (hit)
	{
		for (int i = cache_.size() - 1; i >= 0; i--)
		{
			if (tag == cache_[i].GetTag(set_addr))
			{
				hit_set_id = i;
			}
		}
		for (int i = hit_set_id; i > 0; i--)//replace
		{
			SwapCacheData(i, set_addr);
		}
		cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
	}
	else
	{
		if (non_valid_id == cache_.size())//cache is full
		{
			for (int i = cache_.size() - 1; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
		else
		{
			for (int i = non_valid_id; i > 0; i--)//replace
			{
				SwapCacheData(i, set_addr);
			}
			cache_[0].WriteData(set_addr, tag, data);//write data to the latest set
		}
	}
	if (hit)
	{
		if (hit_set_id == 0)
		{
			return FIRST_HIT;
		}
		else
		{
			return NOT_FIRST_HIT;
		}
	}
	else
	{
		return NOT_HIT;
	}
}
