#include <stdlib.h>
#include <stdio.h>
#include "CacheLine.h"
//#include <iostream>
//#include <fstream>
//using namespace std;

CacheLine::CacheLine(int length_of_tag, int length_of_data)
{
	SetValid(0);
	length_of_tag_ = length_of_tag;
	length_of_data_ = length_of_data;
	tag_.resize(length_of_tag_, 0);
	data_.resize(length_of_data_, 0);
}

CacheLine::CacheLine(const CacheLine &cl)
{
	SetValid(0);
	length_of_tag_ = cl.length_of_tag_;
	length_of_data_ = cl.length_of_data_;
	tag_.resize(length_of_tag_, 0);
	data_.resize(length_of_data_, 0);
}

CacheLine::~CacheLine()
{
}

int CacheLine::GetTag()
{
	int sum = 0;
	int base = 1;
	for (int i = 0; i < tag_.size(); i++)
	{
		sum = sum + base * (int)tag_[i];
		base = base * 2;
	}
	return sum;
}

bool CacheLine::ReadData(int tag, int& data)
{
	bool valid = GetValid();
	SetValid(1);
	int base = 1;
	int sum = 0;
	for (int i = 0; i < tag_.size(); i++)
	{
		valid = valid && (bool)(tag % 2 == (int)tag_[i]);
		tag_[i] = (char)(tag % 2);
		tag = (int)(tag / 2);
	}
	for (int i = 0; i < data_.size(); i++)
	{
		sum = sum + base * (int)data_[i];
		base = base * 2;
	}
	data = sum;
	return valid;
}

bool CacheLine::WriteData(int tag, int data)
{
	bool valid = GetValid();
	SetValid(1);
	for (int i = 0; i < tag_.size(); i++)
	{
		valid = valid && (bool)(tag % 2 == (int)tag_[i]);
		tag_[i] = (char)(tag % 2);
		tag = (int)(tag / 2);
	}
	for (int i = 0; i < data_.size(); i++)
	{
		data_[i] = (char)(data % 2);
		data = (int)(data / 2);
	}
	return valid;
}