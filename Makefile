CXX = clang++

SRC = main.cpp \
			AbstractEntity.cpp \
			Character.cpp \
			ResourceManager.cpp \
			Monster.cpp \
			GameWorld.cpp \
			CollisionManager.cpp \
			Platform.cpp \
			Background.cpp \
			MapFactory.cpp  \
			SoundManager.cpp \
			PickMonster.cpp \
			TemporaryObject.cpp \
			IObservable.cpp \
			IObserver.cpp \
			WorldStateObs.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -W -Wall -Wextra -Wpedantic -g -std=c++14

LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

NAME = lbg

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(LIBS) $(CXXFLAGS) -o $(NAME) $(OBJ)

.PHONY: clean fclean re

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: clean all
