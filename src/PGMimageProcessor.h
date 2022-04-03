#ifndef PGM_IMAGE_PROCESSOR_H
#define PGM_IMAGE_PROCESSOR_H

#include "ConnectedComponent.h"
#include <vector>
#include <memory>
#include <string>

namespace RBLCAM001
{
    class PGMimageProcessor
    {
        private:
            std::vector<std::unique_ptr<ConnectedComponent>> compVector;
            std::string fileName;

        public:
            //Big 6
            PGMimageProcessor(std::string file);
            ~PGMimageProcessor();
            PGMimageProcessor(const PGMimageProcessor &rhs);
            PGMimageProcessor &operator=(const PGMimageProcessor &rhs);
            PGMimageProcessor(PGMimageProcessor &&rhs);
            PGMimageProcessor &operator=(PGMimageProcessor &&rhs);
            
            //Methods
            unsigned char ** readData(unsigned char threshold);
            int extractComponents(unsigned char threshold, int minValidSize);
            int filterComponentsBySize(int minSize, int maxSize);
            bool writeComponents(const std::string & outFileName);

            //Accessors
            int getComponentCount(void) const;
            int getLargestSize(void) const;
            int getSmallestSize(void) const;

            //Printing
            void printComponentData(const ConnectedComponent &theComponent) const;
    };
}

#endif