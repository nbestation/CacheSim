#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheLine.h"
class CacheSet
{
public:
	CacheSet(int size_of_cache_set, int length_of_tag, int length_of_data);
	CacheSet(const CacheSet& );
	~CacheSet();
	bool ReadData(int addr, int tag, int& data);
	bool WriteData(int addr, int tag, int data);
	int GetTag(int addr);
	bool GetValid(int addr);

private:
	int size_of_cache_set_;	
	int length_of_tag_;
	int length_of_data_; 
	std::vector<class CacheLine> cache_set_;
};
