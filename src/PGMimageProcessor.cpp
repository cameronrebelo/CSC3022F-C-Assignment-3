#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "PGMimageProcessor.h"

RBLCAM001::PGMimageProcessor::PGMimageProcessor(std::string filename)
{
    fileName = filename;
}

RBLCAM001::PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &rhs)
{
    fileName = rhs.fileName;
    for (size_t i = 0; i < rhs.compVector.size(); i++)
    {
        *(compVector[i]) = *(rhs.compVector[i]); 
    }
    
}

RBLCAM001::PGMimageProcessor& RBLCAM001::PGMimageProcessor::operator=(const PGMimageProcessor &rhs)
{
    this->fileName=rhs.fileName;
    for (size_t i = 0; i < rhs.compVector.size(); i++)
    {
        * compVector[i] = *(rhs.compVector[i]);
    }
    return *this;

}

RBLCAM001::PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&rhs)
{
    fileName = rhs.fileName;
    rhs.fileName = "";
    std::move(begin(rhs.compVector), end(rhs.compVector), std::inserter(compVector, end(compVector)));
    
}

//move assignment

//destrcutor

int RBLCAM001::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{   
    int compNum = 0;
    // begin reading in data from file
    std::string line = "";
    std::ifstream file(fileName, std::ios::binary);
    file.unsetf(std::ios_base::skipws);
    std::stringstream ss;
    int width, height;

    getline(file, line);
    if (line.compare("P5") != 0)
    {
        std::cerr << "error" << std::endl;
    }
    else
    {
        getline(file, line);
        while (line[0] == '#')
        {
            getline(file, line);
        }
        ss << line;
        ss >> width >> height;
        int length = width * height;
        getline(file >> std::ws, line);
        unsigned char **fileRead = new unsigned char *[height]; // array to store all pixel data
        for (size_t i = 0; i < height; i++)
        {
            fileRead[i] = new unsigned char[width];
            for (size_t j = 0; j < width; j++)
            {
                unsigned char test;
                file >> test;
                if (test >= threshold)
                {
                    fileRead[i][j] = 255;
                }
                else
                {
                    fileRead[i][j] = 0;
                }
            }
        }
        file.close();

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (fileRead[i][j] == 255)
                {
                    RBLCAM001::ConnectedComponent temp(compNum);
                    compNum ++;
                    temp.addPixel(std::pair<int,int> (i,j));
                    fileRead[i][j] = 0;
                }
            }
        }
    }
}

//filterComponentsBySize

//writeComponents


int RBLCAM001::PGMimageProcessor::getComponentCount(void) const
{
    return compVector.size();
}
int RBLCAM001::PGMimageProcessor::getLargestSize(void) const
{
    int largest = 0;
    for (size_t i = 0; i < compVector.size(); i++)
    {
        if(compVector[i]->getPixelNum() > largest)
        {
            largest = compVector[i]->getPixelNum();
        }
    }
    return largest;
}
int RBLCAM001::PGMimageProcessor::getSmallestSize(void) const
{
    int smallest = 0;
    for (size_t i = 0; i < compVector.size(); i++)
    {
        if(compVector[i]->getPixelNum() < smallest)
        {
            smallest = compVector[i]->getPixelNum();
        }
    }
    return smallest;
}
