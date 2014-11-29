//
//  LeBloqState.h
//  Project 1
//
//  Created by Eduardo Almeida on 29/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__LeBloqState__
#define __Project_1__LeBloqState__

#include "LeBloqBoard.h"

class LeBloqState {
    
    LeBloqBoard _board;
    
    int _player;
    
    bool _playing;
    
public:
    
    LeBloqState(LeBloqBoard b, int p, bool r) {
        _board = b;
        _player = p;
        _playing = r;
    }
    
    LeBloqBoard getBoard() {
        return _board;
    }
    
    int getPlayer() {
        return _player;
    }
    
    bool getPlaying() {
        return _playing;
    }
    
};

#endif /* defined(__Project_1__LeBloqState__) */