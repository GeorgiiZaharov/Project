#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle with Image");

    // Загрузка текстуры изображения
    sf::Texture texture;
    if (!texture.loadFromFile("image.png"))
    {
        return 0;
    }
    // Определение центра экрана
    sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

    sf::Sprite image, buf;
    image.setTexture(texture);

    // Позиционирование и масштабирование картинки внутри круга
    sf::FloatRect imageBounds = image.getLocalBounds();

    image.setOrigin(imageBounds.width / 2, imageBounds.height / 2);
    image.setPosition(windowCenter);


    sf::RectangleShape border, rec;
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(-2.f);
    border.setOutlineColor(sf::Color::Red);
    border.setPosition(0.f,0.f);
    border.setSize(sf::Vector2f(100.f, 30.f));

    rec.setFillColor(sf::Color::Green);
    rec.setPosition(0,0);

    int health = 0;
    const int size = 100.f;
    const int max_health = 100;
    // Определение начального угла поворота
    float angle = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        // Получение позиции мыши в окне
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Расчет вектора направления от центра круга к позиции мыши
        sf::Vector2f direction = sf::Vector2f(mousePosition.x - windowCenter.x, mousePosition.y - windowCenter.y);

        // Расчет угла поворота круга
        angle = std::atan2(direction.y, direction.x);
        float rotation = angle * 180.f / 3.1415926535f;

        ++health;
        rec.setSize(sf::Vector2f((health / max_health) % size, 30.f));
        // rec.setSize(sf::Vector2f(100.f, 30.f));


        image.setRotation(rotation);

        window.clear();
        window.draw(image);
        window.draw(rec);
        window.draw(border);

        window.display();
    }

    return 0;
}
