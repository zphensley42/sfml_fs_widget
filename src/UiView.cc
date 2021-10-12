#include "UiView.h"

void sfml::fs::widget::UiView::configure(sf::Vector2f size, sf::Vector2f position) {
    m_bounds.left = position.x;
    m_bounds.top = position.y;

    m_bounds.width = size.x;
    m_bounds.height = size.y;
}

