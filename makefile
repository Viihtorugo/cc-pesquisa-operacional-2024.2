build:
	g++ lista/2.1.cpp -o bin/main \
  -I/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/include/ \
  -I/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/include \
  -L/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/lib/x86-64_linux/static_pic \
  -L/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/lib/x86-64_linux/static_pic \
  -lilocplex -lcplex -lconcert -lm -lpthread -ldl

run:
	./bin/main