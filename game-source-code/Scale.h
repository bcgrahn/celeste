#ifndef SCALE_H
#define SCALE_H

#include <tuple>

using namespace std;

class Scale
{
public:
    Scale();
    tuple <float, float> getScale(int name_);

private:
    enum name {P1, P2, HOMESCREENBACKGROUND, GAMEBACKGROUND, FLOE, BIRD, CRAB, FISH, CASTLE, SCORE, TEMPERATURE, DEFAULT};
};

#endif
