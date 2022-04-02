#include "ConnectedComponent.h"

RBLCAM001::ConnectedComponent::ConnectedComponent()
{
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
RBLCAM001::ConnectedComponent::ConnectedComponent &operator=(const ConnectedComponent &rhs)
{

}



















void RBLCAM001::ConnectedComponent::addPixel(std::pair<int,int> newPixel){
    pixels.push_back(newPixel);
}