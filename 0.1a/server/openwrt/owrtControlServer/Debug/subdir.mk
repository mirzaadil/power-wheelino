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
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-openwrt-linux-g++ -I/home/kranzrm/Downloads/OpenWrt-SDK-brcm47xx-for-Linux-i686-gcc-4.3.3+cs_uClibc-0.9.30.1/staging_dir/target-mipsel_uClibc-0.9.30.1/usr/include/ -I"/home/kranzrm/workspace/owrtControlServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


