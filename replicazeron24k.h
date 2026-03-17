#pragma once

#include "quantum.h"

// =============================================================
//  REPLICAZERON 24K - replicazeron24k.h
//  Macro de layout para 1 fila x 24 teclas (pines directos)
// =============================================================

/*
 *  Mapa de teclas (Azeron Cyborg 2):
 *
 *  ÍNDICE          MEDIO           ANULAR          MEÑIQUE
 *  T1  T2  T3     T6  T7          T10 T11         T14 T15
 *  T4  T5         T8  T9          T12 T13         T16 T17
 *
 *  PULGAR                          PALMA
 *  T18 T19 T20 T21 T22             T23 T24(WASD)
 */

#define LAYOUT_direct( \
    k00, k01, k02, k03, k04,  \
    k05, k06, k07, k08,       \
    k09, k10, k11, k12,       \
    k13, k14, k15, k16,       \
    k17, k18, k19, k20, k21,  \
    k22, k23                  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23 } \
}
