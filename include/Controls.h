#ifndef GWIDI_IMPORTER_CONTROLS_H
#define GWIDI_IMPORTER_CONTROLS_H

#include "HContainer.h"
#include "ButtonWidget.h"

namespace sfml { namespace fs { namespace widget {

class Controls {
public:
    Controls();


    void resize();
    bool delegateEvent(sf::RenderWindow& window, sf::Event &event, sf::View* view);
    void draw(sf::View* v, sf::RenderWindow &w);

    inline void setOkaySelectedListener(std::function<void()> listener) {
        m_okaySelected = listener;
    }
    inline void setCancelSelectedListener(std::function<void()> listener) {
        m_cancelSelected = listener;
    }

private:
    void init();

    // TODO: Make a button widget and use it here for the controls
    // TODO: Controls are:
    // TODO: - OK
    // TODO: - Cancel
    // TODO: - Up (back a directory in the path) (should this be in the title bar?)
    // TODO: Moving forward into directories will be done from the items list (double click item if directory -> move forward)

    // TODO: Create a base widget library for buttons instead of putting it in fs_widget
    // TODO: Delegate events directly from window's loop to the base widgets so that they can control things like focus / hover / etc

private:
    sfml::base::HContainer m_buttons;
    sfml::base::ButtonWidget* m_butOk;
    sfml::base::ButtonWidget* m_butCancel;

    std::function<void()> m_okaySelected;
    std::function<void()> m_cancelSelected;
};

}}}

#endif //GWIDI_IMPORTER_CONTROLS_H
