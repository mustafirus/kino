################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Action.cpp \
../src/DBCursor.cpp \
../src/DataBase.cpp \
../src/DataContext.cpp \
../src/DbException.cpp \
../src/Dict.cpp \
../src/Exception.cpp \
../src/FCapts.cpp \
../src/Field.cpp \
../src/FrameThread.cpp \
../src/FrameWnd.cpp \
../src/OdbcCursor.cpp \
../src/OdbcDataBase.cpp \
../src/OdbcException.cpp \
../src/QField.cpp \
../src/QRestr.cpp \
../src/QTable.cpp \
../src/Query.cpp \
../src/RField.cpp \
../src/RKey.cpp \
../src/RLink.cpp \
../src/ROut.cpp \
../src/RSField.cpp \
../src/RSWhere.cpp \
../src/Record.cpp \
../src/RecordSet.cpp \
../src/Rib.cpp \
../src/SqlStmt.cpp \
../src/StMdfr.cpp \
../src/TabMap.cpp \
../src/Table.cpp \
../src/TempRecord.cpp \
../src/Thread.cpp \
../src/kino.cpp \
../src/main.cpp \
../src/stdx.cpp 

OBJS += \
./src/Action.o \
./src/DBCursor.o \
./src/DataBase.o \
./src/DataContext.o \
./src/DbException.o \
./src/Dict.o \
./src/Exception.o \
./src/FCapts.o \
./src/Field.o \
./src/FrameThread.o \
./src/FrameWnd.o \
./src/OdbcCursor.o \
./src/OdbcDataBase.o \
./src/OdbcException.o \
./src/QField.o \
./src/QRestr.o \
./src/QTable.o \
./src/Query.o \
./src/RField.o \
./src/RKey.o \
./src/RLink.o \
./src/ROut.o \
./src/RSField.o \
./src/RSWhere.o \
./src/Record.o \
./src/RecordSet.o \
./src/Rib.o \
./src/SqlStmt.o \
./src/StMdfr.o \
./src/TabMap.o \
./src/Table.o \
./src/TempRecord.o \
./src/Thread.o \
./src/kino.o \
./src/main.o \
./src/stdx.o 

CPP_DEPS += \
./src/Action.d \
./src/DBCursor.d \
./src/DataBase.d \
./src/DataContext.d \
./src/DbException.d \
./src/Dict.d \
./src/Exception.d \
./src/FCapts.d \
./src/Field.d \
./src/FrameThread.d \
./src/FrameWnd.d \
./src/OdbcCursor.d \
./src/OdbcDataBase.d \
./src/OdbcException.d \
./src/QField.d \
./src/QRestr.d \
./src/QTable.d \
./src/Query.d \
./src/RField.d \
./src/RKey.d \
./src/RLink.d \
./src/ROut.d \
./src/RSField.d \
./src/RSWhere.d \
./src/Record.d \
./src/RecordSet.d \
./src/Rib.d \
./src/SqlStmt.d \
./src/StMdfr.d \
./src/TabMap.d \
./src/Table.d \
./src/TempRecord.d \
./src/Thread.d \
./src/kino.d \
./src/main.d \
./src/stdx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


