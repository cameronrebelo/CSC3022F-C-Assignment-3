GLOBALIGNORE=sloan_image.pgm

findcomp: PGMimageProcessor.o ConnectedComponent.o driver.o
	g++ bin/PGMimageProcessor.o bin/ConnectedComponent.o bin/driver.o -o findcomp -std=c++2a
 
PGMimageProcessor.o: src/PGMimageProcessor.cpp src/PGMimageProcessor.h
	g++ -c src/PGMimageProcessor.cpp -o bin/PGMimageProcessor.o -std=c++2a

ConnectedComponent.o: src/ConnectedComponent.cpp src/ConnectedComponent.h
	g++ -c src/ConnectedComponent.cpp -o bin/ConnectedComponent.o -std=c++2a

driver.o: src/driver.cpp
	g++ -c src/driver.cpp -o bin/driver.o -std=c++2a
   
test:
	./findcomp -t 50 -s 5 100 -p -w output.pgm input.pgm

clean:
	@rm -f bin/*.o
	@rm findcomp
	@rm *.pgm