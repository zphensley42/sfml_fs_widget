#ifndef GWIDI_IMPORTER_VERTICALTEXTLIST_H
#define GWIDI_IMPORTER_VERTICALTEXTLIST_H

#include "BaseWidget.h"
#include "ButtonWidget.h"

namespace sfml { namespace fs { namespace widget {

class VerticalTextList : public sfml::base::BaseWidget {
public:
    const int SCROLL_SPEED_MULT = 10;

    VerticalTextList();
    VerticalTextList(const std::vector<std::string> &items);

    virtual bool delegateEvent(sf::RenderWindow& window, sf::Event &event) override;
    virtual void draw(sf::View* v, sf::RenderWindow &w) override;

    virtual void setSize(sf::Vector2f size) override;
    virtual void setPosition(sf::Vector2f position) override;

    inline void setItemSelectListener(std::function<void(base::ButtonWidget*)> listener) {
        m_itemSelected = listener;
    }

private:
    // TODO: For efficiency, bake the text items to a render texture?
    // TODO: When baked, we would have to show an 'overlay' per the selected position of the text instead of changing the drawing of the text
    // TODO: This may be unnecessary optimization, but it is an option

    // TODO: Use views to limit the list to the 'view' while another 'view' fills the bottom for the buttons / controls
    // TODO: Method that calculates the max / min scroll based on the visible size of the view vs visible size of the content in the list

    void recalcScrollLimits();

    void init();

    sf::RectangleShape m_background;
    sf::Font m_itemFont;

    sf::Vector2f m_scroll{0, 0};
    std::pair<float, float> m_scrollLimits{0 ,0};

    std::function<void(base::ButtonWidget*)> m_itemSelected{nullptr};
};

}}}

#endif //GWIDI_IMPORTER_VERTICALTEXTLIST_H
