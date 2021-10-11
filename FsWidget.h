#ifndef GWIDI_SFML_FSWIDGET_H
#define GWIDI_SFML_FSWIDGET_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace sfml { namespace fs { namespace widget {

class FS_Widget {
public:
    static FS_Widget *create();

    void show();

private:
    std::vector<std::string> buildFileList();

};

}}}

#endif //GWIDI_SFML_FSWIDGET_H
