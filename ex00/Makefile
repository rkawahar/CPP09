CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
DEBUG = -g -fsanitize=address
SRCS = main.cpp BitcoinExchange.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = btc
TARGET1 = debug

all: $(TARGET)

debug: $(TARGET1)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o  $@ $^

$(TARGET1): $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o  $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@rm -f *.o *.d

fclean:
	@rm -f *.o *.d
	@rm -f $(TARGET) $(TARGET1)

maclean:
	@make all
	@make clean

re:
	@rm -f *.o *.d
	@rm -f $(TARGET) $(TARGET1)
	@make all

.PHONY: all clean fclean re
