/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNEEdgeDataFrame.h
/// @author  Pablo Alvarez Lopez
/// @date    Jan 2020
///
// The Widget for add edgeData elements
/****************************************************************************/
#pragma once


// ===========================================================================
// included modules
// ===========================================================================

#include <netedit/frames/GNEFrame.h>


// ===========================================================================
// class declaration
// ===========================================================================

class GNEDataInterval;
class GNEDataSet;

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNEEdgeDataFrame
 * The Widget for setting internal attributes of additional elements
 */
class GNEEdgeDataFrame : public GNEFrame {

public:
    // ===========================================================================
    // class DataSetSelector
    // ===========================================================================

    class DataSetSelector : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNEEdgeDataFrame::DataSetSelector)

    public:
        /// @brief constructor
        DataSetSelector(GNEEdgeDataFrame* edgeDataFrameParent);

        /// @brief destructor
        ~DataSetSelector();

        /// @brief refresh interval selector
        void refreshDataSetSelector();

        /// @brief get new data set ID (or return empty string if isn't valid)
        std::string getNewDataSetID() const;

        /// @brief get current select data set ID
        GNEDataSet *getSelectedDataSet() const;

        /// @brief check if we're creating a new data set
        bool createNewDataSet() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when the user set a new data set ID
        long onCmdSetNewDataSetID(FXObject*, FXSelector, void*);

        /// @brief Called when the user select an existent data set
        long onCmdSelectDataSet(FXObject* obj, FXSelector, void*);

        /// @brief Called when the user select a radio button
        long onCmdSelectRadioButton(FXObject* obj, FXSelector, void*);

        /// @}

    protected:
        FOX_CONSTRUCTOR(DataSetSelector)

    private:
        /// @brief pointer to edgeData frame Parent
        GNEEdgeDataFrame* myEdgeDataFrameParent;

        /// @brief radio button to create a new dataSet
        FXRadioButton *myNewDataSetRadioButton;

        /// @brief radio button to select an existent dataSet
        FXRadioButton *myExistentDataSetRadioButton;

        /// @brief data set label
        FXLabel *myNetDataSetLabel;

        /// @brief interval new id
        FXTextField *myNewDataSetIDTextField; 

        /// @brief comboBox with intervals
        FXComboBox* myDataSetsComboBox;
    };

    /*
    /// @brief interval begin
    FXTextField *myBeginTextField; 

    /// @brief interval end
    FXTextField *myEndTextField; 
    */
    /**@brief Constructor
     * @brief parent FXHorizontalFrame in which this GNEFrame is placed
     * @brief viewNet viewNet that uses this GNEFrame
     */
    GNEEdgeDataFrame(FXHorizontalFrame* horizontalFrameParent, GNEViewNet* viewNet);

    /// @brief Destructor
    ~GNEEdgeDataFrame();

    /// @brief show Frame
    void show();

    /**@brief add additional element
     * @param objectsUnderCursor collection of objects under cursor after click over view
     * @return true if additional was sucesfully added
     */
    bool addEdgeData(const GNEViewNetHelper::ObjectsUnderCursor& objectsUnderCursor);

protected:
    /// @brief DataSetSelector modul
    DataSetSelector *myDataSetSelector;

    /// @brief parameters editor
    GNEFrameAttributesModuls::ParametersEditor *myParametersEditor;

    /// @brief interval selected
    void intervalSelected();

private:
    //
};

/****************************************************************************/
