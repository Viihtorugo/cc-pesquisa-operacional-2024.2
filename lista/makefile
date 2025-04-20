lista/%: clear
	@echo "Compilando $@ -> bin/main"
	g++ $@.cpp -o bin/main \
		-I/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/include/ \
		-I/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/include \
		-L/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/lib/x86-64_linux/static_pic \
		-L/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/lib/x86-64_linux/static_pic \
		-lilocplex -lcplex -lconcert -lm -lpthread -ldl
	@echo "Executando bin/main"
	./bin/main

1q: clear
	@echo "Compilando 1q/main.cpp -> bin/main"
	g++ 1q/main.cpp -o bin/main
	@echo "Executando bin/main"
	./bin/main 10 < 1q/input/2.in

test: clear
	@echo "Compilando test.cpp -> bin/main"
	g++ test.cpp -o bin/main \
		-I/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/include/ \
		-I/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/include \
		-L/opt/ibm/ILOG/CPLEX_Studio_Community2212/cplex/lib/x86-64_linux/static_pic \
		-L/opt/ibm/ILOG/CPLEX_Studio_Community2212/concert/lib/x86-64_linux/static_pic \
		-lilocplex -lcplex -lconcert -lm -lpthread -ldl
	@echo "Executando bin/main"
	./bin/main

clear:
	rm -rf bin/main