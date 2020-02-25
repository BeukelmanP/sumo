/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNEEdgeData.cpp
/// @author  Pablo Alvarez Lopez
/// @date    Jan 2020
///
// class for edge data
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <netedit/GNEViewNet.h>
#include <netedit/GNEUndoList.h>
#include <netedit/changes/GNEChange_Attribute.h>
#include <netedit/elements/network/GNEEdge.h>

#include "GNEEdgeData.h"
#include "GNEDataInterval.h"


// ===========================================================================
// member method definitions
// ===========================================================================

// ---------------------------------------------------------------------------
// GNEEdgeData - methods
// ---------------------------------------------------------------------------

GNEEdgeData::GNEEdgeData(GNEDataInterval* dataIntervalParent, GNEEdge *edgeParent, const std::map<std::string, std::string>& parameters) :
    GNEGenericData(SUMO_TAG_MEANDATA_EDGE, dataIntervalParent, parameters,
        {edgeParent}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}) {
}


GNEEdgeData::~GNEEdgeData() {}


void 
GNEEdgeData::updateGeometry() {
    // nothing to update
}


void 
GNEEdgeData::updateDottedContour() {
    // nothing to update
}


Position 
GNEEdgeData::getPositionInView() const {
    return getParentEdges().front()->getPositionInView();
}


void 
GNEEdgeData::writeGenericData(OutputDevice& device) const {
    // open device
    device.openTag(myTagProperty.getTag());
    // write edge ID
    device.writeAttr(SUMO_ATTR_ID, getParentEdges().front()->getID());
    // write params
    writeParams(device);
    // close device
    device.closeTag();
}


bool
GNEEdgeData::isGenericDataValid() const {
    return true;
}


std::string
GNEEdgeData::getGenericDataProblem() const {
    return "";
}


void
GNEEdgeData::fixGenericDataProblem() {
    throw InvalidArgument(getTagStr() + " cannot fix any problem");
}


void 
GNEEdgeData::selectAttributeCarrier(bool changeFlag) {
    //
}


void
GNEEdgeData::unselectAttributeCarrier(bool changeFlag) {
    //
}


bool
GNEEdgeData::isAttributeCarrierSelected() const {
    return mySelected;
}


bool
GNEEdgeData::drawUsingSelectColor() const {
    if (mySelected && (getViewNet()->getEditModes().currentSupermode == GNE_SUPERMODE_DEMAND)) {
        return true;
    } else {
        return false;
    }
}


std::string 
GNEEdgeData::getAttribute(SumoXMLAttr key) const {
    switch (key) {
        case SUMO_ATTR_ID:
            return getParentEdges().front()->getID();
        case GNE_ATTR_PARAMETERS:
            return getParametersStr();
        default:
            throw InvalidArgument(getTagStr() + " doesn't have an attribute of type '" + toString(key) + "'");
    }
}


double 
GNEEdgeData::getAttributeDouble(SumoXMLAttr key) const {
    throw InvalidArgument(getTagStr() + " doesn't have a double attribute of type '" + toString(key) + "'");
}


void 
GNEEdgeData::setAttribute(SumoXMLAttr key, const std::string& value, GNEUndoList* undoList) {
    if (value == getAttribute(key)) {
        return; //avoid needless changes, later logic relies on the fact that attributes have changed
    }
    switch (key) {
        case GNE_ATTR_PARAMETERS:
            undoList->p_add(new GNEChange_Attribute(this, getViewNet()->getNet(), key, value));
            break;
        default:
            throw InvalidArgument(getTagStr() + " doesn't have an attribute of type '" + toString(key) + "'");
    }
}


bool 
GNEEdgeData::isValid(SumoXMLAttr key, const std::string& value) {
    switch (key) {
        case GNE_ATTR_PARAMETERS:
            return Parameterised::areParametersValid(value);
        default:
            throw InvalidArgument(getTagStr() + " doesn't have an attribute of type '" + toString(key) + "'");
    }
}


void 
GNEEdgeData::enableAttribute(SumoXMLAttr /*key*/, GNEUndoList* /*undoList*/) {
    // Nothing to enable
}


void 
GNEEdgeData::disableAttribute(SumoXMLAttr /*key*/, GNEUndoList* /*undoList*/) {
    // Nothing to disable enable
}


bool GNEEdgeData::isAttributeEnabled(SumoXMLAttr /*key*/) const {
    return true;
}


std::string 
GNEEdgeData::getPopUpID() const {
    return getTagStr();
}


std::string 
GNEEdgeData::getHierarchyName() const {
    return getTagStr() + ": " + getParentEdges().front()->getID();
}


void 
GNEEdgeData::setAttribute(SumoXMLAttr key, const std::string& value) {
    switch (key) {
        case GNE_ATTR_PARAMETERS:
            setParametersStr(value);
            break;
        default:
            throw InvalidArgument(getTagStr() + " doesn't have an attribute of type '" + toString(key) + "'");
    }
}


void 
GNEEdgeData::setEnabledAttribute(const int /*enabledAttributes*/) {
    throw InvalidArgument("Nothing to enable");
}

/****************************************************************************/
