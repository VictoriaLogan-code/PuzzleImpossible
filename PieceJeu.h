/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo2_ASD
 Fichier     : PieceJeu.h
 Auteur(s)   : Marco Maziero
 Date        : 04.03.2020

 But         : <‡ completer>

 Remarque(s) : <‡ completer>

 Compilateur : MinGW-g++
 -----------------------------------------------------------------------------------
*/

#ifndef LABO2_ASD_PIECEJEU_H
#define LABO2_ASD_PIECEJEU_H
#include "pieces.h"

class PieceJeu {
public:
    static std::vector<PieceJeu> genererPile();
    static std::array<std::array<PieceJeu, 3>, 3> genererGrille();
    static bool comparaisonsCotes(AttachementType c1, AttachementType c2);

    PieceJeu();
    PieceJeu(Piece cotes, unsigned int id, char orientation = 'a');

    unsigned int getId() const;
    char getOrientation() const;
    void tournerPiece();
    bool comparerPiece(Direction direction, const PieceJeu& piece);

private:
    static const unsigned int NO_PIECE_VIDE;
    Piece cotesPiece;
    char orientation;
    unsigned int id;
};
#endif //LABO2_ASD_PIECEJEU_H
