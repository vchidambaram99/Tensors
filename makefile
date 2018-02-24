.PHONY: clean directories
source = $(shell find . -name *.cpp)
goal := executable
ifneq ($(MAKECMDGOALS),)
goal := $(MAKECMDGOALS)
endif
objects = $(patsubst ./src/%.cpp,./build/$(goal)/%.o, $(source))
depends = $(patsubst ./src/%.cpp,./build/$(goal)/%.d, $(source))
compile = g++ -Wall -o $@ -O3 -std=c++17 -DNDEBUG -ffast-math -march=native -fopenmp
debug   = g++ -Wall -o $@ -Og -std=c++17 -ffast-math -march=native -fopenmp
singleE = g++ -Wall -o $@ -O3 -std=c++17 -DNDEBUG -ffast-math -march=native #executable but no multithreading
singleD = g++ -Wall -o $@ -Og -std=c++17 -ffast-math -march=native #debug but no multithreading
noOpt = g++ -Wall -o $@ -std=c++17 #no optimizations (SSE/AVX instructions, multithreading, etc)
buildFolders = $(sort $(dir $(objects)))

executable: $(objects) makefile
	$(compile) $(objects)

debug: $(objects) makefile
	$(debug) $(objects)

singleE: $(objects) makefile
	$(singleE) $(objects)

singleD: $(objects) makefile
	$(singleD) $(objects)

noOpt: $(objects) makefile
	$(noOpt) $(objects)

./build/executable/%.o:./src/%.cpp makefile | $(buildFolders)
	$(compile) -c $< -MMD -MP

./build/debug/%.o:./src/%.cpp makefile | $(buildFolders)
	$(debug) -c $< -MMD -MP

./build/singleE/%.o:./src/%.cpp makefile | $(buildFolders)
	$(singleE) -c $< -MMD -MP

./build/singleD/%.o:./src/%.cpp makefile | $(buildFolders)
	$(singleD) -c $< -MMD -MP

./build/noOpt/%.o:./src/%.cpp makefile | $(buildFolders)
	$(noOpt) -c $< -MMD -MP

$(buildFolders):
	mkdir -p $(buildFolders)

clean:
	rm -rf build
	rm -f executable
	rm -f debug
	rm -f singleE
	rm -f singleD
	rm -f noOpt

ifneq ($(MAKECMDGOALS),clean)
-include $(depends)
endif
