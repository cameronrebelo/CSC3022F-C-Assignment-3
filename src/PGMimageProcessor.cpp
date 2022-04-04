#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>
#include "PGMimageProcessor.h"

int height, width = 0;



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

RBLCAM001::PGMimageProcessor &RBLCAM001::PGMimageProcessor::operator=(const PGMimageProcessor &rhs)
{
    this->fileName = rhs.fileName;
    for (size_t i = 0; i < rhs.compVector.size(); i++)
    {
        *compVector[i] = *(rhs.compVector[i]);
    }
    return *this;
}

RBLCAM001::PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&rhs)
{
    fileName = rhs.fileName;
    rhs.fileName = "";
    std::move(begin(rhs.compVector), end(rhs.compVector), std::inserter(compVector, end(compVector)));
}

RBLCAM001::PGMimageProcessor &RBLCAM001::PGMimageProcessor::operator=(PGMimageProcessor &&rhs)
{
    if (this != &rhs)
    {
        fileName = rhs.fileName;
        compVector = rhs.compVector;
    }
    return *this;
}

RBLCAM001::PGMimageProcessor::~PGMimageProcessor()
{
    for (size_t i = 0; i < compVector.size(); i++)
    {
        compVector[i] = nullptr;
    }
}

//Methods 

bool isValid(unsigned char **grid, int row, int col, unsigned char threshold)
{
    // If cell lies out of bounds
    if (row < 0 || col < 0 || row >= height || col >= width)
        return false;

    // If cell is already visited
    if (grid[row][col] < threshold)
        return false;

    // Otherwise
    return true;
}

// Function to perform the BFS traversal
void BFS(unsigned char **grid, int row, int col, RBLCAM001::ConnectedComponent &comp, unsigned char threshold) // based on a bfs algortihm from https://www.geeksforgeeks.org/breadth-first-traversal-bfs-on-a-2d-array/
{
    int dRow[] = {-1, 0, 1, 0};
    int dCol[] = {0, 1, 0, -1};

    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int,int> (row, col));
    grid[row][col] = 0;

    while (!q.empty())
    {

        std::pair<int, int> cell = q.front();
        int x = cell.first;
        int y = cell.second;

        comp.addPixel(cell);

        q.pop();

        // Go to the adjacent cells
        for (int i = 0; i < 4; i++)
        {

            int adjx = x + dRow[i];
            int adjy = y + dCol[i];

            if (isValid(grid, adjx, adjy, threshold))
            {

                q.push({adjx, adjy});

                grid[adjx][adjy] = 0;
            }
        }
    }
}

int RBLCAM001::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
    int compNum = 0;
    unsigned char **grid = readData(threshold);
    // begin reading in data from file

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (isValid(grid, i, j, threshold))
            {
                RBLCAM001::ConnectedComponent temp(compNum);
                BFS(grid, i, j, temp, threshold);

                if (temp.getPixelNum() >= minValidSize)
                {
                    compVector.push_back(std::make_shared<RBLCAM001::ConnectedComponent>(temp));
                    compNum++;
                }
            }
        }
    }
    std::cout << compNum << std::endl;
    return compNum;
}

int RBLCAM001::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){

    // std::vector<std::shared_ptr<ConnectedComponent>>::iterator it = compVector.begin();
    // while(it!=compVector.end())
    // {
    //     if(**it.getPixelNum()>maxSize || it->getPixelNum()<minSize)
    //     {

    //     }
    // }
    compVector.erase(std::remove_if(compVector.begin(), compVector.end(),
                       [minSize,maxSize](std::shared_ptr<RBLCAM001::ConnectedComponent> c) -> bool 
                       { if(c->getPixelNum()<minSize || c->getPixelNum()>maxSize)
                            {
                           return true;
                       } }),
        compVector.end());
    
}

bool RBLCAM001::PGMimageProcessor::writeComponents(const std::string & outFileName)
{
    unsigned char output[height][width];
    memset(output,0,sizeof(output));
    for (size_t i = 0; i < compVector.size(); i++)
    {
        for (size_t j = 0; j < compVector[i]->getPixelNum(); j++)
        {
            std::pair<int, int> cell = compVector[i]->getPixels()[j];
            int x = cell.first;
            int y = cell.second;
            output[x][y] = (unsigned char)255;
        }
        
    }
            std::ofstream out(outFileName, std::ios::binary);
            out << "P5" << std::endl;
            out << "#RBLCAM001 Image Processor" << std::endl;
            out << width << "  " << height << std::endl;
            out << "255" << std::endl;
            for (size_t j = 0; j < height; j++)
            {
                for (size_t k = 0; k < width; k++)
                {
                    out << output[j][k];
                }
            }
            out.close();
    return true;
}

unsigned char **RBLCAM001::PGMimageProcessor::readData(unsigned char threshold)
{
    std::string line = "";
    std::ifstream file(fileName, std::ios::binary);
    file.unsetf(std::ios_base::skipws);
    std::stringstream ss;

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
                file >> fileRead[i][j];
            }
        }
        file.close();
        return fileRead;
    }
}

int RBLCAM001::PGMimageProcessor::getComponentCount(void) const
{
    return compVector.size();
}

int RBLCAM001::PGMimageProcessor::getLargestSize(void) const
{
    int largest = 0;
    for (size_t i = 0; i < compVector.size(); i++)
    {
        if (compVector[i]->getPixelNum() > largest)
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
        if (compVector[i]->getPixelNum() < smallest)
        {
            smallest = compVector[i]->getPixelNum();
        }
    }
    return smallest;
}

void RBLCAM001::PGMimageProcessor::print()
{
    std::cout << "Components:" << std::endl;
    for (size_t i = 0; i < compVector.size(); i++)
    {
        printComponentData(*compVector[i]);
    }
    std::cout << "\n\nThe Total number of components was " << sizeof(compVector) << std::endl;
    std::cout << "\n\nThe Smallest component was " << getSmallestSize() << std::endl;
    std::cout << "\n\nThe Sargest component was " << getLargestSize() << std::endl;
    
}


void RBLCAM001::PGMimageProcessor::printComponentData(const RBLCAM001::ConnectedComponent &theComponent) const
{
    std::cout << theComponent.getID() << " - Size: " << theComponent.getPixelNum() << std::endl;
}
