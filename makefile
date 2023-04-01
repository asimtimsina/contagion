contagion: main.o Simulation.o Agent.o closenesscentrality.o degreecentrality.o distributeequally.o distributeproportionally.o distributerandomly.o 
	g++ -o contagion main.o Simulation.o Agent.o closenesscentrality.o degreecentrality.o distributeequally.o distributeproportionally.o distributerandomly.o 
	
main.o: main.o Simulation.h
	g++ -c main.cpp
	
Agent.o: Agent.h Agent.cpp
	g++ -c Agent.cpp
	
closenesscentrality.o:  Agent.cpp closenesscentrality.h closenesscentrality.cpp
	g++ -c closenesscentrality.cpp
	
degreecentrality.o: Agent.cpp degreecentrality.h degreecentrality.cpp
	g++ -c degreecentrality.cpp
	
distributeequally.o: distributeequally.h distributeequally.cpp Agent.h 
	g++ -c distributeequally.cpp
	
distributeproportionally.o: distributeproportionally.h distributeproportionally.cpp Agent.h  distributeequally.h
	g++ -c distributeproportionally.cpp
	
distributerandomly.o: distributerandomly.h distributerandomly.cpp Agent.h 
	g++ -c distributerandomly.cpp
	
Simulation.o: Agent.cpp closenesscentrality.h degreecentrality.h distributeequally.h distributeproportionally.h distributerandomly.h Simulation.h Simulation.cpp
