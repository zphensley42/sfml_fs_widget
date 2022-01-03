#include <iostream>
#include "Controls.h"
#include "DrawUtil.h"

namespace sfml { namespace fs { namespace widget {

TopControls::TopControls() {
    init();
}

void TopControls::init() {
    float windowWidth = static_cast<float>(DrawUtil::instance().window()->getSize().x);
    float butWidth = windowWidth * 0.25f;
    float x = (0.33f * windowWidth) - butWidth;


    m_butBack = new sfml::base::ButtonWidget();
    m_butUp = new sfml::base::ButtonWidget();
    m_textCurDir = new sfml::base::TextWidget();

    m_butBack->setText("Back", 12);
    m_butBack->setTextAlign(sfml::base::ButtonWidget::TextAlign::ALIGN_CENTER);
    m_butBack->setPosition({x, 5.f});
    m_butBack->setSize({butWidth, 30});
    m_butBack->setForegroundColors({
                                         sf::Color::White,
                                         sf::Color::White,
                                         sf::Color::White,
                                         sf::Color::White,
                                         sf::Color::White,
                                 });
    m_butBack->setBackgroundColors({
                                         sf::Color::Black,
                                         sf::Color::Cyan,
                                         sf::Color::Blue,
                                         sf::Color::Red,
                                         sf::Color(100, 100, 100, 255),
                                 });

    x = (0.66f * windowWidth);
    m_butUp->setText("Up", 12);
    m_butUp->setTextAlign(sfml::base::ButtonWidget::TextAlign::ALIGN_CENTER);
    m_butUp->setPosition({x, 5.f});
    m_butUp->setSize({butWidth, 30});
    m_butUp->setForegroundColors({
                                             sf::Color::White,
                                             sf::Color::White,
                                             sf::Color::White,
                                             sf::Color::White,
                                             sf::Color::White,
                                     });
    m_butUp->setBackgroundColors({
                                             sf::Color::Black,
                                             sf::Color::Cyan,
                                             sf::Color::Blue,
                                             sf::Color::Red,
                                             sf::Color(100, 100, 100, 255),
                                     });



    x += 35;
    m_textCurDir->setText("./", 14, sf::Color::White);
    m_textCurDir->setPosition({x, 5.f});
    m_textCurDir->setSize({butWidth, 30});


    m_buttons.addChild(m_butBack);
    m_buttons.addChild(m_butUp);
    m_buttons.addChild(m_textCurDir);
    resize();

    m_butBack->setClickedListener([this](){
        if(m_backSelected) {
            m_backSelected();
        }
    });
    m_butUp->setClickedListener([this](){
        if(m_upSelected) {
            m_upSelected();
        }
    });
}

void TopControls::updateSelectedDir(const std::string &dir) {
    m_textCurDir->setText(dir, 14, sf::Color::White);
}

void TopControls::resize() {
    m_buttons.setSize({DrawUtil::instance().controlsView().getSize().x, DrawUtil::instance().controlsView().getSize().y});
    m_buttons.setPosition({20, 0});
    m_buttons.setSpacing(20);
}

bool TopControls::delegateEvent(sf::RenderWindow &window, sf::Event &event, sf::View *view) {
    return m_buttons.delegateEvent(window, event, view);
}

void TopControls::draw(sf::View *v, sf::RenderWindow &w) {
    m_buttons.draw(v, w);
}





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
