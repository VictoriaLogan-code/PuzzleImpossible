#include <iostream>
#include <string>
#include <chrono>
#include "pieces.h"
using namespace std;

/**********************************************************************************************
 * DECLARATION ET IMPLEMENTATION DE LA CLASSE PIECE JEU
 **********************************************************************************************/

/************************************** DECLARATION *******************************************/
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

/************************************ IMPLEMENTATION ******************************************/
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

void trouverSolutions(array<array<PieceJeu, 3>, 3>& grille, vector<PieceJeu> pile, int posX, int posY, string& listeSolutions);


/**********************************************************************************************
 * CONTENU DU MAIN
 **********************************************************************************************/
int main() {

    vector<PieceJeu> pileCartes         = PieceJeu::genererPile();
    array<array<PieceJeu, 3>, 3> grille = PieceJeu::genererGrille();
    string solutions;

    cout << "Toutes les solutions du Puzzle Impossible sont :" << endl;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    trouverSolutions(grille, pileCartes, 0, 0, solutions);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tps = t2 - t1;

    cout << solutions;
    cout << "Temps de recherche : " << tps.count() << "ms";
    return 0;
}

void trouverSolutions(array<array<PieceJeu, 3>, 3>& grille, vector<PieceJeu> pile, int posX, int posY, string& listeSolutions) {

    // Parcours toutes les pièces contenues dans la pile actuelle
    for (int i = 0; i < pile.size(); ++i) {

        // Parcours toutes les rotations de la piece possibles
        for (int j = 0; j < 4; ++j) {

            // Vérifie les cases en haut et a gauche de la pièce pour confirmer que la pièce est valide a cet endroit et cette orientation
            if (posY != 0 && !(pile.at(i).comparerPiece(HAUT, grille.at(posY - 1).at(posX)))) {
                // Pièce non valide, change l'orientation et recommence la boucle
                pile.at(i).tournerPiece();
                continue;
            }
            if (posX != 0 && !(pile.at(i).comparerPiece(GAUCHE, grille.at(posY).at(posX - 1)))) {
                // Pièce non valide, change l'orientation et recommence la boucle
                pile.at(i).tournerPiece();
                continue;
            }

            // LE CODE SI DESSOUS EST EXECUTE SI LA PIECE EST VALIDE

            // Pièce valide, ajoute à la grille
            grille.at(posY).at(posX) = pile.at(i);

            // Pièce valide. Vérifie que l'on est à la fin de la grille (SUCCES)
            if (posX == 2 && posY == 2) {
                // REUSSITE => ECRITURE REPONSE
                for (int k = 0; k < grille.size(); ++k) {
                    for (int l = 0; l < grille.size(); ++l) {
                        listeSolutions += to_string((grille.at(k).at(l).getId() + 1)) + grille.at(k).at(l).getOrientation() + " ";
                    }
                }
                listeSolutions += "\n";
                return;
            }

            // Pièce valide supprime la piece de la prochaine pile
            vector<PieceJeu> prochainePile = pile;
            prochainePile.erase(prochainePile.begin() + i);

            // Détermine les prochaines coordonées
            int prochX = posX + 1;
            int prochY = posY;
            if (prochX > 2) { prochX = 0; ++prochY; }

            // Appelle la fonction pour la prochaine case de la grille
            trouverSolutions(grille, prochainePile, prochX, prochY, listeSolutions);
            pile.at(i).tournerPiece();
        }
    }
    // Fin de fonction
}
