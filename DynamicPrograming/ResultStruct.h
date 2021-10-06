#pragma once
#include <map>
/*********************************************************
* Summary: Struct to store metadata used by all of the algorithms.
*
* Author: Nathan Cook
* Created: Oct 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

struct ResultStruct {
	int problem;
	int count;
	std::map<int, int> coins;
};