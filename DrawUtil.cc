#include <iostream>
#include "DrawUtil.h"

namespace sfml { namespace fs { namespace widget {

DrawUtil& DrawUtil::instance() {
    static DrawUtil s;
    return s;
}

void DrawUtil::init(sf::RenderWindow &window) {
    m_window = &window;

    if (!m_mainFont.loadFromFile("E:/tools/repos/gwidi_sfml/assets/arial.ttf")) {
        std::cerr << "Failed to load main font\n";
    }

    auto size = window.getSize();
    m_titleView.reset({0, 0, static_cast<float>(size.x), static_cast<float>(size.y * 0.05)});
    m_titleView.setViewport({0, 0, 1, 0.95f});

    m_contentView.reset({0, 0, static_cast<float>(size.x), static_cast<float>(size.y * 0.85)});
    m_contentView.setViewport({0, 0.05f, 1, 0.85f});

    m_controlsView.reset({0, 0, static_cast<float>(size.x), static_cast<float>(size.y * 0.10)});
    m_controlsView.setViewport({0, 0.90f, 1, 0.10f});

    m_titleBack.setFillColor(sf::Color::Red);
    m_titleBack.setSize(m_titleView.getSize());

    m_contentBack.setFillColor(sf::Color::Green);
    m_contentBack.setSize(m_contentView.getSize());

    m_controlsBack.setFillColor(sf::Color::Blue);
    m_controlsBack.setSize(m_controlsView.getSize());
}

void DrawUtil::draw() {
    if(!m_window) {
        return;
    }

    m_window->setView(m_titleView);
    m_window->draw(m_titleBack);

    m_window->setView(m_contentView);
    m_window->draw(m_contentBack);

    m_window->setView(m_controlsView);
    m_window->draw(m_controlsBack);
}

}}}
