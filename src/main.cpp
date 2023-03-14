#include <SFML/Graphics.hpp>
#include <settings.hpp>

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(settings::DIMENSIONS.first, settings::DIMENSIONS.second), "Hello From SFML");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Magenta);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.display();

    }

    return 0;
}
