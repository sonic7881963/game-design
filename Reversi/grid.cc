#include "grid.h"
#include "textdisplay.h"

Grid::~Grid() {
  delete td;
  delete ob;
}

void Grid::setObserver(Observer<Info, State> *observer) {
  ob = observer;
}

bool Grid::isFull() const {
  for (const auto& row : theGrid) {
    for (const auto& cell : row) {
      if (cell.getInfo().colour == Colour::NoColour) {
        return false;
      }
    }
  }
  return true;
}

Colour Grid::whoWon() const {
  int blackCount = 0;
  int whiteCount = 0;

  for (const auto& row : theGrid) {
    for (const auto& cell : row) {
      if (cell.getInfo().colour == Colour::Black) {
        ++blackCount;
      } else if (cell.getInfo().colour == Colour::White) {
        ++whiteCount;
      }
    }
  }

  if (blackCount == whiteCount && isFull()) {
    return Colour::NoColour;
  } else if (blackCount == whiteCount) {
    return Colour::Black;
  }
  return (blackCount > whiteCount) ? Colour::Black : Colour::White;
}

void Grid::init(size_t n) {
  if (n < 4 || n % 2 != 0) {
    return;
  }
  
  int dimasion = n;
  theGrid.clear();
  td = new TextDisplay {dimasion};

  for (size_t i = 0; i < n; ++i) {
    std::vector<Cell> rowOfCells;
    for (size_t j = 0; j < n; ++j) {
      rowOfCells.emplace_back(i,j);
      td->notify(rowOfCells.back());
    }
    theGrid.emplace_back (rowOfCells);
  }


  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i > 0 && j > 0) theGrid[i][j].attach(&theGrid[i - 1][j - 1]);
      if (i > 0) theGrid[i][j].attach(&theGrid[i - 1][j]);
      if (i > 0 && j < n - 1) theGrid[i][j].attach(&theGrid[i - 1][j + 1]);
      if (i < n - 1) theGrid[i][j].attach(&theGrid[i + 1][j]);
      if (i < n - 1 && j > 0) theGrid[i][j].attach(&theGrid[i + 1][j - 1]);
      if (j > 0) theGrid[i][j].attach(&theGrid[i][j - 1]);
      if (j < n - 1) theGrid[i][j].attach(&theGrid[i][j + 1]);
      if (i < n - 1 && j < n - 1) theGrid[i][j].attach(&theGrid[i + 1][j + 1]);
      theGrid[i][j].attach(td);
    }
  }
  
  size_t mid = n / 2;

  setPiece(mid - 1, mid - 1, Colour::Black);
  setPiece(mid, mid, Colour::Black);
  setPiece(mid - 1, mid, Colour::White);
  setPiece(mid, mid - 1, Colour::White);
  
}

bool Grid::setPiece(size_t r, size_t c, Colour colour) {
  if (r >= theGrid.size() || c >= theGrid[0].size() || theGrid[r][c].getInfo().colour != Colour::NoColour) {
    return false;
  }
  theGrid[r][c].setPiece(colour);
  return true;
}

void Grid::toggle(size_t r, size_t c) {
  if (r >= theGrid.size() || c >= theGrid[0].size()) {
    return;
  }
  theGrid[r][c].toggle();
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
  out << *(g.td);
  return out;
}
