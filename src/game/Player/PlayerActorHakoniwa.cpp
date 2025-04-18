#include "Player/PlayerActorHakoniwa.h"
#include "Library/Nerve/NerveSetupUtil.h"
#include "Library/Nerve/NerveUtil.h"

namespace{
    NERVE_IMPL(PlayerActorHakoniwa, Jump);
    struct{
        NERVE_MAKE(PlayerActorHakoniwa, Jump);
    } NrvPlayerActorHakoniwa;
}