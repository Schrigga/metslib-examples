#pragma once
// METSlib tutorial source file - tut_moves.cc                 -*- C++ -*-
//
// Copyright (C) 2009 Mirko Maischberger <mirko.maischberger@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <typeinfo>
#include <metslib/mets.h>
#include "tut_model.h"

/// @brief A move that sets 
class toggle : public mets::mana_move {
  int index_m;
public:
  toggle(int i) : index_m(i) {}
  /// @brief Apply this move
  void apply(mets::feasible_solution& s)
  {
    subsetsum& model = reinterpret_cast<subsetsum&>(s);
    model.delta(index_m, !model.delta(index_m));
  }
  /// @brief Restores previous value.
  ///
  /// It's safe (and fast) to toggle again since apply and unapply ar
  /// always called in pairs. No other move is made in between.
  ///
  void unapply(mets::feasible_solution& s)
  {
    this->apply(s);
  }

  /// @brief Virtual method used by the tabu list to take a copy of a move
  mana_move* clone() const { return new toggle(index_m); }

  /// @brief A number identifying this move as much as possible. It's
  /// used for quick testing presence of moves in the tabu list via an
  /// hash map.
  size_t hash() const { return index_m; }

  /// @brief Comparison of moves: used to test if a move in in a tabu list
  bool operator==(const mets::mana_move& o) const
  {
    //  We first check if the move if of our same type (different move
    // types can coexist in the same tabu list).
    try {
      const toggle& other = dynamic_cast<const toggle&>(o);
      // Then we check for equality
      return (this->index_m == other.index_m);
    } catch (std::bad_cast& e) {
      return false;
    }
  }
   
};