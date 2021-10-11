#include <iostream>
#include <SFML/Graphics.hpp>

#include "FsWidget.h"
#include "DrawUtil.h"

sf::RectangleShape popupBut{{50.f, 25.f}};
bool popupButHovered{false};
bool popupButDown{false};

void onButtonPress() {
    std::cout << "Button pressed!\n";
    auto fs = sfml::fs::widget::FS_Widget::create();
    fs->show();
}

void detectButtonHover(int x, int y) {
    popupButHovered = popupBut.getGlobalBounds().contains(x, y);
}
void detectButtonPress(int but, bool isDown) {
    if(but == 0) {
        if(popupButHovered && isDown) {
            popupButDown = true;
        }
        else if(popupButHovered && popupButDown && !isDown) {
            onButtonPress();
        }
    }

    if(!isDown) {
        popupButDown = false;
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Add a button to 'open' the file select widget
    popupBut.setPosition(0, 0);
    popupBut.setFillColor(sf::Color::Green);


    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                detectButtonPress(event.mouseButton.button, true);
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                detectButtonPress(event.mouseButton.button, false);
            }
            else if(event.type == sf::Event::MouseMoved) {
                detectButtonHover(event.mouseMove.x, event.mouseMove.y);
            }
            else if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window (show more instead of stretch views to the new 'size')
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
//                LayoutManager::instance().setup(window, handler);
                window.setView(sf::View(visibleArea));
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw our UI
        window.draw(popupBut);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

