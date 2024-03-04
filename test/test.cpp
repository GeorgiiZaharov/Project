#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Volume Slider");

    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf");

    sf::Text volumeText("Volume: 0", font, 24);
    volumeText.setPosition(350, 280);

    sf::RectangleShape volumeBar(sf::Vector2f(400, 20));
    volumeBar.setPosition(200, 300);
    volumeBar.setFillColor(sf::Color::Blue);

    sf::RectangleShape volumeSlider(sf::Vector2f(20, 40));
    volumeSlider.setPosition(200, 290);
    volumeSlider.setFillColor(sf::Color::White);

    sf::SoundBuffer shootSoundBuffer;
    if (!shootSoundBuffer.loadFromFile("shootSound.wav"))
    {
        return -1;
    }
    sf::Sound shootSound(shootSoundBuffer);

    sf::SoundBuffer rechargeSoundBuffer;
    if (!rechargeSoundBuffer.loadFromFile("rechargeSound.wav"))
    {
        return -1;
    }
    sf::Sound rechargeSound(rechargeSoundBuffer);

    int volume = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (mousePos.x >= 200 && mousePos.x <= 600)
                    {
                        volumeSlider.setPosition(mousePos.x - 10, 290);
                        volume = (mousePos.x - 200) / 4;
                        volumeText.setString("Volume: " + std::to_string(volume));
                        shootSound.setVolume(volume);
                        rechargeSound.setVolume(volume);
                    }
                }
            }
        }

        window.clear();
        window.draw(volumeBar);
        window.draw(volumeSlider);
        window.draw(volumeText);
        window.display();
    }

    return 0;
}
