//
//  Globals.hpp - Contains declarations of global variables
//  Pong
//
//  Created by John Geiger on 6/26/22.
//
#pragma once

#ifndef Globals_hpp
#define Globals_hpp

#include "Audio.hpp"
#include "TortiApp.hpp"

namespace Torti {
using AudioSystemPtr = std::shared_ptr<AudioSystem>;

extern TortiGameApp *g_pApp;
extern AudioSystemPtr g_pAudio;

}

#endif /* Globals_hpp */
