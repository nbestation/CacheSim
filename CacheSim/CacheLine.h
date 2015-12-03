#pragma once
class CacheLine
{
public:
	CacheLine(int length_of_tag, int length_of_data);
	CacheLine(const CacheLine& );
	~CacheLine();
	inline void SetValid(int valid){ valid_ = valid; }
	inline int GetTagLength(){ return length_of_tag_; }

private:
	char valid_;
	int length_of_tag_;
	char* tag_;
	int length_of_data_;
	char* data_;
};

