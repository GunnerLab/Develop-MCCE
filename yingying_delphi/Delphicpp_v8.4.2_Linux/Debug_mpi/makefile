################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

CC=mpicc
CXX=mpicxx
CXXFLAGS= -w -g -O0 -DPARALLEL_MPI -DNDEBUG --std=c++11 -mtune=native -march=native -mfpmath=sse 

CFLAGS= -w -g -O0 -DPARALLEL_MPI -DNDEBUG --std=c++11 -mtune=native -march=native -mfpmath=sse

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/dplt/subdir.mk
-include src/delphi/subdir.mk
-include src/space/subdir.mk
-include src/solver/subdir.mk
-include src/site/subdir.mk
-include src/misc/subdir.mk
-include src/io/subdir.mk
-include src/interface/subdir.mk
-include src/energy/subdir.mk
-include src/app/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs


# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: delphicpp_mpi_debug

# Tool invocations
delphicpp_mpi_debug: $(OBJS) $(USER_OBJS) $(DPLTOBJECTS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	mpicxx -o "delphicpp_mpi_debug" $(CXXFLAGS) $(OBJS) $(USER_OBJS) $(LIBS) $(DPLTOBJECTS) 
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(DPLTOBJECTS)$(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) delphicpp_mpi_debug
	-@echo ' '
wipe:
	rm rank* eps* phi*

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
