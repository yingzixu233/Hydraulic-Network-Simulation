#include "Tube.hpp"
#include "Node.hpp"
#include "PipeNetwork.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

#include "linalg.hpp"



namespace cie
{
	namespace pipenetwork
	{
			PipeNetwork::PipeNetwork(const std::string& filename) :
				filename_(filename)
			{ }

			std::vector <double> PipeNetwork::computeFluxes() const
			{
				std::ifstream infile(filename_);

				int numberofNodes;
				infile >> numberofNodes;
				int numberofTubes;
				infile >> numberofTubes;


				std::cout << "numberofNodes: " << numberofNodes << std::endl << std::endl;
				std::cout << "numberofTubes: " << numberofTubes << std::endl << std::endl;


				std::vector<Node> Nodedata;
				std::vector<Tube> Tubedata;


				std::cout << "Nodedata:" << std::endl << std::endl;
				Nodedata.reserve(numberofNodes);

				for (int i = 0; i < numberofNodes; ++i)
				{
					double x;
					double y;
					double flow;

					infile >> x;
					infile >> y;
					infile >> flow;

					Nodedata.push_back(Node(x, y, flow, i));

					std::cout << std::setw(10) << " Node id: ";
					std::cout << std::setw(5) << i;
					std::cout << std::setw(10)<< std::setw(15) << " X coordinate: ";
					std::cout << std::setw(5) << x;
					std::cout << std::setw(10) << " Y coordinate:  ";
					std::cout << std::setw(5) << y;
					std::cout << std::setw(10) << " Flow value: ";
					std::cout << std::setw(5) << flow;

					std::cout << std::endl << std::endl;
				}

				std::cout << "Tubedata:" << std::endl << std::endl;
				Tubedata.reserve(numberofTubes);
				for (int i = 0; i < numberofTubes; ++i)
				{
					int index1;
					int index2;
					double diameter;

					infile >> index1;
					infile >> index2;
					infile >> diameter;

					Node* node1 = &Nodedata[index1];
					Node* node2 = &Nodedata[index2];

					Tubedata.push_back(Tube(node1, node2, diameter));

					std::cout << std::setw(10) << " Node1: ";
					std::cout << std::setw(5) << node1->id();
					std::cout << std::setw(10) << " Node2: ";
					std::cout << std::setw(5) << node2->id();
					std::cout << std::setw(10) << " Diameter: ";
					std::cout << std::setw(5) << diameter;

					std::cout << std::endl << std::endl;
				}
				// input data from the file


				linalg::Matrix	B;
				B = cie::linalg::Matrix(numberofNodes, numberofNodes, 0);
				std::cout << "The size of zero-initialized permeability Matrix B: ";
				std::cout << B.size1() << " x " << B.size2() << std::endl << std::endl;
				//create zero-initialized permeability matrix

				for (int i = 0;i < numberofTubes;i++)
				{
					const Node* Node1 = Tubedata[i].node1();
					const Node* Node2 = Tubedata[i].node2();

					int id1 = Node1->id();
					int id2 = Node2->id();
					// get id1 and id2 of the two bounding nodes

					double B_i = Tubedata[i].permeability();
					// compute permeability factor B_i

					B(id1, id1) += B_i;
					B(id2, id2) += B_i;
					B(id1, id2) -= B_i;
					B(id2, id1) -= B_i;
					// assemble B_i into the B matrix
				}
				// 1. Set uo permeablity matrix B

				std::cout << "The permeability Matrix B: " << std::endl << std::endl;
				for (int i = 0; i < numberofNodes;++i)
				{
					for (int j = 0;j < numberofNodes; ++j)
						std::cout << std::setw(10) << B(i, j) ;
					std::cout << std::endl << std::endl;
				}
				//Output permeablity matrix B

				std::vector <double> Q(numberofNodes);
				for (int i = 0; i < numberofNodes; ++i)
				{
					Q[i] -= Nodedata[i].flow();
				}
				//2. create load vector Q

				std::cout << "The load vector Q: " << std::endl << std::endl;
				for (int i = 0; i < numberofNodes; ++i)
				{
					std::cout << std::setw(10) << Q.at(i) ;
				}
				std::cout << std::endl << std::endl;
				//Output load vector Q

				for (int i = 0; i < numberofNodes; ++i)
				{
					B(i, 0) = 0;
					B(0, i) = 0;
				}
				B(0, 0) = 1;
				Q[0] = 0;
				//3. Impose boundary condition

				std::cout << "The permeability Matrix B wth boundary condition:: " << std::endl << std::endl;
				for (int i = 0; i < numberofNodes;++i)
				{
					for (int j = 0;j < numberofNodes; ++j)
						std::cout << std::setw(10) << B(i, j) ;
					std::cout << std::endl << std::endl;
				}

				std::cout << "The load vector Q wth boundary condition: " << std::endl << std::endl;
				for (int i = 0; i < numberofNodes; ++i)
				{
					std::cout << std::setw(10) << Q.at(i);
				}
				std::cout << std::endl << std::endl;
				//Output B and Q with boundary condition

				std::vector<double> h = linalg::solve(B, Q);
				//4. Solve linear equation system to get head vector h

				std::cout << "The head vector h: " << std::endl << std::endl;
				for (int i = 0; i < numberofNodes; ++i)
				{
					std::cout << std::setw(10) << h.at(i) ;
				}
				//Output head vector h

				std::vector<double> q(numberofTubes);
				for (int i = 0; i < numberofTubes; ++i)
				{
					q[i] = 0;
				}
				std::cout << std::endl << std::endl;
				// Create zero-initialized vector of fluxes q 

				for (int i = 0; i < numberofTubes; ++i)
				{
					const Node* node1 = Tubedata[i].node1();
					const Node* node2 = Tubedata[i].node2();

					int id1 = node1->id();
					int id2 = node2->id();

					double h1 = h[id1];
					double h2 = h[id2];
					//extract the entries h1 and h2 at the ids of the two bounding nodes from h

					double B_i = Tubedata[i].permeability();
					//compute permeability factor B_i

					q[i] = B_i * (h1 - h2);
					//Postprocess fluxes
				}
				
				std::cout << "The fluxes q: " << std::endl << std::endl;
				for (int i = 0; i < numberofTubes; ++i)
				{
					std::cout << std::setw(10) << q[i];
				}
				//Output fluxes q 
				
				return q;
			}


	}//namespace pipenetwork

}//namespace cie
