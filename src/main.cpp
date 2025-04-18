#include "System/GameSystem.h"
#include "logger/SDLogger.hpp"

#include <exlaunch.hpp>
#include <common.hpp>

//Includes for hooking
#include "Sequence/HakoniwaSequence.h"
#include "System/GameSystem.h"
#include "Library/Nerve/NerveUtil.h"
#include "Sequence/HakoniwaSequence.h"

#include "Player/PlayerActorHakoniwa.h"

#include "Player/PlayerInput.h"
#include "Library/Controller/InputFunction.h"

#define SDLOGGER 1

HakoniwaSequence *hakoniwaSequence = nullptr;
bool isLoaded = false;

HOOK_DEFINE_TRAMPOLINE(GameSystemInit){
    static void Callback(GameSystem *gameSystem){
        Orig(gameSystem);
        SDLogger::log("GameSystemInit fait !\n");
    }
};

HOOK_DEFINE_TRAMPOLINE(HakoniwaInit){
    static void Callback(HakoniwaSequence *hakoSequence, const al::SequenceInitInfo &info){
        SDLogger::log("HakoniwaSequence initialize !\n");
        hakoniwaSequence = hakoSequence;
        Orig(hakoniwaSequence, info);
        SDLogger::log("HakoniwaSequence initied !\n");
    }
};

// HOOK_DEFINE_TRAMPOLINE(bootLayoutAppear){
//     static void Callback(BootLayout *bootLayout){
//         SDLogger::log("bootLayoutAppear chargement !\n");
//         if(!isLoaded){
//             isLoaded = true;
//         }
//         Orig(bootLayout);
//         SDLogger::log("bootLayoutAppear terminé !\n");
//     }
// };




// HOOK_DEFINE_TRAMPOLINE(loadstage){
//     static void Callback(HakoniwaSequence *hakoSequence){
//         if(hakoSequence->mResourceLoader->isEndLoadWorldResource() && hakoSequence->mInitThread->isDone()){
//             SDLogger::log("Chargement terminé !\n");
//         }
//         Orig(hakoSequence);
//     }
// };


// HOOK_DEFINE_TRAMPOLINE(loadstage){
//     static void Callback(al::IUseNerve *nerve, HakoniwaSequence *hakoSequence){
//         if (al::isFirstStep(nerve)) {
//             SDLogger::log("loadstage chargement !\n");
//             WorldResourceLoader *Wr = hakoSequence->mResourceLoader;
//             Wr->requestLoadWorldHomeStageResource(0, 1);
//             // hakoSequence->mInitThread->start();
//             // const char* name = GameDataFunction::getNextStageName(hakoSequence->mGameDataHolderAccessor);
//             // if (name == nullptr)
//             //     name = GameDataFunction::getMainStageName(hakoSequence->mGameDataHolderAccessor, 0);
//             // int scenario = GameDataFunction::calcNextScenarioNo(hakoSequence->mGameDataHolderAccessor);
//             // if (scenario == -1)
//             //     scenario = 1;
//             // int world = hakoSequence->mGameDataHolderAccessor.mData->mWorldList->tryFindWorldIndexByStageName(name);
//             // if (world > -1) {
//             //     // Logger::log("Requesting %d-%d\n", world, scenario);
//             //     hakoSequence->mResourceLoader->requestLoadWorldHomeStageResource(world, scenario);
//             // }
//         }
//         Orig(nerve, hakoSequence);
//     }
// };


// HOOK_DEFINE_TRAMPOLINE(PlayerInputUpdate){
//     static void Callback(PlayerInput *playerInput){
//         Orig(playerInput);
//         SDLogger::log(al::isNerve(playerInput));
//         if(al::isPadTriggerY(-1)){
//             SDLogger::log("Y is pressed !\n");
//             //al::setNerve(playerInput, $NrvPlayerActorHakoniwa.Jump);
//         }
//     }
// };

extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking environment. */
    exl::hook::Initialize();
    GameSystemInit::InstallAtOffset(0x535850);

    HakoniwaInit::InstallAtSymbol("_ZN16HakoniwaSequence4initERKN2al16SequenceInitInfoE");

    // bootLayoutAppear::InstallAtSymbol("_ZN25HakoniwaStateBootLoadData7exeMenuEv");

    // loadstage::InstallAtSymbol("_ZN16HakoniwaSequence12exeLoadStageEv");

    // bootLoadData::InstallAtOffset(0x510C58);

    //PlayerInputUpdate::InstallAtSymbol("_ZN11PlayerInput6updateEv");
    
    if(SDLOGGER == 1){
        SDLogger::instance().init();
    }
}
