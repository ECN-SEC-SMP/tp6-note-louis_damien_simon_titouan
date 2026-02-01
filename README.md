# CPP - TP6 Otrio

```
Louis VAILLANT
Damien BUREAU
Titouan COPIN
Simon CAU
```

## Présentation
Implémentation console du jeu Otrio réalisée dans le cadre du TP6 de C++.

## Règles du jeu
Otrio se joue sur un plateau 3×3. Chaque case peut accueillir trois anneaux de tailles différentes (petit, moyen, grand) qui se superposent.

**But** : aligner 3 pièces de sa couleur pour gagner.

**Conditions de victoire** :
- 3 anneaux de même taille alignés (ligne, colonne ou diagonale)
- 3 anneaux de tailles croissantes (petit → moyen → grand) alignés
- 3 anneaux empilés sur la même case (petit + moyen + grand)

**Déroulement** : chaque joueur place un anneau par tour jusqu'à ce qu'un joueur gagne ou que toutes les pièces soient posées (égalité).

## Documentation
- Justification détaillée des choix d'architecture dans [doc/README.md](doc/README.md).

## Répartition

### Louis
- classe Otrio
- classe Player
- gestion du menu


### Damien
- classe Board
  - unit tests for string output
  - rename "wall" en "grid"
- classe Frame
- classe Circle
- classe Player
- Render
  - board
  - playersInventory


### Simon
- algos de `checkWinConditions()`
- classe PlayerBot


### Titouan
- classe GameManager
- documentation 