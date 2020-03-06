//
//  pieces.cpp
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#include "pieces.h"
#include <string>
using namespace std;

//                  HAUT                    DROITE                      BAS                     GAUCHE
const Pieces PIECES = {
        { DAME_HAUT, GATEAU_DROIT, ARROSOIR_GAUCHE, FILLE_HAUT },
        { DAME_BAS, ARROSOIR_GAUCHE, FILLE_HAUT, GATEAU_DROIT },
        { FILLE_BAS, GATEAU_GAUCHE, DAME_HAUT, ARROSOIR_DROIT },
        { ARROSOIR_DROIT, GATEAU_GAUCHE, DAME_HAUT, FILLE_HAUT},
        { FILLE_BAS, DAME_HAUT, ARROSOIR_DROIT, GATEAU_DROIT },
        { DAME_BAS, GATEAU_GAUCHE, FILLE_HAUT, ARROSOIR_DROIT},
        { FILLE_BAS, ARROSOIR_GAUCHE, DAME_HAUT, GATEAU_DROIT },
        { DAME_BAS, ARROSOIR_GAUCHE, GATEAU_DROIT, FILLE_HAUT },
        { ARROSOIR_INVERSE, DAME_HAUT, GATEAU_DROIT, FILLE_BAS }
};