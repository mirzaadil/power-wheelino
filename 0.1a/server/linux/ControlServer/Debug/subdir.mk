################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ControlServer.cpp 

OBJS += \
./ControlServer.o 

CPP_DEPS += \
./ControlServer.d 


# Each subdirectory must supply rules for building sources it contributes
ControlServer.o: ../ControlServer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"ControlServer.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


