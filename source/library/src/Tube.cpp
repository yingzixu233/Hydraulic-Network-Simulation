#include "Tube.hpp"
#include "Node.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


namespace cie
{
	namespace pipenetwork
	{
		Tube::Tube(Node* node1, Node* node2, double diameter) :
			node1_(node1), node2_(node2), diameter_(diameter)
		{ }

		Tube::~Tube()
		{ }

		double Tube::length() const
		{
			double l = sqrt(pow(node1_->x() - node2_->x(), 2) + pow(node1_->y() - node2_->y(), 2));
			return l;
			//(*node1_).x();
		}

		double Tube::permeability() const
		{
			const double PI = atan(1.0) * 4;
			const double g = 9.81;
			const double v = 1e-6; 
			double B = PI * g * pow(Tube::diameter_, 4) / (128 * Tube::length() * v);
			return B;
		}

		const Node* Tube::node1() const
		{
			return Tube::node1_;
		}

		const Node* Tube::node2() const
		{
			return Tube::node2_;
		}

	}//namespace pipenetwork

}//namespace cie
