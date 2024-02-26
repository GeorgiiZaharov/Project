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

    sf::Sprite image, buf;
    image.setTexture(texture);

    // Задание размеров круга
    // float circleRadius = 100.f;

    // Определение центра экрана
    sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

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
        // float rotation = angle;

        // // Позиционирование и поворот круга
        // sf::CircleShape circle(circleRadius);
        // circle.setFillColor(sf::Color::Transparent);
        // circle.setOutlineThickness(5.f);
        // circle.setOutlineColor(sf::Color::Red);
        // circle.setOrigin(circleRadius, circleRadius);
        // circle.setPosition(windowCenter);
        // circle.setRotation(rotation);
        // circle.move(circleRadius, circleRadius);

        // Позиционирование и масштабирование картинки внутри круга
        sf::FloatRect imageBounds = image.getLocalBounds();
        // float imageScale = (circleRadius * 2) / std::max(imageBounds.width, imageBounds.height);
        // image.setScale(imageScale, imageScale);
        image.setOrigin(imageBounds.width / 2, imageBounds.height / 2);
        image.setPosition(windowCenter);
        image.setRotation(rotation);

        window.clear();
        // window.draw(circle);
        window.draw(image);
        window.display();
    }

    return 0;
}
