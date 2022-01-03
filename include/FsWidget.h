#ifndef GWIDI_SFML_FSWIDGET_H
#define GWIDI_SFML_FSWIDGET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>

namespace sfml { namespace fs { namespace widget {

class FS_Widget {
public:
    static FS_Widget *create();

    void show();

private:
    std::vector<std::string> pushDirToHistory(const std::string& dir);
    std::pair<std::string, std::vector<std::string>> popDirFromHistory();
    std::pair<std::string, std::vector<std::string>> moveDirUpInHistory();
    std::stack<std::string> m_dirHistory;

};

}}}

#endif //GWIDI_SFML_FSWIDGET_H
