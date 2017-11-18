.PHONY: clean directories
source = $(shell find . -name *.cpp)
goal := executable
ifeq ($(MAKECMDGOALS),debug)
goal := debug
endif
objects = $(patsubst ./src/%.cpp,./build/$(goal)/%.o, $(source))
depends = $(patsubst ./src/%.cpp,./build/$(goal)/%.d, $(source))
compile = g++ -Wall -o $@ -O3 -std=c++14
debug = g++ -Wall -o $@ -Og -std=c++14
buildFolders = $(sort $(dir $(objects)))

executable: $(objects)
	$(compile) $(objects)

debug: $(objects)
	$(debug) $(objects)

./build/executable/%.o:./src/%.cpp | $(buildFolders)
	$(compile) -c $< -MMD -MP

./build/debug/%.o:./src/%.cpp | $(buildFolders)
	$(debug) -c $< -MMD -MP

$(buildFolders):
	mkdir -p $(buildFolders)

clean:
	rm -rf build
	rm -f release
	rm -f debug

ifneq ($(MAKECMDGOALS),clean)
-include $(depends)
endif
