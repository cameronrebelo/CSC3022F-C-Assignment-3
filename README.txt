RBLCAM001

***Please note that the program is not in a working state. I spent many hours tryin to debug the final verion of the
code but was unable to determine the cause of the segmetnation fault.
**Also note that the unit test are not currently in a state of function.



driver.cpp:
    main class of the program, handles all input from the command line and invokes relavent methods on a PGMimageProcessor object.

ConnectedComponent.cpp:
    class that contains a vector of pairs of ints that represent the coordinates of all pixels conneted in a component.
    also has a unique ID and tracks the number of pixels in the vector
    contains:
        - the big 6
        - accessors for all class members
        - method that allows inseration of pixels into the pixel array

ConnectedComponent.h:
    header file for the ConnectedComponent class, conatains class and function declarations

PGMimageProcessor.cpp:
    class that handles all the processing of the image. serves the purpose of inpur, processing and output
    contains:
        - the big 6
        - accessors for all class members
        - readData method that will place data from a PGM into a data structure
        - writeData method that will write a PGM file with the data of the components
        - BFS and is valid helper methods that traverse the grid and validate cells to be added to a compoenent
        - filterComponentsBySize method to cull components that are out of our desired range
        - print methods to display data to users

PGMimageProcessor.h:
    header file for the PGMimageProcessor class, conatains class and function declarations


Makefile:
    compiles class files found in src and places their object files in bin
        make test: 
        - runs a sample testing version
        make unit_test:
        - compiles unit test to be run
        make clean:
        - removes object files in bin, generated *pgm files and the extractor executable file