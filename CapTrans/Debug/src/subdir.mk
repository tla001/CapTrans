################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/captest.c \
../src/capvideo.c \
../src/disOnframebuffer.c \
../src/ipuprocess.c \
../src/mytimer.c \
../src/udptrans.c 

OBJS += \
./src/captest.o \
./src/capvideo.o \
./src/disOnframebuffer.o \
./src/ipuprocess.o \
./src/mytimer.o \
./src/udptrans.o 

C_DEPS += \
./src/captest.d \
./src/capvideo.d \
./src/disOnframebuffer.d \
./src/ipuprocess.d \
./src/mytimer.d \
./src/udptrans.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-linux-gnueabi-gcc -I"/home/tla001/workspace/CapTrans/inc" -I"/home/tla001/workspace/CapTrans/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


