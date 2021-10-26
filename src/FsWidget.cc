#include <iostream>
#include "FsWidget.h"
#include "VerticalTextList.h"
#include "ButtonWidget.h"
#include "HContainer.h"
#include "DrawUtil.h"
#include <filesystem>
#include <string>

namespace sfml { namespace fs { namespace widget {

FS_Widget *FS_Widget::create() {
    return new FS_Widget();
}

std::vector<std::string> FS_Widget::buildFileList() {
    std::string path = "./";
    std::vector<std::string> ret;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        ret.emplace_back(entry.path().string());
    }
    return ret;
}

void initList(sf::RenderWindow &window, VerticalTextList& list) {
    list.setSize({static_cast<float>(window.getSize().x) - 10, DrawUtil::instance().contentView().getSize().y});
    list.setPosition({10, 0});
}

void initControlsGroup(sf::RenderWindow &window, sfml::base::HContainer& container) {
    container.setSize({DrawUtil::instance().controlsView().getSize().x, DrawUtil::instance().controlsView().getSize().y});
    container.setPosition({20, 0});
    container.setSpacing(20);
}

void FS_Widget::show() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "File Select");
    DrawUtil::instance().init(window);

    sf::Font mainFont;
    if (!mainFont.loadFromFile("E:/tools/repos/gwidi_sfml/assets/arial.ttf")) {
        std::cerr << "Failed to load main font\n";
    }
    sf::Text hello("Hello Popup!", mainFont);
    hello.setPosition({0, 0});

    auto files = buildFileList();
    for(auto &file : files) {
        std::cout << "File: " << file << std::endl;
    }
    VerticalTextList list(files);
    initList(window, list);
    list.setItemSelectListener([&](base::ButtonWidget* item) {
        std::cout << "item selected: " <<  item->getText() << std::endl;
        list.selectItem(item);
    });


    // Top controls
    // Up (up in directory structure)
    // Prev (previous directory)
    // Address bar? (not sure if needed yet, but a bar to directly type a directory)

    // Bottom controls
    // OK - close with selection
    // Cancel - close without selection
    float windowWidth = static_cast<float>(window.getSize().x);
    float butWidth = windowWidth * 0.25f;
    float x = (0.33f * windowWidth) - butWidth;
    auto* but_ok = new sfml::base::ButtonWidget();
    but_ok->setText("OK");
    but_ok->setTextAlign(sfml::base::ButtonWidget::TextAlign::ALIGN_CENTER);
    but_ok->setPosition({x, 0.f});
    but_ok->setSize({butWidth, 40});
    but_ok->setForegroundColors({
                                            sf::Color::White,
                                            sf::Color::White,
                                            sf::Color::White,
                                            sf::Color::White,
                                            sf::Color::White,
                                    });
    but_ok->setBackgroundColors({
                                            sf::Color::Black,
                                            sf::Color::Cyan,
                                            sf::Color::Blue,
                                            sf::Color::Red,
                                            sf::Color(100, 100, 100, 255),
                                    });

    x = (0.66f * windowWidth);
    auto* but_cancel = new sfml::base::ButtonWidget();
    but_cancel->setText("Cancel");
    but_cancel->setTextAlign(sfml::base::ButtonWidget::TextAlign::ALIGN_CENTER);
    but_cancel->setPosition({x, 0.f});
    but_cancel->setSize({butWidth, 40});
    but_cancel->setForegroundColors({
                                       sf::Color::White,
                                       sf::Color::White,
                                       sf::Color::White,
                                       sf::Color::White,
                                       sf::Color::White,
                               });
    but_cancel->setBackgroundColors({
                                       sf::Color::Black,
                                       sf::Color::Cyan,
                                       sf::Color::Blue,
                                       sf::Color::Red,
                                       sf::Color(100, 100, 100, 255),
                               });
    sfml::base::HContainer controlsContainer;
    controlsContainer.addChild(but_ok);
    controlsContainer.addChild(but_cancel);
    initControlsGroup(window, controlsContainer);

    bool firstDraw{true};
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window (show more instead of stretch views to the new 'size')
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                DrawUtil::instance().init(window);
                initList(window, list);
                initControlsGroup(window, controlsContainer);
            }
            // TODO: Else where we delegate to BaseWidget views (make list extend it?)
            else {
                if(DrawUtil::instance().mouseInContentView() && list.delegateEvent(window, event, &DrawUtil::instance().contentView())) {
                    continue;
                }
                else if(DrawUtil::instance().mouseInControlsView() && controlsContainer.delegateEvent(window, event, &DrawUtil::instance().controlsView())) {
                    continue;
                }
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw our UI
        // Layout
        DrawUtil::instance().draw();

        // Bottom controls
        controlsContainer.draw(&DrawUtil::instance().controlsView(), window);

        // Content
        list.draw(nullptr, window);

        if(firstDraw) {
            firstDraw = false;
            initControlsGroup(window, controlsContainer);
            // Re-layout after first draw so that we have real sizes of children (TODO: Make this logic flow better, i.e. without having to do an additional pass)
        }

        // Update the window
        window.display();
    }
}

}}}
