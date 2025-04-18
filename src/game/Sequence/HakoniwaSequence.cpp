#include "Sequence/HakoniwaSequence.h"
#include "Library/Nerve/NerveSetupUtil.h"
#include "Library/Nerve/NerveUtil.h"

namespace{
    NERVE_IMPL(HakoniwaSequence, BootLoadData);
    struct{
        NERVE_MAKE(HakoniwaSequence, BootLoadData);
    } NrvHakoniwaSequence;
}
