#ifndef GWIDI_IMPORTER_CONTROLS_H
#define GWIDI_IMPORTER_CONTROLS_H

#include "UiView.h"

namespace sfml { namespace fs { namespace widget {

class Controls {
public:
    Controls();

private:
    void init();

    // TODO: Make a button widget and use it here for the controls
    // TODO: Controls are:
    // TODO: - OK
    // TODO: - Cancel
    // TODO: - Up (back a directory in the path) (should this be in the title bar?)
    // TODO: Moving forward into directories will be done from the items list (double click item if directory -> move forward)
};

}}}

#endif //GWIDI_IMPORTER_CONTROLS_H
