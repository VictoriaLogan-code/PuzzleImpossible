#include <iostream>
#include <string>
#include "PieceJeu.h"
#include "pieces.h"
using namespace std;

void trouverSolutions(array<array<PieceJeu, 3>, 3>& grille, vector<PieceJeu> pile, int posX, int posY, string& listeSolutions);

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
                // La pièce n'est pas valide, on continue avec une autre orientation
                // Tourne la piece avant de recommencer la boucle
                pile.at(i).tournerPiece();
                continue;
            }
            if (posX != 0 && !(pile.at(i).comparerPiece(GAUCHE, grille.at(posY).at(posX - 1)))) {
                // La pièce n'est pas valide, on continue avec une autre orientation
                // Tourne la piece avant de recommencer la boucle
                pile.at(i).tournerPiece();
                continue;
            }

            // LE CODE SI DESSOUS EST EXECUTE SI LA PIECE EST VALIDE

            // Pièce valide, ajoute à la grille
            grille.at(posY).at(posX) = pile.at(i);

            // Pièce valide. Vérifie que l'on est à la fin de la grille (SUCCES)
            if (posX == 2 && posY == 2) {
                // REUSSITE => ECRITURE REPONSE
                // Affiche le résultat dans la console
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

            trouverSolutions(grille, prochainePile, prochX, prochY, listeSolutions);
            pile.at(i).tournerPiece();
        }
    }
    // Fin de fonction
}
