#include "VerticalTextList.h"
#include "DrawUtil.h"
#include <iostream>

namespace sfml { namespace fs { namespace widget {


VerticalTextList::VerticalTextList() : UiView() {}

VerticalTextList::VerticalTextList(const std::vector<std::string> &items) : UiView() {
    for(auto& item : items) {
        m_items.emplace_back();
        m_items.back().setString(item);
        m_items.back().setFont(DrawUtil::instance().font());
        m_items.back().setFillColor(sf::Color::White);
    }
}

bool VerticalTextList::isMouseIn(int x, int y) {
    return m_background.getGlobalBounds().contains(x, y);
}

void VerticalTextList::onMouseWheelScrolled(sf::Mouse::Wheel wheel, float delta) {
    // Update our scrolling
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

void VerticalTextList::configure(sf::Vector2f size, sf::Vector2f position) {
    UiView::configure(size, position);

    init();
}

void VerticalTextList::init() {
    // TODO: Size for y shall grow to fit the total # of items
    // TODO: It more just acts as a minimum size for the background?

    float yPos = m_bounds.top;
    for(auto& item: m_items) {
        item.setPosition({m_bounds.left, yPos});
        auto lb = item.getLocalBounds();
        yPos += lb.height + 10;
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

void VerticalTextList::draw() {
    DrawUtil::instance().window()->setView(DrawUtil::instance().contentView());

    m_background.setPosition({m_bounds.left, m_bounds.top - m_scroll.y});
    DrawUtil::instance().window()->draw(m_background);

    float yPos = m_bounds.top - m_scroll.y; // TODO: don't allocate per loop
    for(auto& item: m_items) {
        item.setPosition({m_bounds.left, yPos});
        DrawUtil::instance().window()->draw(item);
        auto lb = item.getLocalBounds();
        yPos += lb.height + 10;
    }
}


}}}