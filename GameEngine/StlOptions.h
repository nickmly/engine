#ifndef STL_OPTIONS_H
#define STL_OPTIONS_H

#pragma once

//////////////////////////////////////////////////////////////
// disable iterator debugging for perrformannce in DEBUG mode.
// Removing iterator checking by itself boosts speed by ~80%
//////////////////////////////////////////////////////////////
#ifdef _HAS_ITERATOR_DEBUGGING
#undef _HAS_ITERATOR_DEBUGGING
#endif

#define _HAS_ITERATOR_DEBUGGING 0

#endif