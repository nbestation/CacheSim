#pragma once
#include <stdlib.h>
#include <vector>

class CacheLine
{
public:
	CacheLine(int length_of_tag, int length_of_data);
	CacheLine(const CacheLine& );
	~CacheLine();
	inline void SetValid(int valid){ valid_ = valid; }
	inline bool GetValid(){ return valid_; }
	int GetTag();
	bool ReadData(int tag, int& data);
	bool WriteData(int tag, int data);

private:
	bool valid_;
	int length_of_tag_;
	std::vector<char> tag_;
	int length_of_data_;
	std::vector<char> data_;
};

