all: 
	g++ -Wall NasaLaunchAnalysis.cpp -o nasa
	
run:
	./nasa

	
try:all run
