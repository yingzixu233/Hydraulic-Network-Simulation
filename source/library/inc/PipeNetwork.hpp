#pragma once
#include "Node.hpp"
#include "Tube.hpp"
#include <iostream>
#include <vector>

namespace cie
{
	namespace pipenetwork
	{
		class PipeNetwork
		{
		public:
			PipeNetwork(const std::string& filename);
			std::vector <double> computeFluxes() const;
			
		private:
			const std::string& filename_;
		};

	}//namespace pipenetwork

}//namespace cie