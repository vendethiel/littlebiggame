CXX ?= clang++

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

CXXFLAGS = -D SFML_STATIC -W -Wall -Wextra -Wpedantic -g -std=c++23

LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

NAME = lbg

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LIBS)

.PHONY: clean fclean re

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: clean all
