//
//  LeBloq.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#include "LeBloq.h"

#include "PrologParser.h"

std::vector<LeBloqPiece> LeBloqBoard::getPieces() {
    std::vector<LeBloqPiece> pieces;
    
    for (
    
    return std::vector<LeBloqPiece>();
}

LeBloqState LeBloq::_parseOK(std::string answer) {
    answer.erase(0, 3);
    
    answer.pop_back();
    
    auto boardRep = PrologParser::prologToBoardRepresentation(answer, _boardSizeX);
    
    auto board = LeBloqBoard(boardRep);
    
    auto state = LeBloqState(board, 1, true);
    
    _gameStates.push(state);
    
    return state;
}

LeBloqState LeBloq::newGame(int x, int y) {
    _conn->write("initialize(" + std::to_string(x) + "," + std::to_string(y) + ").");
    
    auto answer = _conn->read();
    
    if (answer.find("fail") != std::string::npos || answer.find("ok(") == std::string::npos)
        throw new LeBloqBoardCreationException("Unable to create board.");
    
    _boardSizeX = x;
    _boardSizeY = y;
    
    auto state = _parseOK(answer);
    
    return state;
}

LeBloqState LeBloq::getCurrentGameState() {
    return _gameStates.top();
}

LeBloqState LeBloq::performPlay(int pieceType, char pieceOrientation, Coordinate2D piecePos) {
    std::string message = (_gameStates.size() == 1 ? "playFT(" : "play(") + PrologParser::boardRepresentationToProlog(getCurrentGameState().getBoard().getBoardRepresentation()) + "," + std::to_string(pieceType) + "," + pieceOrientation + "," + std::to_string((int) piecePos.x) + "," + std::to_string((int) piecePos.y) + "," + std::to_string(getCurrentGameState().getPlayer()) + "," + std::to_string(_boardSizeX) + "," + std::to_string(_boardSizeY) + ").";
    
    _conn->write(message);
    
    auto answer = _conn->read();
    
    if (answer.find("fail") != std::string::npos || answer.find("ok(") == std::string::npos)
        throw new LeBloqBoardPlayException("Unable to create board.");
    
    _conn->write(message);
    
    auto state = _parseOK(answer);
    
    return state;
}
