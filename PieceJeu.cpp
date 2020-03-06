/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo2_ASD
 Fichier     : PieceJeu.cpp
 Auteur(s)   : Marco Maziero
 Date        : 04.03.2020

 But         : <‡ completer>

 Remarque(s) : <‡ completer>

 Compilateur : MinGW-g++
 -----------------------------------------------------------------------------------
*/

#include "PieceJeu.h"
using namespace std;

const unsigned int PieceJeu::NO_PIECE_VIDE = 10;

PieceJeu::PieceJeu() {
    cotesPiece = {NONE, NONE, NONE, NONE};
    id = NO_PIECE_VIDE;
    orientation = 'a';
}

PieceJeu::PieceJeu(Piece cotes, unsigned int id, char orientation) : cotesPiece(cotes), id(id), orientation(orientation) {}

bool PieceJeu::comparerPiece(Direction direction, const PieceJeu &piece) {
    switch(direction) {
        case GAUCHE:
            return comparaisonsCotes(cotesPiece.at(3), piece.cotesPiece.at(1));
        case HAUT:
            return comparaisonsCotes(cotesPiece.at(0), piece.cotesPiece.at(2));
        default:
            return false;
    }
}

void PieceJeu::tournerPiece() {
    AttachementType temp = cotesPiece.at(0);
    for (int i = 1; i < 4; ++i) {
        cotesPiece.at(i - 1) = cotesPiece.at(i);
    }
    cotesPiece.at(3) = temp;

    // Met à jout la direction
    ++orientation;
    if (orientation == 'e') { orientation = 'a'; }
}

unsigned int PieceJeu::getId() const {
    return id;
}

vector<PieceJeu> PieceJeu::genererPile() {
    vector<PieceJeu> output;
    for (int i = 0; i < PIECES.size(); ++i) {
        PieceJeu nouvellePiece(PIECES.at(i), i);
        output.push_back(nouvellePiece);
    }
    return output;
}

array<array<PieceJeu, 3>, 3> PieceJeu::genererGrille() {
    PieceJeu p;
    array<array<PieceJeu, 3>, 3> output;
    return output;
}

char PieceJeu::getOrientation() const {
    return orientation;
}

bool PieceJeu::comparaisonsCotes(AttachementType c1, AttachementType c2) {
    return ((c1 == FILLE_HAUT && c2 == FILLE_BAS )          ||
            (c1 == GATEAU_GAUCHE && c2 == GATEAU_DROIT)     ||
            (c1 == ARROSOIR_GAUCHE && c2 == ARROSOIR_DROIT) ||
            (c1 == DAME_HAUT && c2 == DAME_BAS)             ||
            (c2 == FILLE_HAUT && c1 == FILLE_BAS)           ||
            (c2 == GATEAU_GAUCHE && c1 == GATEAU_DROIT)     ||
            (c2 == ARROSOIR_GAUCHE && c1 == ARROSOIR_DROIT) ||
            (c2 == DAME_HAUT && c1 == DAME_BAS));
}

