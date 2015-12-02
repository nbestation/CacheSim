#include <stdlib.h>
#include <stdio.h>
#include "CacheLine.h"
CacheLine::CacheLine(int length_of_tag, int length_of_data)
{
	SetValid(0);
	length_of_tag_ = length_of_tag;
	length_of_data_ = length_of_data;
	tag_ = (char*)malloc(sizeof(char)*length_of_tag_);
	data_ = (char*)malloc(sizeof(char)*length_of_data_);
}

CacheLine::CacheLine(const CacheLine &cl)
{
	length_of_tag_ = cl.length_of_tag_;
	length_of_data_ = cl.length_of_data_;
	tag_ = (char*)malloc(sizeof(char)*length_of_tag_);
	data_ = (char*)malloc(sizeof(char)*length_of_data_);
}

CacheLine::~CacheLine()
{
	//printf("%d\n", tag_);
	free(tag_);
	free(data_);
}