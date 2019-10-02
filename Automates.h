#pragma once

#include "AutomatGraph.h"


DeterminedAutomatGraph determine(const AutomatGraph& UFA);

DeterminedAutomatGraph make_full(const DeterminedAutomatGraph& DFA);

DeterminedAutomatGraph invert(const DeterminedAutomatGraph& FDFA);

DeterminedAutomatGraph make_minimal(const DeterminedAutomatGraph& FDFA);
