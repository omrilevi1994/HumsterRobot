################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Calculations.cpp \
../LocalizationManager.cpp \
../Location.cpp \
../Map.cpp \
../RandomWalk.cpp \
../Robot.cpp \
../main.cpp 

OBJS += \
./Calculations.o \
./LocalizationManager.o \
./Location.o \
./Map.o \
./RandomWalk.o \
./Robot.o \
./main.o 

CPP_DEPS += \
./Calculations.d \
./LocalizationManager.d \
./Location.d \
./Map.d \
./RandomWalk.d \
./Robot.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


