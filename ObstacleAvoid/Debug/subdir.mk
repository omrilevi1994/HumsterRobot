################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AStarAlgorithm.cpp \
../Calculations.cpp \
../Cell.cpp \
../ConfigurationManager.cpp \
../Graph.cpp \
../LocalizationManager.cpp \
../Location.cpp \
../Map.cpp \
../RandomWalk.cpp \
../Robot.cpp \
../Waypoint.cpp \
../WaypointManager.cpp \
../main.cpp 

OBJS += \
./AStarAlgorithm.o \
./Calculations.o \
./Cell.o \
./ConfigurationManager.o \
./Graph.o \
./LocalizationManager.o \
./Location.o \
./Map.o \
./RandomWalk.o \
./Robot.o \
./Waypoint.o \
./WaypointManager.o \
./main.o 

CPP_DEPS += \
./AStarAlgorithm.d \
./Calculations.d \
./Cell.d \
./ConfigurationManager.d \
./Graph.d \
./LocalizationManager.d \
./Location.d \
./Map.d \
./RandomWalk.d \
./Robot.d \
./Waypoint.d \
./WaypointManager.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


