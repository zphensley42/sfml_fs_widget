#include <iostream>
#include "Controls.h"
#include "DrawUtil.h"

namespace sfml { namespace fs { namespace widget {

Controls::Controls() {
    init();
}

void Controls::init() {
    float windowWidth = static_cast<float>(DrawUtil::instance().window()->getSize().x);
    float butWidth = windowWidth * 0.25f;
    float x = (0.33f * windowWidth) - butWidth;


    m_butOk = new sfml::base::ButtonWidget();
    m_butCancel = new sfml::base::ButtonWidget();

    m_butOk->setText("OK");
    m_butOk->setTextAlign(sfml::base::ButtonWidget::TextAlign::ALIGN_CENTER);
    m_butOk->setPosition({x, 0.f});
    m_butOk->setSize({butWidth, 40});
    m_butOk->setForegroundColors({
                                        sf::Color::White,
                                        sf::Color::White,
                                        sf::Color::White,
                                        sf::Color::White,
                                        sf::Color::White,
                                });
    m_butOk->setBackgroundColors({
                                        sf::Color::Black,
                                        sf::Color::Cyan,
                                        sf::Color::Blue,
                                        sf::Color::Red,
                                        sf::Color(100, 100, 100, 255),
                                });

    x = (0.66f * windowWidth);
    m_butCancel->setText("Cancel");
    m_butCancel->setTextAlign(sfml::base::ButtonWidget::TextAlign::ALIGN_CENTER);
    m_butCancel->setPosition({x, 0.f});
    m_butCancel->setSize({butWidth, 40});
    m_butCancel->setForegroundColors({
                                            sf::Color::White,
                                            sf::Color::White,
                                            sf::Color::White,
                                            sf::Color::White,
                                            sf::Color::White,
                                    });
    m_butCancel->setBackgroundColors({
                                            sf::Color::Black,
                                            sf::Color::Cyan,
                                            sf::Color::Blue,
                                            sf::Color::Red,
                                            sf::Color(100, 100, 100, 255),
                                    });
    m_buttons.addChild(m_butOk);
    m_buttons.addChild(m_butCancel);
    resize();

    m_butOk->setClickedListener([this](){
        if(m_okaySelected) {
            m_okaySelected();
        }
    });
    m_butCancel->setClickedListener([this](){
        if(m_cancelSelected) {
            m_cancelSelected();
        }
    });
}

void Controls::resize() {
    m_buttons.setSize({DrawUtil::instance().controlsView().getSize().x, DrawUtil::instance().controlsView().getSize().y});
    m_buttons.setPosition({20, 0});
    m_buttons.setSpacing(20);
}

bool Controls::delegateEvent(sf::RenderWindow &window, sf::Event &event, sf::View *view) {
    return m_buttons.delegateEvent(window, event, view);
}

void Controls::draw(sf::View *v, sf::RenderWindow &w) {
    m_buttons.draw(v, w);
}

}}}
