#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheLine.h"
#include "CacheSet.h"
CacheSet::CacheSet(int size_of_cache_set, int length_of_tag, int length_of_data)
{
	size_of_cache_set_ = size_of_cache_set;
	length_of_tag_ = length_of_tag;
	length_of_data_ = length_of_data;
	//class CacheLine temp(length_of_tag, length_of_data);
	//cache_set_.resize(size_of_cache_set, temp);
	cache_set_.resize(size_of_cache_set, { length_of_tag, length_of_data });
}

CacheSet::CacheSet(const CacheSet& cs)
{
	size_of_cache_set_ = cs.size_of_cache_set_;
	length_of_tag_ = cs.length_of_tag_;
	length_of_data_ = cs.length_of_data_;
	//class CacheLine temp(cs.length_of_tag_, cs.length_of_data_);
	//cache_set_.resize(cs.size_of_cache_set_, temp);
	cache_set_.resize(cs.size_of_cache_set_, { cs.length_of_tag_, cs.length_of_data_ });
}

CacheSet::~CacheSet()
{
	for (int i = 0; i < cache_set_.size(); i++)
	{
		cache_set_[i].~CacheLine();
	}
}