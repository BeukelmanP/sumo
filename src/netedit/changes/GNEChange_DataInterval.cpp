/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNEChange_DataInterval.cpp
/// @author  Pablo Alvarez Lopez
/// @date    Jan 2020
///
// A network change in which a data interval element is created or deleted
/****************************************************************************/

// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <netedit/GNENet.h>
#include <netedit/elements/data/GNEDataInterval.h>
#include <netedit/elements/data/GNEDataSet.h>
#include <netedit/GNEViewNet.h>

#include "GNEChange_DataInterval.h"

// ===========================================================================
// FOX-declarations
// ===========================================================================
FXIMPLEMENT_ABSTRACT(GNEChange_DataInterval, GNEChange, nullptr, 0)

// ===========================================================================
// member method definitions
// ===========================================================================

GNEChange_DataInterval::GNEChange_DataInterval(GNEDataInterval* dataInterval, bool forward) :
    GNEChange(dataInterval->getDataSetParent()->getViewNet()->getNet(), forward),
    myDataInterval(dataInterval),
    myDataSetParent(dataInterval->getDataSetParent()) {
    myDataInterval->incRef("GNEChange_DataInterval");
}


GNEChange_DataInterval::~GNEChange_DataInterval() {
    assert(myDataInterval);
    myDataInterval->decRef("GNEChange_DataInterval");
    if (myDataInterval->unreferenced()) {
        // show extra information for tests
        WRITE_DEBUG("Deleting unreferenced " + myDataInterval->getTagStr() + " '" + myDataInterval->getID() + "'");
        // make sure that element isn't in net before removing
        if (myDataSetParent->dataIntervalChildrenExist(myDataInterval)) {
             // remove data interval from data set parent
            myDataSetParent->removeDataIntervalChild(myDataInterval);
        }
        delete myDataInterval;
    }
}


void
GNEChange_DataInterval::undo() {
    if (myForward) {
        // show extra information for tests
        WRITE_DEBUG("Removing " + myDataInterval->getTagStr() + " '" + myDataInterval->getID() + "' in GNEChange_DataInterval");
         // remove data interval from data set parent
        myDataSetParent->removeDataIntervalChild(myDataInterval);
    } else {
        // show extra information for tests
        WRITE_DEBUG("Adding " + myDataInterval->getTagStr() + " '" + myDataInterval->getID() + "' in GNEChange_DataInterval");
        // add data interval into data set parent
        myDataSetParent->addDataIntervalChild(myDataInterval);
    }
    // Requiere always save elements
    myNet->requireSaveDataElements(true);
}


void
GNEChange_DataInterval::redo() {
    if (myForward) {
        // show extra information for tests
        WRITE_DEBUG("Adding " + myDataInterval->getTagStr() + " '" + myDataInterval->getID() + "' in GNEChange_DataInterval");
        // add data interval into data set parent
        myDataSetParent->addDataIntervalChild(myDataInterval);
    } else {
        // show extra information for tests
        WRITE_DEBUG("Removing " + myDataInterval->getTagStr() + " '" + myDataInterval->getID() + "' in GNEChange_DataInterval");
        // remove data interval from data set parent
        myDataSetParent->removeDataIntervalChild(myDataInterval);
    }
    // Requiere always save elements
    myNet->requireSaveDataElements(true);
}


FXString
GNEChange_DataInterval::undoName() const {
    if (myForward) {
        return ("Undo create " + myDataInterval->getTagStr()).c_str();
    } else {
        return ("Undo delete " + myDataInterval->getTagStr()).c_str();
    }
}


FXString
GNEChange_DataInterval::redoName() const {
    if (myForward) {
        return ("Redo create " + myDataInterval->getTagStr()).c_str();
    } else {
        return ("Redo delete " + myDataInterval->getTagStr()).c_str();
    }
}
