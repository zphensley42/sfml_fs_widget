#include <iostream>
#include "FsWidget.h"
#include "VerticalTextList.h"
#include "ButtonWidget.h"
#include "HContainer.h"
#include "DrawUtil.h"
#include <filesystem>
#include <string>
#include "Controls.h"

namespace sfml { namespace fs { namespace widget {

FS_Widget *FS_Widget::create() {
    return new FS_Widget();
}

std::vector<std::string> FS_Widget::pushDirToHistory(const std::string& dir) {
    m_dirHistory.push(dir);
    std::vector<std::string> ret;
    for (const auto & entry : std::filesystem::directory_iterator(dir)) {
        ret.emplace_back(entry.path().string());
    }
    return ret;
}

std::pair<std::string, std::vector<std::string>> FS_Widget::popDirFromHistory() {
    std::string dir = m_dirHistory.top();
    std::vector<std::string> ret;
    for (const auto & entry : std::filesystem::directory_iterator(dir)) {
        ret.emplace_back(entry.path().string());
    }
    m_dirHistory.pop();
    return {m_dirHistory.top(), ret};
}

std::pair<std::string, std::vector<std::string>> FS_Widget::moveDirUpInHistory() {
    std::string dir = m_dirHistory.top();
    // If at the end already, just return what we have
    auto fpos = dir.find('/');
    if(fpos == std::string::npos) {
        std::vector<std::string> ret;
        for (const auto & entry : std::filesystem::directory_iterator(dir)) {
            ret.emplace_back(entry.path().string());
        }
        return {dir, ret};
    }
    else {
        // Move our dir string back and add to history
        dir = dir.substr(0, fpos);
        return {dir, pushDirToHistory(dir)};
    }
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

    auto files = pushDirToHistory("./");
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
    TopControls topControls;
    topControls.setBackSelectedListener([&, this](){
        auto newFiles = popDirFromHistory();
        list.setItems(newFiles.second);
        topControls.updateSelectedDir(newFiles.first);
        // TODO: Clear old selections?
    });
    topControls.setUpSelectedListener([&, this](){
        auto newFiles = moveDirUpInHistory();
        list.setItems(newFiles.second);
        topControls.updateSelectedDir(newFiles.first);
        // TODO: Clear old selections?
    });

    // Bottom controls
    // OK - close with selection
    // Cancel - close without selection
    Controls bottomControls;
    bottomControls.setOkaySelectedListener([&list, &window](){
        auto selectedItem = list.selectedItem();
        if(selectedItem) {
            auto asButton = static_cast<base::ButtonWidget*>(selectedItem);
            std::cout << "OK clicked, TODO: Close the dialog, selected item: " << asButton->getText() << std::endl;
        }
        else {
            std::cout << "OK clicked, TODO: Close the dialog, NO selected item" << std::endl;
        }

        window.close();
    });
    bottomControls.setCancelSelectedListener([&window](){
        std::cout << "Cancel clicked, TODO: Close the dialog" << std::endl;
        window.close();
    });

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
                bottomControls.resize();
            }
            // TODO: Else where we delegate to BaseWidget views (make list extend it?)
            else {
                if(DrawUtil::instance().mouseInContentView() && list.delegateEvent(window, event, &DrawUtil::instance().contentView())) {
                    continue;
                }
                else if(DrawUtil::instance().mouseInTitleView() && topControls.delegateEvent(window, event, &DrawUtil::instance().titleView())) {
                    continue;
                }
                else if(DrawUtil::instance().mouseInControlsView() && bottomControls.delegateEvent(window, event, &DrawUtil::instance().controlsView())) {
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
        topControls.draw(&DrawUtil::instance().titleView(), window);
        bottomControls.draw(&DrawUtil::instance().controlsView(), window);

        // Content
        list.draw(nullptr, window);

        if(firstDraw) {
            firstDraw = false;
            topControls.resize();
            bottomControls.resize();
            // Re-layout after first draw so that we have real sizes of children (TODO: Make this logic flow better, i.e. without having to do an additional pass)
        }

        // Update the window
        window.display();
    }
}

}}}
