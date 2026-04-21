//
// Created by Bernie Joyce on 21/04/2026.
//

#include "Bug.h"

bool Bug::isWayBlocked() {
        {
                if (position.first==0 && direction_==west) {
                        return true;
                }
                if (position.first==9 && direction_==east){
                        return true;
                }
                if (position.second==0 && direction_==south) {
                        return true;
                }
                if (position.second==9 && direction_==north) {
                        return true;
                }
                return false;
        }
}
