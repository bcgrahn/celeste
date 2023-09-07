#include "scale.h"
#include <tuple>

using namespace std;


Scale::Scale()
{
}

tuple<float,float> Scale::getScale(int name_){
    switch (name_){
        case P1:
            return make_tuple(3.65f,3.65f);
            break;
        case P2:
            return make_tuple(3.65f,3.65f);
            break;
        case HOMESCREENBACKGROUND:
            return make_tuple(4.05f,4.1f);
            break;
        case GAMEBACKGROUND:
            return make_tuple(4.05f,4.1f);
            break;
        case FLOE:
            return make_tuple(4.05f,4.1f);
            break;
        case BIRD:
            return make_tuple(4.05f,4.1f);
            break;
        case CRAB:
            return make_tuple(4.05f,4.1f);
            break;
        case FISH:
            return make_tuple(4.05f,4.1f);
            break;
        case CASTLE:
            return make_tuple(2.5f,2.5f);
            break;
        case SCORE:
            return make_tuple(4.05f,4.1f);
            break;
        case TEMPERATURE:
            return make_tuple(4.05f,4.1f);
            break;
        default:
            return make_tuple(4.05f,4.1f);
            break;
    }
}
