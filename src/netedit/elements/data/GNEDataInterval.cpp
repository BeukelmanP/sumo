/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNEDataInterval.cpp
/// @author  Pablo Alvarez Lopez
/// @date    Jan 2020
///
// A abstract class for data sets
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <netedit/GNEViewNet.h>

#include "GNEDataInterval.h"


// ===========================================================================
// member method definitions
// ===========================================================================

// ---------------------------------------------------------------------------
// GNEDataInterval - methods
// ---------------------------------------------------------------------------

GNEDataInterval::GNEDataInterval(const std::string& id, GNEViewNet* viewNet) :
    GNEAttributeCarrier(SUMO_TAG_NOTHING),
    myViewNet(viewNet) {
}


GNEDataInterval::GNEDataInterval(GNEDataInterval* dataSetParent, GNEViewNet* viewNet) :
    GNEAttributeCarrier(SUMO_TAG_NOTHING),
    myViewNet(viewNet) {
}


GNEDataInterval::~GNEDataInterval() {}


bool
GNEDataInterval::isDataIntervalValid() const {
    return true;
}


std::string
GNEDataInterval::getDataIntervalProblem() const {
    return "";
}


void
GNEDataInterval::fixDataIntervalProblem() {
    throw InvalidArgument(getTagStr() + " cannot fix any problem");
}


GNEViewNet*
GNEDataInterval::getViewNet() const {
    return myViewNet;
}


bool
GNEDataInterval::isAttributeCarrierSelected() const {
    return mySelected;
}


bool
GNEDataInterval::drawUsingSelectColor() const {
    if (mySelected && (myViewNet->getEditModes().currentSupermode == GNE_SUPERMODE_DEMAND)) {
        return true;
    } else {
        return false;
    }
}

/****************************************************************************/
