lista/%:
	@echo "Compilando $@ -> bin/main"
	g++ $@.cpp -o bin/main \
		-I/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/include/ \
		-I/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/include \
		-L/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/lib/x86-64_linux/static_pic \
		-L/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/lib/x86-64_linux/static_pic \
		-lilocplex -lcplex -lconcert -lm -lpthread -ldl
	@echo "Executando bin/main"
	./bin/main

lista/1_grasp:
	@echo "Compilando $@.cpp -> bin/main"
	g++ $@.cpp -o bin/main
	@echo "Executando bin/main"
	./bin/main 30 < lista/in

lista/1:
	@echo "Compilando $@.cpp -> bin/main"
	g++ $@.cpp -o bin/main
	@echo "Executando bin/main"
	./bin/main 100 < lista/input/1.in