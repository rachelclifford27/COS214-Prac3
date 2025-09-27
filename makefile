# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Project sources
SRCS = ChatAggregate.cpp \
       ChatIterator.cpp \
       ChatRoom.cpp \
       Command.cpp \
       CtrlCat.cpp \
       DemoMain.cpp \
       Dogorithm.cpp \
       LogMessageCommand.cpp \
       MessageIterator.cpp \
       NotificationObserver.cpp \
       NotificationSubject.cpp \
       SendMessageCommand.cpp \
       TestingMain.cpp \
       UserIterator.cpp \
       Users.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executables (choose which mains you want to build)
TARGETS = demo testing

# Default target
all: $(TARGETS)

# Build demo executable from DemoMain
demo: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Build testing executable from TestingMain
testing: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile cpp to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all clean