compiler		=	g++

cpp_standard	=	-std=c++11

main			=	src/PSN_Test_Server.cpp

# libs			=	src/PSN_Test_Server_LC.hpp

# flags			=	-lglfw

final_name		=	PSN_Test_Server

success: compile
	@echo "-------------------------------------"
	@echo "\tSuccessfully Compiled"
	@echo "-------------------------------------"

compile:
	$(compiler) $(cpp_standard) $(main) -o $(final_name)
# $(compiler) $(cpp_standard) $(main) $(libs) $(flags) -o $(final_name)

run:
	./PSN_Test_Server.exe