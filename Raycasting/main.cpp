#include "Screen.h"

int main()
{
    Screen* screen = new Screen(800,600);
    Screen* helper = new Screen(800, 600);
    sf::RenderWindow* window = &screen->_window();
    sf::RenderWindow* help = &helper->_window();
    window->setFramerateLimit(60);
    while (window->isOpen() && help->isOpen())
    {
        sf::Event event;
        sf::Event b;
        while (window->pollEvent(event) && help->pollEvent(b))
        {
            if (event.type == sf::Event::Closed || b.type == sf::Event::Closed) {
                window->close();
                help->close();
            }
        }
        screen->update();
        helper->helpDispl();
        //window->clear();
        //window->display();
    }

    return 0;
}