#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "textdisplay.h"

using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  Colour cur;
  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      
      int n;
      cin >> n;
      // Add code here
      if (n < 4 || n % 2 != 0) continue;
      cur = Colour::Black;
      g.init(n);
      cout << g;
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      // Add code here
      
      if (g.setPiece(r, c, cur)) {
        cur = (cur == Colour::Black) ? Colour::White : Colour::Black;
        cout << g;
        if (g.isFull()) {
            Colour winner = g.whoWon();
            if (winner == Colour::NoColour) {
                cout << "Tie!" << endl;
            } else {
                cout  << ((winner == Colour::Black) ? "Black " : "White ") << "wins!" << endl;
            }
            return 0;
        }
      }
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
