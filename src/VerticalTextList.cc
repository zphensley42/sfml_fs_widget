#include "VerticalTextList.h"
#include "DrawUtil.h"
#include <iostream>

namespace sfml::fs::widget {

VerticalTextList::VerticalTextList() : sfml::base::BaseWidget() {}

VerticalTextList::VerticalTextList(const std::vector<std::string> &items) : sfml::base::BaseWidget() {
    for(auto& item : items) {
        auto child = new base::ButtonWidget();
        child->setText(item);
        child->setForegroundColors({
                                                   sf::Color::White,
                                                   sf::Color::White,
                                                   sf::Color::White,
                                                   sf::Color::White,
                                                   sf::Color::White,
                                           });
        child->setBackgroundColors({
                                                   sf::Color::Black,
                                                   sf::Color::Cyan,
                                                   sf::Color::Blue,
                                                   sf::Color::Red,
                                                   sf::Color(100, 100, 100, 255),
                                           });

        addChild(child);
    }
}

// TODO: Determine how to handle overlapping bounds? (i.e. children inside parents should take precedence?)
bool VerticalTextList::delegateEvent(sf::RenderWindow& window, sf::Event &event) {
    // Delegate to children first (for overlapping bounds)?
    for(auto& item : m_children) {
        if(item->delegateEvent(window, event)) {
            return true;
        }
    }

    // Need to handle move / mouse wheel
    if(event.type == sf::Event::EventType::MouseWheelScrolled) {
        if(globalBounds().contains(event.mouseWheelScroll.x, event.mouseWheelScroll.y)) {
            auto wheel = event.mouseWheelScroll.wheel;
            auto delta = event.mouseWheelScroll.delta;
            if(wheel == sf::Mouse::Wheel::VerticalWheel) {
                m_scroll.y -= (delta * SCROLL_SPEED_MULT);
                if(m_scroll.y < m_scrollLimits.first) {
                    m_scroll.y = m_scrollLimits.first;
                }

                if(m_scroll.y > m_scrollLimits.second) {
                    m_scroll.y = m_scrollLimits.second;
                }
            }
        }
    }

    return false;
}

void VerticalTextList::setPosition(sf::Vector2f position) {
    sfml::base::BaseWidget::setPosition(position);

    init();
}

void VerticalTextList::setSize(sf::Vector2f size) {
    sfml::base::BaseWidget::setSize(size);

    init();
}

void VerticalTextList::init() {
    // TODO: Size for y shall grow to fit the total # of items
    // TODO: It more just acts as a minimum size for the background?

    float yPos = m_bounds.top;
    for(auto& item : m_children) {
        auto but = static_cast<base::ButtonWidget*>(item);
        but->setSize({m_bounds.width, 50});
        but->setPosition({m_bounds.left, yPos});
        auto itemHeight = but->getHeight();
        yPos += itemHeight + 10;
    }
    m_bounds.height = yPos - m_bounds.top;

    m_background.setFillColor(sf::Color::Black);
    m_background.setSize({m_bounds.width, m_bounds.height});
    m_background.setPosition({m_bounds.left, m_bounds.top - m_scroll.y});

    recalcScrollLimits();
}

void VerticalTextList::recalcScrollLimits() {
    auto viewSize = DrawUtil::instance().contentView().getSize();
    auto contentSize = m_bounds.height + m_bounds.top;

    // Min should be 0 (i.e. we can't scroll beyond what we initially draw as)
    // Max is the amount that would allow us to see all of the content
    m_scrollLimits.first = 0;
    m_scrollLimits.second = contentSize - viewSize.y;
    if(m_scrollLimits.second < 0) {
        m_scrollLimits.second = 0;
    }

    std::cout << "Calculated scroll limits, min: " << m_scrollLimits.first << ", max: " << m_scrollLimits.second << std::endl;
}

void VerticalTextList::draw(sf::View* v, sf::RenderWindow &w) {
    DrawUtil::instance().window()->setView(DrawUtil::instance().contentView());

    m_background.setPosition({m_bounds.left, m_bounds.top - m_scroll.y});
    DrawUtil::instance().window()->draw(m_background);

    float yPos = m_bounds.top - m_scroll.y; // TODO: don't allocate per loop
    for(auto& item : m_children) {
        auto but = static_cast<base::ButtonWidget*>(item);
        but->setPosition({m_bounds.left, yPos});
        but->draw(&DrawUtil::instance().contentView(), *DrawUtil::instance().window());
        auto itemHeight = but->getHeight();
        yPos += itemHeight + 10;
    }
}

}
