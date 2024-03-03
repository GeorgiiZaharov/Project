#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Animation {
public:
    Animation(sf::Texture& texture, sf::IntRect idleRect, sf::IntRect fireRect, float duration) :
        time_start(0.f),
        anim_duration(duration),
        tex(texture),
        change_to_fire_anim(false)
    {
        rec.setTexture(tex);
        idle = idleRect;
        fire = fireRect;
    }

    void change_anim(float cur_time) {
        float elapsed_time = cur_time - time_start;
        bool should_change_to_fire_anim = change_to_fire_anim && elapsed_time < anim_duration;
        
        if (should_change_to_fire_anim != animating) {
            animating = should_change_to_fire_anim;
            time_start = cur_time;
        }
        
        if (animating) {
            rec.setTextureRect(fire);
        }
        else {
            rec.setTextureRect(idle);
        }
    }

    // Другие методы класса...

private:
    float time_start;
    sf::IntRect idle;
    sf::IntRect fire;
    float anim_duration;
    sf::Texture tex;
    sf::Sprite rec;
    bool change_to_fire_anim;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Animation");
    window.setFramerateLimit(60);

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("enemy.png")) {
        return -1;
    }

    sf::IntRect idleRect(0, 0, 64, 64);
    sf::IntRect fireRect(64, 0, 64, 64);

    Animation enemyAnim(enemyTexture, idleRect, fireRect, 200.f);

    sf::Clock clock;
    clock.restart();

    bool shooting = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                shooting = true;
                enemyAnim.change_to_fire_anim = true;
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                shooting = false;
                enemyAnim.change_to_fire_anim = false;
            }
        }

        float cur_time = clock.getElapsedTime().asMilliseconds();
        enemyAnim.change_anim(cur_time);

        window.clear();
        window.draw(enemyAnim.rec);
        window.display();
    }

    return 0;
}
