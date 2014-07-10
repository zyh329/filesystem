#*****************************************************************************
# Copyright	:  
# Author	:   
# Date		:   2012-10-29
# Version	:   
# Description	:   Demo
#****************************************************************************/
MODULE = FileSystem

SHELL = /bin/sh 

OS_ARC := x64
IS_X64 := $(shell uname -a|grep -o 'x86_64')
ifdef IS_X64
	OS_ARC=x64
else
	OS_ARC=x86
endif

OS_VER := $(shell cat /etc/issue)
OS_VER := $(shell echo $(OS_VER)| grep -o '[0-9]\{1,3\}\.[0-9]\{1,3\}')
$(warning ${OS_VER})

# directory
DIR_SRC = ./
DIR_BIN = ./bin/${OS_VER}/${OS_ARC}/
DIR_LIB = ../lib/${OS_VER}/${OS_ARC}/
DIR_OBJ	= ../obj/$(MODULE)/

# create temporary directory
$(shell mkdir -p ${DIR_BIN}) 
$(shell mkdir -p ${DIR_OBJ}) 

#****************************************************************************

CC = g++ -fshort-wchar -O3 -DNDEBUG
#CC = g++ 

##SHARED = -L. -lSDKFirmwareCrypt -luuid -o
SHARED = -L. -lSDKFirmwareCrypt -luuid -shared -o

FPIC = -fPIC -c

OBJECT_C = $(DIR_SRC)*.cpp
OBJECT_H = $(DIR_SRC)*.h

OBJECT = *.o
##TARGET = testFS
TARGET = $(DIR_BIN)lib${MODULE}.so

#****************************************************************************

$(TARGET):$(OBJECT)
	$(CC) $(OBJECT) $(SHARED) $(TARGET) 
	mv $(OBJECT) $(DIR_OBJ)
	cp $(DIR_BIN)lib${MODULE}.so ../Output/

$(OBJECT):$(OBJECT_C) $(OBJECT_H)
	$(CC) $(FPIC) $(OBJECT_C) 

clean:
	rm -f  $(TARGET)
	rm -fr $(DIR_OBJ)
	rm -f ../Output/lib${MODULE}.so
