// DMath_Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.hpp"
#include <iostream>
#include <list>
#include <algorithm>
enum Var
	{
		_null = 2,
		_one = 1,
		_X = 3,
		_zero = 0
	};

#define List BDList

template<unsigned n = 16> struct Vector
{
	Var data_[n];
	Vector(){}
	Vector(char* str)
	{
		for(unsigned i = 0; i < n; ++i)
		{
			switch(str[i])
			{
			case '0' : data_[i] = _null; break;
			case '1' : data_[i] = _one; break;
			case 'x' : data_[i] = _X; break;
			}
		}
	}

	Vector operator ^(Vector arg) const
	{

		Vector tmp;
		unsigned nullCount = 0;
		for(unsigned i = 0; i < n; ++i)
		{
			tmp.data_[i] = static_cast<Var>(data_[i] & arg.data_[i]);
			if (tmp.data_[i] == _zero)
			{
				++nullCount;  
				tmp.data_[i] = _X;
			}
		}
		if(nullCount == 1) return tmp;
		else throw "Error";
	}

	Vector operator &(Vector arg) const
	{
		Vector tmp;
		for(unsigned i = 0; i < n; ++i)
		{
			tmp.data_[i] = static_cast<Var>(data_[i] & arg.data_[i]);
		}
		return tmp;
	}
	bool inc(Vector arg) const
	{
		return ((*this) & arg) == arg;
	}
	bool operator == (Vector arg) const
	{
		for(unsigned i = 0; i < n; ++i)
		{
			if(data_[i] != arg.data_[i]) return false;
		}
		return true;
	}

	void print() const
	{
		for(unsigned j = 0; j < n; ++j)
		{
			switch(data_[j])
			{
			case _null: std::cout << "0"; break;
			case _one: std::cout << "1"; break;
			case _X: std::cout << "x"; break;
			}
		}
		std::cout << std::endl;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	typedef Vector<16> Vector;
	

	std::list<Vector> lst;
	
	//ввод


	
	lst.push_back(Vector("10xx01001xxxx101"));
	lst.push_back(Vector("0x11x1xx1x00xx01"));
	lst.push_back(Vector("xxxxxxxxxxxxx01x"));


	bool newIteration = true;
	while(newIteration)
	{
		newIteration = false;
		for(std::list<Vector>::iterator i = lst.begin(); i!=lst.end() && !newIteration;)
		{
			Vector curr = *i;
			

			bool weryty = false;
			for(std::list<Vector>::iterator j = lst.begin(); j!=lst.end(); ++j)
			{
				Vector nxt = *j;
				if(nxt.inc(curr) && i != j)
				{
					//std::list<Vector>::iterator k = i;
					//++k;
					//i.remove();
					i = lst.erase(i);
					weryty = true;;
					break;
				}
			}
			if(weryty) continue;

			for(std::list<Vector>::iterator j = lst.begin(); j!=lst.end();)
			{
				Vector nxt = *j;
				if(curr.inc(nxt) && i != j)
				{
					//std::list<Vector>::iterator k = j;
					//++k;
					//j.remove();
					j = lst.erase(j);
				}
				else ++j;					
			}

			std::list<Vector>::iterator j = i;
			++j;
			for(; j!=lst.end(); ++j)
			{
				Vector nxt = *j;
				try
				{
					Vector abc = curr ^ nxt;
					
					bool absorpted = false;
					for(std::list<Vector>::iterator q = lst.begin(); q!=lst.end(); ++q)
					{//10 01 01 10 01 10 10 01 11 10 10 11 01 10 01 11
						Vector dd = *q;
						if(dd.inc(abc))
						{
							absorpted = true;;
							break;
						}
					}//10 11 11 10 01 10 10 01 11 11 11 11 01 10 01 00
					if(!absorpted)
					{
						lst.push_front(abc);
						newIteration = true;
						break;
					}

				} catch(...){}
			}
			++i;
		}
	}
	std::cout <<"start:/r/n\r\n";
	for(std::list<Vector>::iterator i = lst.begin(); i!=lst.end() ; ++i)
	{
		Vector curr = *i;
		curr.print();
	}


	

		
	return 0;
}





