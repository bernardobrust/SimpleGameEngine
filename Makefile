# Config for Post-Modern C
CXX       := g++
CXX_STD   := --std=c++26
CXX_MOD   := -fmodules-ts
CXX_EXTRA := -fno-rtti -fno-exceptions
CXXFLAGS  := $(CXX_STD) $(CXX_MOD)  $(CXX_EXTRA)

MODE      ?= debug
# Default as many wayland users have XWayland
WINDOWING ?= X11

VALID_TARGETS := core

# TODO: set OS target (useless for now)
OS := gnu_linux

ifeq ($(filter clean,$(MAKECMDGOALS)),)
    ifeq ($(filter $(TARGET),$(VALID_TARGETS)),)
        $(error TARGET must be one of: $(VALID_TARGETS))
    endif
endif

BUILD_DIR := build

# Build order:
# Data Structures -> Platform Layer -> Core
OBJS :=

# We need to compile the data structures before the core engine
DATA_STRUCTURES := $(shell find src/data_structures -name *.cpp)
OBJS 			+= $(DATA_STRUCTURES:%=$(BUILD_DIR)/%.o)

# Platform layer
PLATFORM := $(shell find src/platform -name *.cpp)
OBJS 	 += $(PLATFORM:%=$(BUILD_DIR)/%.o)

SRCS := $(shell find src/$(TARGET) -name *.cpp)
OBJS += $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

LIBS :=

# We are not using pthreads now but we'll likely use it latter
ifeq ($(OS), gnu_linux)
	LIBS += -lpthread
endif

ifeq ($(WINDOWING), X11)
    CXXFLAGS += -DPLATFORM_GNU_LINUX_X11
    LIBS     += -lX11
else ifeq ($(WINDOWING), wayland)
    CXXFLAGS += -DPLATFORM_GNU_LINUX_WAYLAND
else
    $(error Unknown WINDOWING option: $(WINDOWING). Choose 'X11' or 'wayland')
endif

# Werror can be annoying but it's usefull to force reasonable code
WARN_FLAGS    := -Wall -Wextra -Wpedantic -Wshadow -Werror
DBG_FLAGS     := -ggdb -Og
RELEASE_FLAGS := -Ofast -flto -march=native -DNDEBUG

LDFLAGS :=

ifeq ($(filter $(MODE),debug),$(MODE))
    CXXFLAGS += $(WARN_FLAGS) $(DBG_FLAGS)
else
    CXXFLAGS += $(RELEASE_FLAGS)
    LDFLAGS  += -Wl,-s
endif

BIN := $(BUILD_DIR)/$(MODE)/$(TARGET)

# This compiles the objects in the order they are defined
$(BIN): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS) $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# System headers to pre-compile as modules
# Used in release builds
SYS_HEADERS := cstdlib cstring
# Build/debug headers
SYS_HEADERS += type_traits cassert iostream

.PHONY: clean test setup

setup:
ifeq ($(wildcard gcm.cache),)
	@echo "Pre-compiling system headers..."
	@mkdir -p gcm.cache
	@for hdr in $(SYS_HEADERS); do \
		$(CXX) $(CXXFLAGS) -xc++-system-header $$hdr; \
	done
else
	@echo "gcm modules already exist. Skipping setup."
endif

$(OBJS): | setup

test: $(BIN)
	./$(BIN)

clean:
	rm -rf build gcm.cache

-include $(DEPS)
