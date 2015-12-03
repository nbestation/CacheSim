#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CacheLine.h"
class CacheSet
{
public:
	CacheSet(int size_of_cache_set, int length_of_tag, int length_of_data);
	CacheSet::CacheSet(CacheSet& cs);
	~CacheSet();

private:
	int size_of_cache_set_;	
	int length_of_tag_;
	int length_of_data_; 
	std::vector<class CacheLine> cache_set_;
};
