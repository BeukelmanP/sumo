/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNEChange_DataSet.cpp
/// @author  Pablo Alvarez Lopez
/// @date    Jan 2020
///
// A network change in which a data set element is created or deleted
/****************************************************************************/

// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <netedit/GNENet.h>
#include <netedit/elements/data/GNEDataSet.h>
#include <netedit/elements/data/GNEDataInterval.h>
#include <netedit/GNEViewNet.h>

#include "GNEChange_DataSet.h"

// ===========================================================================
// FOX-declarations
// ===========================================================================
FXIMPLEMENT_ABSTRACT(GNEChange_DataSet, GNEChange, nullptr, 0)

// ===========================================================================
// member method definitions
// ===========================================================================

GNEChange_DataSet::GNEChange_DataSet(GNEDataSet* dataSet, bool forward) :
    GNEChange(dataSet->getViewNet()->getNet(), forward),
    myDataSet(dataSet) {
    myDataSet->incRef("GNEChange_DataSet");
}


GNEChange_DataSet::~GNEChange_DataSet() {
    assert(myDataSet);
    myDataSet->decRef("GNEChange_DataSet");
    if (myDataSet->unreferenced()) {
        // show extra information for tests
        WRITE_DEBUG("Deleting unreferenced " + myDataSet->getTagStr() + " '" + myDataSet->getID() + "'");
        // make sure that element isn't in net before removing
        if (myNet->dataSetExist(myDataSet)) {
            myNet->deleteDataSet(myDataSet);
        }
        delete myDataSet;
    }
}


void
GNEChange_DataSet::undo() {
    if (myForward) {
        // show extra information for tests
        WRITE_DEBUG("Removing " + myDataSet->getTagStr() + " '" + myDataSet->getID() + "' in GNEChange_DataSet");
        // delete data set from net
        myNet->deleteDataSet(myDataSet);
    } else {
        // show extra information for tests
        WRITE_DEBUG("Adding " + myDataSet->getTagStr() + " '" + myDataSet->getID() + "' in GNEChange_DataSet");
        // insert data set into net
        myNet->insertDataSet(myDataSet);
    }
    // Requiere always save elements
    myNet->requireSaveDataElements(true);
}


void
GNEChange_DataSet::redo() {
    if (myForward) {
        // show extra information for tests
        WRITE_DEBUG("Adding " + myDataSet->getTagStr() + " '" + myDataSet->getID() + "' in GNEChange_DataSet");
        // insert data set into net
        myNet->insertDataSet(myDataSet);
    } else {
        // show extra information for tests
        WRITE_DEBUG("Removing " + myDataSet->getTagStr() + " '" + myDataSet->getID() + "' in GNEChange_DataSet");
        // delete data set from net
        myNet->deleteDataSet(myDataSet);
    }
    // Requiere always save elements
    myNet->requireSaveDataElements(true);
}


FXString
GNEChange_DataSet::undoName() const {
    if (myForward) {
        return ("Undo create " + myDataSet->getTagStr()).c_str();
    } else {
        return ("Undo delete " + myDataSet->getTagStr()).c_str();
    }
}


FXString
GNEChange_DataSet::redoName() const {
    if (myForward) {
        return ("Redo create " + myDataSet->getTagStr()).c_str();
    } else {
        return ("Redo delete " + myDataSet->getTagStr()).c_str();
    }
}
