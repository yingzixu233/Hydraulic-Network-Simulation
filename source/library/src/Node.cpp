#include "Node.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


namespace cie
{
	namespace pipenetwork
	{
		Node::Node(double x, double y, double flow, int id) :
			x_(x), y_(y), flow_(flow), id_(id)
		{ }

		Node::~Node()
		{ }

		double Node::x() const
		{
			return x_;
		}

		double Node::y() const
		{
			return y_;
		}

		double Node::flow() const
		{
			return flow_;
		}

		int Node::id() const
		{
			return id_;
		}

	}//namespace pipenetwork
	
}//namespace cie
