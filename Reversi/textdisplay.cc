#include "textdisplay.h"
#include "subject.h"

TextDisplay::TextDisplay(int n) :  gridSize(n) {
    theDisplay.resize(n, std::vector<char>(n, '-'));
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    auto info = whoNotified.getInfo();
    if (info.colour == Colour::Black) {
        theDisplay[info.row][info.col] = 'B';
    } else if (info.colour == Colour::White) {
        theDisplay[info.row][info.col] = 'W';
    } else {
        theDisplay[info.row][info.col] = '-';
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for ( auto row : td.theDisplay) {
        for (auto cell : row) {
            out << cell;
        }
        out << std::endl;
    }
    return out;
}
