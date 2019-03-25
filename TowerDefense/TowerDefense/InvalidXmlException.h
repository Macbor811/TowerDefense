#pragma once
#include "vcruntime_exception.h"

class InvalidXmlException :
	public std::exception
{
public:
	using std::exception::exception;
	virtual ~InvalidXmlException() {};
};

