#include "ConnectedComponent.h"

RBLCAM001::ConnectedComponent::ConnectedComponent(int id)
{
    ID = id;
    pixelNum = 0;
}
RBLCAM001::ConnectedComponent::ConnectedComponent(const ConnectedComponent &rhs)
{
    pixelNum = rhs.pixelNum;
    ID = rhs.ID;
    for (size_t i = 0; i < rhs.pixelNum; i++)
    {
        pixels[i]= rhs.pixels[i];
    }
}
RBLCAM001::ConnectedComponent& RBLCAM001::ConnectedComponent::operator=(const ConnectedComponent &rhs)
{
    this->ID=rhs.ID;
    this->pixelNum=rhs.pixelNum;
    for (size_t i = 0; i < rhs.pixelNum; i++)
    {
        this->pixels[i]=rhs.pixels[i];
    }
    return *this;

}
RBLCAM001::ConnectedComponent::ConnectedComponent(ConnectedComponent &&rhs) :
pixelNum{rhs.pixelNum},
ID{rhs.ID}
{
    for (size_t i = 0; i < rhs.pixelNum; i++)
    {
        pixels[i]= rhs.pixels[i];
    }
}

RBLCAM001::ConnectedComponent & RBLCAM001::ConnectedComponent::operator=(ConnectedComponent &&rhs)
{
    if(this!= &rhs){
        pixels = rhs.pixels;
        ID = rhs.ID;
        pixelNum=rhs.pixelNum;
    }
    return *this;
}
RBLCAM001::ConnectedComponent::~ConnectedComponent()
{
    pixelNum = 0;
    ID = -1;    
}



















void RBLCAM001::ConnectedComponent::addPixel(std::pair<int,int> newPixel){
    pixels.push_back(newPixel);
}