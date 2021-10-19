#include <iostream>
#include "FsWidget.h"
#include "VerticalTextList.h"
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
    list.setItemSelectListener([](base::ButtonWidget* item) {
        std::cout << "item selected: " <<  item->getText() << std::endl;
    });

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
            }
            // TODO: Else where we delegate to BaseWidget views (make list extend it?)
            else {
//                if(!base::FocusManager::instance().delegateEventToNecessaryWidgets(event)) {
                    if(list.delegateEvent(window, event)) {
                        // Skip future delegates as necessary
                        continue;
//                    }
                }
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw our UI
        DrawUtil::instance().draw();
        list.draw(nullptr, window);

        // Update the window
        window.display();
    }
}

}}}
