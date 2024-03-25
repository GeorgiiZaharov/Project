all:
	g++ -Wall -Wextra *.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -D SFML_STATIC -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lX11 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfgui
test:
	./sfml-app
