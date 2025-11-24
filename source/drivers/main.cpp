#include <iostream>
#include <fstream>

#include "Node.hpp"
#include "PipeNetwork.hpp"

#include "linalg.hpp"


int main()
{
	std::string filename = "pipedata.txt";

	std::ofstream outfile(filename);

    outfile.is_open();

	outfile << 
        "8              \n"
        "11             \n"
        "   0    0  -50 \n"
        "1000    0  -50 \n"
        "2000    0    0 \n"
        "   0  500    0 \n"
        " 500  500    0 \n"
        "   0 1000  -50 \n"
        "1000 1000    0 \n"
        "2000 1000  150 \n"
        "0 1 0.5        \n"
        "1 2 0.5        \n"
        "0 3 0.5        \n"
        "3 4 0.5        \n"
        "4 1 0.5        \n"
        "1 7 0.5        \n"
        "2 7 0.5        \n"
        "3 5 0.5        \n"
        "5 6 0.5        \n"
        "4 6 0.5        \n"
        "6 7 0.5        \n";

    outfile.close();

	cie::pipenetwork::PipeNetwork a1(filename);

	a1.computeFluxes();

	return 0;
}