#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape( 100.f);
    sf::CircleShape shape2(100.f);
    shape.setPointCount(3);
    shape2.setPointCount(3);
    int cnt = 0;
        shape2.setOrigin(100.f, 100.f);
	    // shape2.rotate(static_cast<float>(cnt));
	    shape2.move(100.f, 100.f);

    shape.setFillColor(sf::Color::Green);
    shape2.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        cnt ++;
        cnt = cnt % 360;
	    shape2.rotate(static_cast<float>(cnt));

        window.clear();
        window.draw(shape);
        window.draw(shape2);
        window.display();
    }

    return 0;
}
