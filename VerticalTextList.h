#ifndef GWIDI_IMPORTER_VERTICALTEXTLIST_H
#define GWIDI_IMPORTER_VERTICALTEXTLIST_H

#include "UiView.h"

namespace sfml { namespace fs { namespace widget {

class VerticalTextList : public UiView {
public:
    const int SCROLL_SPEED_MULT = 10;

    VerticalTextList();
    VerticalTextList(const std::vector<std::string> &items);

    void configure(sf::Vector2f size, sf::Vector2f position) override;

    virtual void onMouseWheelScrolled(sf::Mouse::Wheel wheel, float delta) override;
    virtual bool isMouseIn(int x, int y) override;

    void draw() override;
private:
    // TODO: For efficiency, bake the text items to a render texture?
    // TODO: When baked, we would have to show an 'overlay' per the selected position of the text instead of changing the drawing of the text
    // TODO: This may be unnecessary optimization, but it is an option

    // TODO: Use views to limit the list to the 'view' while another 'view' fills the bottom for the buttons / controls
    // TODO: Method that calculates the max / min scroll based on the visible size of the view vs visible size of the content in the list

    void recalcScrollLimits();

    void init();

    sf::RectangleShape m_background;
    std::vector<sf::Text> m_items;
    sf::Font m_itemFont;

    sf::Vector2f m_scroll{0, 0};
    std::pair<float, float> m_scrollLimits{0 ,0};
};

}}}

#endif //GWIDI_IMPORTER_VERTICALTEXTLIST_H
