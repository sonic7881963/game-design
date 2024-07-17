#include "cell.h"

Cell::Cell(size_t r, size_t c) : r{r}, c{c}{}

void Cell::setPiece(Colour colour) {
  this->colour = colour;
  setState(State{StateType::NewPiece, colour, Direction::N});
  notifyObservers();
}


void Cell::toggle() {
    colour = (colour == Colour::Black) ? Colour::White : Colour::Black;


}

void Cell::notify(Subject<Info, State> &whoFrom) {
  State myState = getState();
  State fromState = whoFrom.getState();
  Info fromInfo = whoFrom.getInfo();
  Direction fromDirection = getDirection(fromInfo.row, fromInfo.col, r, c);

  if (fromState.type == StateType::NewPiece) {
    if (colour != Colour::NoColour && colour != fromState.colour) {
      setState({StateType::Relay, fromState.colour, fromDirection});
      notifyObservers();
    }
  } else if (fromState.type == StateType::Relay) {
    if (fromDirection == fromState.direction) {
      if (colour != Colour::NoColour && colour != fromState.colour) {
        setState({StateType::Relay, fromState.colour, fromDirection});
        notifyObservers();
      } else if (colour == fromState.colour) {
        setState({StateType::Reply, fromState.colour, oppositeDirection(fromDirection)});
        notifyObservers();
      }
    }
  } else if (fromState.type == StateType::Reply) {
    if (fromDirection == fromState.direction && myState.type == StateType::Relay) {
      toggle();
      setState({StateType::Reply, fromState.colour, fromDirection});
      notifyObservers();
    }
  }
}


Direction Cell::getDirection(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = fromRow - toRow;
    int colDiff = fromCol - toCol;

    if (rowDiff == -1 && colDiff == -1) {
        return Direction::NW;
    } else if (rowDiff == -1 && colDiff == 0) {
        return Direction::N;
    } else if (rowDiff == -1 && colDiff == 1) {
        return Direction::NE;
    } else if (rowDiff == 0 && colDiff == -1) {
        return Direction::W;
    } else if (rowDiff == 0 && colDiff == 1) {
        return Direction::E;
    } else if (rowDiff == 1 && colDiff == -1) {
        return Direction::SW;
    } else if (rowDiff == 1 && colDiff == 0) {
        return Direction::S;
    } else if (rowDiff == 1 && colDiff == 1) {
        return Direction::SE;
    }

    return Direction::N;
}

Direction Cell::oppositeDirection(Direction dir) {
    switch (dir) {
        case Direction::NW:
            return Direction::SE;
        case Direction::N:
            return Direction::S;
        case Direction::NE:
            return Direction::SW;
        case Direction::W:
            return Direction::E;
        case Direction::E:
            return Direction::W;
        case Direction::SW:
            return Direction::NE;
        case Direction::S:
            return Direction::N;
        case Direction::SE:
            return Direction::NW;
        default:
            return Direction::N;
    }
}

Info Cell::getInfo() const {
    return {r, c, colour};
}
