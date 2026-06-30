# Config for Post-Modern C
CXX      := g++
CXX_STD  := --std=c++26 -fno-rtti
MOD_FLAG := -fmodules-ts

MODE      ?= debug
# Default as many wayland users have XWayland
WINDOWING ?= x11

VALID_TARGETS := core

# TODO: set OS target
# OS :=

ifeq ($(filter clean,$(MAKECMDGOALS)),)
    ifeq ($(filter $(TARGET),$(VALID_TARGETS)),)
        $(error TARGET must be one of: $(VALID_TARGETS))
    endif
endif

BUILD_DIR := build

SRCS 			:= $(shell find src/$(TARGET) -name *.cpp)
DATA_STRUCTURES := $(shell find src/data_structures -name *.cpp)

# We need to compile the data structures before the core engine
OBJS := $(DATA_STRUCTURES:%=$(BUILD_DIR)/%.o)
OBJS += $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CXXFLAGS := $(CXX_STD) $(MOD_FLAG)
CXXFLAGS += $(addprefix -I,$(INC_DIRS))

LIBS :=

ifeq ($(WINDOWING), x11)
    CXXFLAGS += -DPLATFORM_LINUX_X11
    LIBS     += -lX11
else ifeq ($(WINDOWING), wayland)
    CXXFLAGS += -DPLATFORM_LINUX_WAYLAND
else
    $(error Unknown WINDOWING option: $(WINDOWING). Choose 'x11' or 'wayland')
endif

WARN_FLAGS    := -Wall -Wextra -Werror
DBG_FLAGS     := -ggdb -O0
RELEASE_FLAGS := -Ofast -flto -march=native -DNDEBUG

LDFLAGS :=

ifeq ($(filter $(MODE),debug),$(MODE))
    CXXFLAGS += $(WARN_FLAGS) $(DBG_FLAGS)
else
    CXXFLAGS += $(RELEASE_FLAGS)
endif

BIN := $(BUILD_DIR)/$(MODE)/$(TARGET)

$(BIN): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS) $(LDFLAGS)

# Modules need to be built in a specific order to work

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# System headers to pre-compile as modules
# C headers
SYS_HEADERS := cstdint cstdio cassert cstdlib cstring
# Temporary headers
SYS_HEADERS += vector
# Build/debug headers
SYS_HEADERS += type_traits

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
