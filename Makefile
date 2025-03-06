all: 
	g++ -Wall NasaLaunchAnalysis.cpp -o nasa
	g++ -g -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -g -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt
	
run:
	./nasa
	./tct
	./pdt

	
try:all run
