#include "ConnectedComponent.h"

//Default Constructor
RBLCAM001::ConnectedComponent::ConnectedComponent(int id)
{
    ID = id;
    pixelNum = 0;
}

//Copy Constructor
RBLCAM001::ConnectedComponent::ConnectedComponent(const ConnectedComponent &rhs)
{
    pixelNum = rhs.pixelNum;
    ID = rhs.ID;
    for (size_t i = 0; i < rhs.pixelNum; i++)
    {
        pixels[i] = rhs.pixels[i];
    }
}

//Copy assignment operator
RBLCAM001::ConnectedComponent &RBLCAM001::ConnectedComponent::operator=(const ConnectedComponent &rhs)
{
    this->ID = rhs.ID;
    this->pixelNum = rhs.pixelNum;
    for (size_t i = 0; i < rhs.pixelNum; i++)
    {
        this->pixels[i] = rhs.pixels[i];
    }
    return *this;
}

//Move Constructor
RBLCAM001::ConnectedComponent::ConnectedComponent(ConnectedComponent &&rhs) : pixelNum{rhs.pixelNum},ID{rhs.ID}
{
    for (size_t i = 0; i < rhs.pixelNum; i++)
    {
        pixels[i] = rhs.pixels[i];
    }
}

//Move assignment operator
RBLCAM001::ConnectedComponent &RBLCAM001::ConnectedComponent::operator=(ConnectedComponent &&rhs)
{
    if (this != &rhs)
    {
        pixels = rhs.pixels;
        ID = rhs.ID;
        pixelNum = rhs.pixelNum;
    }
    return *this;
}

//Destructor
RBLCAM001::ConnectedComponent::~ConnectedComponent()
{
    pixelNum = 0;
    ID = -1;
}

//Methods 

//Returns ID
int RBLCAM001::ConnectedComponent::getID() const
{
    return ID;
}

//Returns amount of pixels
int RBLCAM001::ConnectedComponent::getPixelNum() const
{
    return pixelNum;
}

//Returns vector or coordinates of pixels
std::vector<std::pair<int, int>> RBLCAM001::ConnectedComponent::getPixels() const
{
    return pixels;
}

//Adds a pixel by coordinate to the vector
void RBLCAM001::ConnectedComponent::addPixel(std::pair<int, int> newPixel)
{
    pixels.push_back(newPixel);
    pixelNum++;
}