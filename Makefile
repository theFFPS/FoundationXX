CXX ?= c++
CXX_OPTS ?= -Wall -Werror -Wextra -g -I./inc -std=c++20

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,src,*.cpp)          
SRC_EXAMPLE = $(call rwildcard,example,*.cpp)          
OBJS = $(patsubst src/%.cpp, bin/%.cpp.o, $(SRC))
EXEC_EXAMPLE = $(patsubst example/%.cpp, example/target/%, $(SRC_EXAMPLE))

all:
	@echo "You should compile it by using OS-specific build script or via make <OSNAME>"
linux: $(OBJS)
	@mkdir -p build
	@mkdir -p example/target
	@$(CXX) $(CXX_OPTS) -o target/libfoundationxx.so $(OBJS) -shared
example/target/%: example/%.cpp
	@mkdir -p example/target
	@echo "    CC $^"
	@mkdir -p $(@D)
	@$(CXX) $(CXX_OPTS) $^ -o $@
bin/%.cpp.o: src/%.cpp
	@mkdir -p bin
	@echo "    CC $^"
	@mkdir -p $(@D)
	@$(CXX) $(CXX_OPTS) -c $^ -o $@
clear:
	@rm -rf bin/* target/*