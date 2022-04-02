#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <vector>
namespace RBLCAM001
{
    class ConnectedComponent
    {
        private:
            int pixelNum, ID;
            std::vector<std::pair<int,int>> pixels;

        public:
            //Big 6
            ConnectedComponent();
            ~ConnectedComponent();
            ConnectedComponent(const ConnectedComponent &rhs);
            ConnectedComponent &operator=(const ConnectedComponent &rhs);
            ConnectedComponent(ConnectedComponent &&rhs);
            ConnectedComponent &operator=(ConnectedComponent &&rhs);
            //Accessors
            int getID();
            int getPixelNum();
            std::vector<std::pair<int,int>> getPixels();
            void addPixel(std::pair<int,int> newPixel);

            };
}

#endif