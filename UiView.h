#ifndef GWIDI_IMPORTER_UIVIEW_H
#define GWIDI_IMPORTER_UIVIEW_H

#include <SFML/Graphics.hpp>

namespace sfml { namespace fs { namespace widget {

class UiView {
public:
    UiView() = default;
    virtual void configure(sf::Vector2f size, sf::Vector2f position);

    virtual void onMouseWheelScrolled(sf::Mouse::Wheel wheel, float delta) {}
    virtual bool isMouseIn(int x, int y) { return false; }

    inline sf::FloatRect& bounds() {
        return m_bounds;
    }

    virtual void draw() {}
protected:
    sf::FloatRect m_bounds;
};

}}}


#endif //GWIDI_IMPORTER_UIVIEW_H
