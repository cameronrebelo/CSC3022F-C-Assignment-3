GLOBALIGNORE=sloan_image.pgm

extractor: FrameSequence.o extractor.o
	g++ bin/FrameSequence.o bin/extractor.o -o extractor -std=c++2a
 
FrameSequence.o: src/FrameSequence.cpp src/extractor.h
	g++ -c src/FrameSequence.cpp -o bin/FrameSequence.o -std=c++2a

extractor.o: src/extractor.cpp src/extractor.h
	g++ -c src/extractor.cpp -o bin/extractor.o -std=c++2a
   
test:
	./extractor sloan_image.pgm -t 0 0 100 100 -s 100 100 -w none base1 -w reverse base2 -w invert base3 -w revinvert base4 

clean:
	@rm -f bin/*.o
	@rm extractor
	mv sloan_image.pgm data
	@rm *.pgm
	mv data/sloan_image.pgm .