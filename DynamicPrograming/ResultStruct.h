#pragma once
#include <map>
/*********************************************************
* Summary: Struct to store metadata used by all of the algorithms.
*
* Author: Nathanael Cook
* Created: Oct 2021
* 
* Used to store the result for each problem. Standerized Data stucrter
* used by all three algorithms
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

struct ResultStruct {
	int problem;
	int count;
	std::map<int, int> coins;
};