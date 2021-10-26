#ifndef GWIDI_IMPORTER_DRAWUTIL_H
#define GWIDI_IMPORTER_DRAWUTIL_H

#include <SFML/Graphics.hpp>

namespace sfml { namespace fs { namespace widget {

class DrawUtil {
public:
    DrawUtil() = default;
    ~DrawUtil() = default;
    static DrawUtil& instance();

    void init(sf::RenderWindow& window);

    inline sf::RenderWindow* window() {
        return m_window;
    }

    inline sf::Font& font() {
        return m_mainFont;
    }

    inline sf::View& titleView() {
        return m_titleView;
    }

    inline sf::View& contentView() {
        return m_contentView;
    }

    inline sf::View& controlsView() {
        return m_controlsView;
    }

    bool mouseInTitleView();
    bool mouseInContentView();
    bool mouseInControlsView();

    void draw();
private:
    sf::RenderWindow* m_window{nullptr};
    sf::Font m_mainFont;

    sf::View m_titleView;
    sf::View m_contentView;
    sf::View m_controlsView;

    sf::RectangleShape m_titleBack;
    sf::RectangleShape m_contentBack;
    sf::RectangleShape m_controlsBack;


    sf::FloatRect m_titleViewBounds;
    sf::FloatRect m_contentViewBounds;
    sf::FloatRect m_controlsViewBounds;
};

}}}

#endif //GWIDI_IMPORTER_DRAWUTIL_H
