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
    m_titleView.setViewport({0, 0, 1, 0.05f});

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




    m_titleViewBounds.left = 0;
    m_titleViewBounds.top = 0;
    m_titleViewBounds.height = 0.05f * m_window->getSize().y;
    m_titleViewBounds.width = 1.f * m_window->getSize().x;

    m_contentViewBounds.left = 0;
    m_contentViewBounds.top = 0.05f * m_window->getSize().y;
    m_contentViewBounds.height = 0.85f * m_window->getSize().y;
    m_contentViewBounds.width = 1.f * m_window->getSize().x;

    m_controlsViewBounds.left = 0;
    m_controlsViewBounds.top = 0.90f * m_window->getSize().y;
    m_controlsViewBounds.height = 0.10f * m_window->getSize().y;
    m_controlsViewBounds.width = 1.f * m_window->getSize().x;
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

bool DrawUtil::mouseInTitleView() {
    auto p = sf::Mouse::getPosition(*m_window);
    return m_titleViewBounds.contains({static_cast<float>(p.x), static_cast<float>(p.y)});
}

bool DrawUtil::mouseInContentView() {
    auto p = sf::Mouse::getPosition(*m_window);
    return m_contentViewBounds.contains({static_cast<float>(p.x), static_cast<float>(p.y)});
}

bool DrawUtil::mouseInControlsView() {
    auto p = sf::Mouse::getPosition(*m_window);
    return m_controlsViewBounds.contains({static_cast<float>(p.x), static_cast<float>(p.y)});
}

}}}
