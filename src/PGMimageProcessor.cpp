#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>
#include "PGMimageProcessor.h"



int height,width = 0;

int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, 1, 0, -1 };
 
// Function to check if a cell
// is be visited or not
bool isValid(unsigned char*** grid, int row, int col, unsigned char threshold)
{
    // If cell lies out of bounds
    if (row < 0 || col < 0
        || row >= height || col >= width)
        return false;
 
    // If cell is already visited
    if (*grid[row][col]<threshold)
        return false;
 
    // Otherwise
    return true;
}
 
// Function to perform the BFS traversal
void BFS(unsigned char *** grid, int row, int col, RBLCAM001::ConnectedComponent & comp, unsigned char threshold) //based on a bfs algortihm from https://www.geeksforgeeks.org/breadth-first-traversal-bfs-on-a-2d-array/
{
    // Stores indices of the matrix cells
    std::queue<std::pair<int, int> > q;
 
    // Mark the starting cell as visited
    // and push it into the queue
    q.push({ row, col });
    *grid[row][col] = 0;
 
    // Iterate while the queue
    // is not empty
    while (!q.empty()) {
 
        std::pair<int, int> cell = q.front();
        int x = cell.first;
        int y = cell.second;
 
        comp.addPixel(cell);
 
        q.pop();
 
        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {
 
            int adjx = x + dRow[i];
            int adjy = y + dCol[i];
 
            if (isValid(grid,adjx, adjy,threshold)) {
                q.push({ adjx, adjy });
                *grid[adjx][adjy] = 0;
            }
        }
    }
}

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
    unsigned char ** grid = readData(threshold);
    // begin reading in data from file

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (isValid(&grid, i, j, threshold))
                {
                    RBLCAM001::ConnectedComponent temp(compNum);
                    compNum ++;
                    BFS(&grid, i, j, temp, threshold);
                }
            }
        }
    
}

//filterComponentsBySize

//writeComponents

unsigned char ** RBLCAM001::PGMimageProcessor::readData(unsigned char threshold)
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
