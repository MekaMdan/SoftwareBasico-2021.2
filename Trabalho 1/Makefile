CC = g++
CFLAGS = -Wall -g
RM = rm -rf

TARGET_MONT = montador
TARGET_COMP = compilador

all:$(TARGET_MONT) $(TARGET_COMP)

$(TARGET_MONT): $(TARGET_MONT).cpp 
	$(CC) $(CFLAGS) -o $(TARGET_MONT) $(TARGET_MONT).cpp
$(TARGET_COMP): $(TARGET_COMP).cpp
	$(CC) $(CFLAGS) -o $(TARGET_COMP) $(TARGET_COMP).cpp

