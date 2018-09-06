CC = g++ -O3 -std=c++11
LDFLAGS = -lpthread -L. -leshyperneat -lneat


all: xor.cpp 
	@mkdir -p bin
	@mkdir -p XOR_results_files
	@rm -f XOR_results_files/**
	$(CC) ./xor.cpp -o ./bin/XOR $(LDFLAGS) 


run:
	@mkdir -p ./XOR_results_files
	./bin/XOR user_definitions/user_def_standart genetics_encodings/test_encoding ./XOR_results_files/


clean:
	@cd ..; make clean
	@rm -rf XOR_results_files/ bin