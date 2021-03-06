//
//  LeBloqBoard.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 29/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "LeBloqBoard.h"

#define ORIENT_H    'h'
#define ORIENT_V    'v'

#define PIECE_1_B   3
#define PIECE_1_S   2

#define PIECE_2_B   4
#define PIECE_2_S   2

#define PIECE_3_B   4
#define PIECE_3_S   3

char LeBloqBoard::_figurePieceOrientation(Coordinate2D coord) {
    int type = _boardRepresentation[coord.y][coord.x];
    
    if (coord.x <= 6 && _boardRepresentation[coord.y][coord.x + 3] == type)             //  Width  = 4
        
        return ORIENT_H;
    
    else if (coord.x <= 7 && _boardRepresentation[coord.y][coord.x + 2] == type) {      //  Width  = 3
        
        if (coord.y <= 6 && _boardRepresentation[coord.y + 3][coord.x] == type)         //  Height = 4
            return ORIENT_V;
        else                                                            //  Height = 2
            return ORIENT_H;
        
    } else {                                                            //  Width  = 2
        
        if (coord.y <= 6 && _boardRepresentation[coord.y + 3][coord.x] == type)         //  Height = 4
            return ORIENT_V;
        else                                                            //  Height = 3
            return ORIENT_V;
        
    }
}

void LeBloqBoard::_removePieceFromBoard(std::vector<std::vector<int>> &board, Coordinate2D coord) {
    int pieceType = board[coord.y][coord.x];
    
    char orient = _figurePieceOrientation(coord);
    
    int width, height;
    
    switch (pieceType) {
            
        case 1:
            
            width  = (orient == ORIENT_H ? PIECE_1_B : PIECE_1_S);
            height = (orient == ORIENT_H ? PIECE_1_S : PIECE_1_B);
            
            break;
            
        case 2:
            
            width  = (orient == ORIENT_H ? PIECE_2_B : PIECE_2_S);
            height = (orient == ORIENT_H ? PIECE_2_S : PIECE_2_B);
            
            break;
            
        case 3:
            
            width  = (orient == ORIENT_H ? PIECE_3_B : PIECE_3_S);
            height = (orient == ORIENT_H ? PIECE_3_S : PIECE_3_B);
            
            break;
            
        default:
            
            throw new LeBloqUnknownPieceException("Unknown Piece Type!");
            
            break;
            
    }
    
    for (; height; height--, coord.y++) //  ¯\_(ツ)_/¯
        for (int i = coord.x; i < coord.x + width; i++)
            board[coord.y][i] = 0;
}

std::vector<LeBloqPiece> LeBloqBoard::getPieces() {
    std::vector<LeBloqPiece> pieces;
    
    std::vector< std::vector<int> > boardRep = _boardRepresentation;   //  Let's create a copy and mess with it.
    
    for (int i = 0; i < boardRep.size(); i++) {
        std::vector<int> line = boardRep[i];
        
        for (int j = 0; j < line.size(); j++, line = boardRep[i]) {
            int piece = line[j];
            
            if (piece > 0 && piece < 4) {
                
                //
                //  We're forcibly at the (0, 0) of the piece,
                //  let's just figure out its orientation and
                //  then remove it from the array.
                //
                
                Coordinate2D coord(j, i);
                
                char orientation = _figurePieceOrientation(coord);
                
                _removePieceFromBoard(boardRep, coord);
                
                pieces.push_back(LeBloqPiece(coord, piece, orientation));
            }
        }
    }
    
    return pieces;
}

std::vector<LeBloqTile> LeBloqBoard::getScoredTiles() {
    std::vector<LeBloqTile> tiles;
    
    for (int i = 0; i < _boardRepresentation.size(); i++) {
        std::vector<int> line = _boardRepresentation[i];
        
        for (int j = 0; j < line.size(); j++, line = _boardRepresentation[i]) {
            int tile = line[j];
            
            if (tile > 3)
                tiles.push_back(LeBloqTile(Coordinate2D(j, i), tile - 3));
        }
        
    }
    
    return tiles;
}

unsigned int LeBloqBoard::getScoringForPlayer(int player) {
    unsigned int score = 0;
    
    std::vector<LeBloqTile> scoredTiles = getScoredTiles();
    
    for (int i = 0; i < scoredTiles.size(); i++)
        if (scoredTiles[i].scoringPlayer == player)
            score++;
    
    return score;
}
