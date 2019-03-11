#pragma once
#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <deque>          // std::deque

class stackObj
{
public:
	float x;
	float y;
	int type;

	stackObj();
	stackObj(float, float, int);
	~stackObj();
};

stackObj::stackObj()
{
}

stackObj::stackObj(float i = 0, float j = 0, int k = 0)
:x(i), y(j), type(k)
{
}

stackObj::~stackObj()
{
}

//stored Variables
static std::stack<stackObj> undoStack;
static std::stack<stackObj> redoStack;