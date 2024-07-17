
#ifndef DIRECTION_H
#define DIRECTION_H
enum class Direction { N, NE, E, SE, S, SW, W, NW };

 std::string dtoa(Direction direction);

 Direction atod(std::string str);
 Direction itod(int no);
#endif
