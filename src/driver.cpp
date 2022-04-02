#include <iostream>
#include <string>
#include <vector>
#include "PGMimageProcessor.h"

int main(int argc, char* argv[])
{

    //readin CLI's
    std::string filename = argv[argc-1];
    int threshold; 
    int min = 3;
    int max;
    std::string writeFileName;
    bool printing;
    
    //amount of operations to be done stored in vector with corresponding file name
    std::vector<std::vector<std::string>> writeOptions;
    int writes = 0;

    for (size_t i = 2; i < argc; i++)
    {
        if(std::string(argv[i]) == "-t")
        {
            threshold = stoi(std::string(argv[i+1]));
        }
        if(std::string(argv[i]) == "-s")
        {           
            min = stoi(std::string(argv[i+1]));
            max = stoi(std::string(argv[i+2]));
        }
        if (std::string(argv[i]) == "-w")
        { 
            writeFileName = argv[i + 1];
        }
        if (std::string(argv[i]) == "-p")
        { 
            printing = true;
        }
        
    }

    RBLCAM001::PGMimageProcessor p(filename);
    


}