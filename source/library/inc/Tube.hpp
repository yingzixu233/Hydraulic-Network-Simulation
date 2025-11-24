#pragma once
#include "Node.hpp"

namespace cie
{
	namespace pipenetwork
	{
		class Tube
		{
		public:
			Tube(Node* node1, Node* node2, double diameter);

			~Tube();

			double length() const;

			double permeability() const;

			const Node* node1() const;

			const Node* node2() const;

		private:
			Node* node1_;
			Node* node2_;
			double diameter_;

		};

	}//namespace pipenetwork
	
}//namespace cie