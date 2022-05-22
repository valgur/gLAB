/*This file is part of gLAB's GUI.

    gLAB's GUI is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3.

    gLAB's GUI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with gLAB's GUI.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "glab_gui.h"
#include "ui_glab_gui.h"

//Set tooltips for each item in the Conditions combo box for plot 1
void gLAB_GUI::set_conditionsComboBoxPlot1_OutputMessagesTooltips() {
    ui->comboBoxPlot1Condition->setItemData(0,ui->comboBoxPlot1Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(1,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(2,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(3,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(4,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(5,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(6,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(7,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(8,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(9,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(10,ui->checkBoxPrintSatstatCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(11,ui->checkBoxPrintSatstattotCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(12,ui->checkBoxPrintSatpvtShowOrbit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(13,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(14,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(15,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(16,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(17,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(18,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot1Condition->setItemData(19,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
}

//Set tooltips for each item in the Conditions combo box for plot 2
void gLAB_GUI::set_conditionsComboBoxPlot2_OutputMessagesTooltips() {
    ui->comboBoxPlot2Condition->setItemData(0,ui->comboBoxPlot2Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(1,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(2,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(3,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(4,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(5,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(6,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(7,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(8,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(9,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(10,ui->checkBoxPrintSatstatCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(11,ui->checkBoxPrintSatstattotCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(12,ui->checkBoxPrintSatpvtShowOrbit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(13,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(14,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(15,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(16,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(17,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(18,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot2Condition->setItemData(19,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
}

//Set tooltips for each item in the Conditions combo box for plot 3
void gLAB_GUI::set_conditionsComboBoxPlot3_OutputMessagesTooltips() {
    ui->comboBoxPlot3Condition->setItemData(0,ui->comboBoxPlot3Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(1,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(2,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(3,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(4,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(5,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(6,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(7,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(8,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(9,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(10,ui->checkBoxPrintSatstatCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(11,ui->checkBoxPrintSatstattotCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(12,ui->checkBoxPrintSatpvtShowOrbit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(13,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(14,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(15,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(16,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(17,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(18,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot3Condition->setItemData(19,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
}

//Set tooltips for each item in the Conditions combo box for plot 4
void gLAB_GUI::set_conditionsComboBoxPlot4_OutputMessagesTooltips() {
    ui->comboBoxPlot4Condition->setItemData(0,ui->comboBoxPlot4Condition->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(1,ui->checkBoxPrintInput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(2,ui->checkBoxPrintCS->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(3,ui->checkBoxPrintModel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(4,ui->checkBoxPrintEpochsat->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(5,ui->checkBoxPrintPrefit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(6,ui->checkBoxPrintPostfit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(7,ui->checkBoxPrintFilter->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(8,ui->checkBoxPrintOutput->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(9,ui->checkBoxPrintSatdiff->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(10,ui->checkBoxPrintSatstatCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(11,ui->checkBoxPrintSatstattotCompare->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(12,ui->checkBoxPrintSatpvtShowOrbit->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(13,ui->checkBoxPrintSbascor->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(14,ui->checkBoxPrintSbasvar->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(15,ui->checkBoxPrintSbasiono->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(16,ui->checkBoxPrintSbasunsel->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(17,ui->checkBoxPrintSbasout->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(18,ui->checkBoxPrintDgnss->toolTip(),Qt::ToolTipRole);
    ui->comboBoxPlot4Condition->setItemData(19,ui->checkBoxPrintUsererror->toolTip(),Qt::ToolTipRole);
}

// Function to Clear the Plots configurations
void gLAB_GUI::on_pushButtonPlotClear_clicked() {
    this->on_checkBoxAutoLimits_clicked(true);
    this->on_checkBoxAutoTicks_clicked(true);
    this->on_radioButtonPlotNr1_clicked();
    ui->comboBoxLabelPosition->setCurrentIndex(0);
    ui->checkBoxExpandFigureToMargin->setChecked(false);
    ui->lineEditPlotTitle->setText("");
    ui->lineEditPlotXLabel->setText("");
    ui->lineEditPlotYLabel->setText("");
    ui->lineEditFractionalText->setText("");
    ui->lineEditWaterMark->setText("");
    ui->lineEditPlotXmin->setText("");
    ui->lineEditPlotXmax->setText("");
    ui->lineEditPlotYmin->setText("");
    ui->lineEditPlotYmax->setText("");
    ui->lineEditXTickNum->setText("");
    ui->lineEditYTickNum->setText("");
    ui->pushButtonPlot->setEnabled(false);
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    ui->checkBoxPEPercentiles->setChecked(false);
    ui->checkBoxPLPercentiles->setChecked(false);

    //Enable all options disabled by Stanford or Stanford-ESA templates
    StanfordPlotSelected = 0;
    StanfordESAPlotSelected = 0;
    ui->radioButtonPlotNr2->setDisabled(false);
    ui->radioButtonPlotNr3->setDisabled(false);
    ui->radioButtonPlotNr4->setDisabled(false);
    ui->comboBoxPlot1Condition->setDisabled(false);
    ui->comboBoxPlot1ConditionOutput->setDisabled(false);
    ui->lineEditPlot1Condition->setDisabled(false);
    ui->comboBoxPlot1TypeLine->setDisabled(false);
    ui->comboBoxPlot1ColorLine->setDisabled(false);
    ui->comboBoxPlot1Xsbasout->setDisabled(false);
    ui->lineEditPlot1Xcolumn->setDisabled(false);
    ui->lineEditPlot1Ycolumn->setDisabled(false);
    ui->lineEditPlot1LegendLabel->setDisabled(false);

    ui->lineEditFractionalText->setDisabled(false);
    ui->comboBoxLabelPosition->setDisabled(false);
    ui->checkBoxAutoLimits->setDisabled(false);
    ui->checkBoxAutoTicks->setDisabled(false);
    ui->lineEditPlotXmin->setDisabled(false);
    ui->lineEditPlotYmin->setDisabled(false);
    ui->lineEditPlotXmax->setDisabled(false);
    ui->lineEditPlotYmax->setDisabled(false);


    // Plot Nr 1
    ui->lineEditPlot1SourceFile->setText("");
    ui->comboBoxPlot1TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot1ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot1Condition_currentIndexChanged(0);
    ui->comboBoxPlot1ColorLine->setCurrentIndex(0);   
    ui->lineEditPlot1Xcolumn->setText("");
    ui->lineEditPlot1Ycolumn->setText("");
    ui->lineEditPlot1LegendLabel->setText("");
    // Plot Nr 2
    ui->lineEditPlot2SourceFile->setText("");
    ui->comboBoxPlot2TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot2ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot2Condition_currentIndexChanged(0);
    ui->comboBoxPlot2ColorLine->setCurrentIndex(1);
    ui->lineEditPlot2Xcolumn->setText("");
    ui->lineEditPlot2Ycolumn->setText("");
    ui->lineEditPlot2LegendLabel->setText("");
    // Plot Nr 3
    ui->lineEditPlot3SourceFile->setText("");
    ui->comboBoxPlot3TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot3ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot3Condition_currentIndexChanged(0);
    ui->comboBoxPlot3ColorLine->setCurrentIndex(2);
    ui->lineEditPlot3Xcolumn->setText("");
    ui->lineEditPlot3Ycolumn->setText("");
    ui->lineEditPlot3LegendLabel->setText("");
    // Plot Nr 4
    ui->lineEditPlot4SourceFile->setText("");
    ui->comboBoxPlot4TypeLine->setCurrentIndex(0);
    ui->comboBoxPlot4ConditionOutput->setCurrentIndex(0);
    this->on_comboBoxPlot4Condition_currentIndexChanged(0);
    ui->comboBoxPlot4ColorLine->setCurrentIndex(3);
    ui->lineEditPlot4Xcolumn->setText("");
    ui->lineEditPlot4Ycolumn->setText("");
    ui->lineEditPlot4LegendLabel->setText("");
}

// Function to show or hide the plot limits
void gLAB_GUI::on_checkBoxAutoLimits_clicked(bool checked) {
    ui->checkBoxAutoLimits->setChecked(checked);
    ui->frameAutoLimits->setHidden(checked);
}

// Function to show or hide the tick limits
void gLAB_GUI::on_checkBoxAutoTicks_clicked(bool checked) {
    ui->checkBoxAutoTicks->setChecked(checked);
    ui->frameAutoTicks->setHidden(checked);
}


// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr1_clicked() {
    ui->radioButtonPlotNr1->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(0);
}

// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr2_clicked() {
    ui->radioButtonPlotNr2->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(1);
}

// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr3_clicked() {
    ui->radioButtonPlotNr3->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(2);
}

// Function to set the correct stacked widget in Analysis mode
void gLAB_GUI::on_radioButtonPlotNr4_clicked() {
    ui->radioButtonPlotNr4->setChecked(true);
    ui->stackedWidgetPlotNr->setCurrentIndex(3);
}

////////////////// Plot Nr 1 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot1Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot1Condition->setCurrentIndex(index);
    ui->stackedWidgetPlot1Xcolumn->setCurrentIndex(index);
    ui->stackedWidgetPlot1Ycolumn->setCurrentIndex(index);
    ui->comboBoxPlot1ConditionPrn->setCurrentIndex(0);
    ui->lineEditPlot1Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot1Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot1Xcolumn->setText("");
    ui->lineEditPlot1Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot1Xcolumn->setHidden(true);
        ui->lineEditPlot1Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot1Xcolumn->setHidden(false);
        ui->lineEditPlot1Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("");                        
            break;
        }
        case 1 : { // Input
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 2 : { // Cycle slips
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"CS\")");
            break;
        }
        case 3 : { // Model
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 4 : { // Epochsat
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 5 : { // Prefit
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 6 : { // Postfit
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 7 : { // Filter
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 8 : { // Output
            ui->stackedWidgetPlot1Condition->setCurrentIndex(2);
            ui->lineEditPlot1Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 9 : { // Satdiff
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 10 : { // Satstat
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 11 : { // Satstattot
            ui->stackedWidgetPlot1Condition->setCurrentIndex(0);
            ui->lineEditPlot1Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 12 : { // Satpvt
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SATPVT\")");
            break;
        }
        case 13 : { // SBASCORR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 14 : { // SBASVAR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 15 : { // SBASIONO
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 16 : { // SBASUNSEL
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 17 : { // SBASOUT
            ui->stackedWidgetPlot1Condition->setCurrentIndex(2);
            ui->lineEditPlot1Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 18 : { // DGNSS
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->stackedWidgetPlot1Condition->setCurrentIndex(1);
            ui->lineEditPlot1Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot1ConditionPrn_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index);
    }
    ui->lineEditPlot1Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 1
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot1ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot1Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($33==%1)").arg(index-1);
    }
    ui->lineEditPlot1Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot1SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out *.txt);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}

//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot1SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot1SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}



// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot1Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot1Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot1Xcolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot1Xcolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot1Xinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot1Xcs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot1Xmodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot1Xepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot1Xprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot1Xpostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot1Xfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot1Xoutput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot1Xsatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot1Xsatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot1Xsatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot1Xsatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot1Xsbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot1Xsbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot1Xsbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot1Xsbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot1Xsbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot1Xdgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot1Xuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot1Xinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xcs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xmodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xpostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xoutput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xsbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xdgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Xuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot1Xcolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the X column line edit

// Function to set the correct value of the combo box Y column from line edit
void gLAB_GUI::on_lineEditPlot1Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot1Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot1Ycolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot1Ycolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot1Yinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot1Ycs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot1Ymodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot1Yepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot1Yprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot1Ypostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot1Yfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot1Youtput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot1Ysatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot1Ysatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot1Ysatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot1Ysatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot1Ysbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot1Ysbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot1Ysbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot1Ysbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot1Ysbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot1Ydgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot1Yuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the Y column line edit
void gLAB_GUI::on_comboBoxPlot1Yinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ycs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ymodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Yepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Yprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ypostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Yfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Youtput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ysbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Ydgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot1Yuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot1Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot1Ycolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the Y column line edit


////////////////// Plot Nr 2 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 2
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot2Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot2Condition->setCurrentIndex(index);
    ui->stackedWidgetPlot2Xcolumn->setCurrentIndex(index);
    ui->stackedWidgetPlot2Ycolumn->setCurrentIndex(index);
    ui->comboBoxPlot2ConditionPrn->setCurrentIndex(0);
    ui->lineEditPlot2Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot2Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot2Xcolumn->setText("");
    ui->lineEditPlot2Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot2Xcolumn->setHidden(true);
        ui->lineEditPlot2Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot2Xcolumn->setHidden(false);
        ui->lineEditPlot2Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("");
            break;
        }
        case 1 : { // Input
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 2 : { // Cycle slips
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"CS\")");
            break;
        }
        case 3 : { // Model
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 4 : { // Epochsat
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 5 : { // Prefit
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 6 : { // Postfit
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 7 : { // Filter
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 8 : { // Output
            ui->stackedWidgetPlot2Condition->setCurrentIndex(2);
            ui->lineEditPlot2Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 9 : { // Satdiff
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 10 : { // Satstat
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 11 : { // Satstattot
            ui->stackedWidgetPlot2Condition->setCurrentIndex(0);
            ui->lineEditPlot2Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 12 : { // Satpvt
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SATPVT\")");
            break;
        }
        case 13 : { // SBASCORR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 14 : { // SBASVAR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 15 : { // SBASIONO
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 16 : { // SBASUNSEL
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 17 : { // SBASOUT
            ui->stackedWidgetPlot2Condition->setCurrentIndex(2);
            ui->lineEditPlot2Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 18 : { // DGNSS
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->stackedWidgetPlot2Condition->setCurrentIndex(1);
            ui->lineEditPlot2Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 2
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot2ConditionPrn_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index);
    }
    ui->lineEditPlot2Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 2
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot2ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot2Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($33==%1)").arg(index-1);
    }
    ui->lineEditPlot2Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot2SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}


//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot2SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot2SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}


// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot2Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot2Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot2Xcolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot2Xcolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot2Xinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot2Xcs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot2Xmodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot2Xepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot2Xprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot2Xpostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot2Xfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot2Xoutput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot2Xsatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot2Xsatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot2Xsatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot2Xsatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot2Xsbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot2Xsbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot2Xsbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot2Xsbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot2Xsbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot2Xdgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot2Xuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot2Xinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xcs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xmodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xpostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xoutput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xsbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xdgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Xuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot2Xcolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the X column line edit

// Function to set the correct value of the combo box Y column from line edit
void gLAB_GUI::on_lineEditPlot2Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot2Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot2Ycolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot2Ycolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot2Yinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot2Ycs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot2Ymodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot2Yepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot2Yprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot2Ypostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot2Yfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot2Youtput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot2Ysatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot2Ysatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot2Ysatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot2Ysatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot2Ysbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot2Ysbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot2Ysbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot2Ysbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot2Ysbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot2Ydgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot2Yuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the Y column line edit
void gLAB_GUI::on_comboBoxPlot2Yinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ycs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ymodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Yepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Yprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ypostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Yfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Youtput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ysbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Ydgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot2Yuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot2Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot2Ycolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the Y column line edit


////////////////// Plot Nr 3 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 3
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot3Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot3Condition->setCurrentIndex(index);
    ui->stackedWidgetPlot3Xcolumn->setCurrentIndex(index);
    ui->stackedWidgetPlot3Ycolumn->setCurrentIndex(index);
    ui->comboBoxPlot3ConditionPrn->setCurrentIndex(0);
    ui->lineEditPlot3Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot3Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot3Xcolumn->setText("");
    ui->lineEditPlot3Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot3Xcolumn->setHidden(true);
        ui->lineEditPlot3Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot3Xcolumn->setHidden(false);
        ui->lineEditPlot3Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("");
            break;
        }
        case 1 : { // Input
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 2 : { // Cycle slips
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"CS\")");
            break;
        }
        case 3 : { // Model
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 4 : { // Epochsat
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 5 : { // Prefit
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 6 : { // Postfit
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 7 : { // Filter
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 8 : { // Output
            ui->stackedWidgetPlot3Condition->setCurrentIndex(2);
            ui->lineEditPlot3Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 9 : { // Satdiff
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 10 : { // Satstat
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 11 : { // Satstattot
            ui->stackedWidgetPlot3Condition->setCurrentIndex(0);
            ui->lineEditPlot3Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 12 : { // Satpvt
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SATPVT\")");
            break;
        }
        case 13 : { // SBASCORR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 14 : { // SBASVAR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 15 : { // SBASIONO
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 16 : { // SBASUNSEL
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 17 : { // SBASOUT
            ui->stackedWidgetPlot3Condition->setCurrentIndex(2);
            ui->lineEditPlot3Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 18 : { // DGNSS
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->stackedWidgetPlot3Condition->setCurrentIndex(1);
            ui->lineEditPlot3Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 3
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot3ConditionPrn_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index);
    }
    ui->lineEditPlot3Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 3
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot3ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot3Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($33==%1)").arg(index-1);
    }
    ui->lineEditPlot3Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot3SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}



//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot3SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot3SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}


// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot3Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot3Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot3Xcolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot3Xcolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot3Xinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot3Xcs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot3Xmodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot3Xepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot3Xprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot3Xpostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot3Xfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot3Xoutput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot3Xsatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot3Xsatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot3Xsatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot3Xsatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot3Xsbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot3Xsbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot3Xsbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot3Xsbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot3Xsbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot3Xdgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot3Xuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot3Xinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xcs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xmodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xpostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xoutput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xsbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xdgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Xuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot3Xcolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the X column line edit

// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot3Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot3Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot3Ycolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot3Ycolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot3Yinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot3Ycs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot3Ymodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot3Yepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot3Yprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot3Ypostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot3Yfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot3Youtput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot3Ysatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot3Ysatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot3Ysatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot3Ysatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot3Ysbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot3Ysbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot3Ysbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot3Ysbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot3Ysbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot3Ydgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot3Yuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the Y column line edit
void gLAB_GUI::on_comboBoxPlot3Yinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ycs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ymodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Yepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Yprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ypostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Yfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Youtput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ysbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Ydgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot3Yuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot3Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot3Ycolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the Y column line edit


////////////////// Plot Nr 4 //////////////////
///////////////////////////////////////////////
// Function to set the correct stacked window in the condition of the Plot Nr 4
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot4Condition_currentIndexChanged(int index) {
    ui->comboBoxPlot4Condition->setCurrentIndex(index);
    ui->stackedWidgetPlot4Xcolumn->setCurrentIndex(index);
    ui->stackedWidgetPlot4Ycolumn->setCurrentIndex(index);
    ui->comboBoxPlot4ConditionPrn->setCurrentIndex(0);
    ui->lineEditPlot4Xcolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot4Ycolumn->setText("1"); // To make the change to "empty" effective
    ui->lineEditPlot4Xcolumn->setText("");
    ui->lineEditPlot4Ycolumn->setText("");
    /*if ( index == 0 ) {
        ui->lineEditPlot4Xcolumn->setHidden(true);
        ui->lineEditPlot4Ycolumn->setHidden(true);
    } else {
        ui->lineEditPlot4Xcolumn->setHidden(false);
        ui->lineEditPlot4Ycolumn->setHidden(false);
    }*/
    switch ( index ) {
        case 0 : { // Nothing
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("");
            break;
        }
        case 1 : { // Input
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"INPUT\")");
            break;
        }
        case 2 : { // Cycle slips
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"CS\")");
            break;
        }
        case 3 : { // Model
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"MODEL\")");
            break;
        }
        case 4 : { // Epochsat
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"EPOCHSAT\")");
            break;
        }
        case 5 : { // Prefit
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"PREFIT\")");
            break;
        }
        case 6 : { // Postfit
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"POSTFIT\")");
            break;
        }
        case 7 : { // Filter
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"FILTER\")");
            break;
        }
        case 8 : { // Output
            ui->stackedWidgetPlot4Condition->setCurrentIndex(2);
            ui->lineEditPlot4Condition->setText("($1==\"OUTPUT\")");
            break;
        }
        case 9 : { // Satdiff
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SATDIFF\")");
            break;
        }
        case 10 : { // Satstat
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"SATSTAT\")");
            break;
        }
        case 11 : { // Satstattot
            ui->stackedWidgetPlot4Condition->setCurrentIndex(0);
            ui->lineEditPlot4Condition->setText("($1==\"SATSTATTOT\")");
            break;
        }
        case 12 : { // Satpvt
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SATPVT\")");
            break;
        }
        case 13 : { // SBASCORR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASCORR\")");
            break;
        }
        case 14 : { // SBASVAR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASVAR\")");
            break;
        }
        case 15 : { // SBASIONO
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASIONO\")");
            break;
        }
        case 16 : { // SBASUNSEL
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"SBASUNSEL\")");
            break;
        }
        case 17 : { // SBASOUT
            ui->stackedWidgetPlot4Condition->setCurrentIndex(2);
            ui->lineEditPlot4Condition->setText("($1==\"SBASOUT\")");
            break;
        }
        case 18 : { // DGNSS
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"DGNSS\")");
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->stackedWidgetPlot4Condition->setCurrentIndex(1);
            ui->lineEditPlot4Condition->setText("($1==\"USERADDEDERROR\")");
            break;
        }
    }
}

// Function to set the correct stacked window in the condition of the Plot Nr 4
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot4ConditionPrn_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($6==%1)").arg(index);
    }
    ui->lineEditPlot4Condition->setText(text);
}

// Function to set the correct stacked window in the condition of the Plot Nr 4
// and write the proper condition in the line edit
void gLAB_GUI::on_comboBoxPlot4ConditionOutput_currentIndexChanged(int index) {
    // Get the condition text of the line edit
    QString text = ui->lineEditPlot4Condition->text();
    // Get the ampersand position in the string
    int end = text.indexOf("&", 0, Qt::CaseInsensitive);
    // Delete previous second condition (from ampersand to the end)
    if ( end != -1 ) text = text.mid(0, end-1);
    // Write the new second condition
    if ( index != 0 ) {
        text = (text + " & ($33==%1)").arg(index-1);
    }
    ui->lineEditPlot4Condition->setText(text);
}

// Open dialog to set the plot source filename and path
void gLAB_GUI::on_pushButtonPlot4SourceFile_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPlot4SourceFile->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
    if ( this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true ) ui->pushButtonPlot->setEnabled(true);
    else ui->pushButtonPlot->setEnabled(false);
}

//This is to enable Plot button when the user manually sets a text file name
void gLAB_GUI::on_lineEditPlot4SourceFile_textChanged() {
    if ( this->fileExists( ui->lineEditPlot4SourceFile->text() ) == true ) {
        ui->pushButtonPlot->setEnabled(true);
    } else {
        if ( ui->lineEditPlot4SourceFile->text().isEmpty()==false) {
            ui->pushButtonPlot->setEnabled(false);
        } else {
           if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot2SourceFile->text() ) == true ||
                this->fileExists( ui->lineEditPlot3SourceFile->text() ) == true  ) {
               ui->pushButtonPlot->setEnabled(true);
           }
        }
    }
}


// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot4Xcolumn_textChanged() {
    int index;
    if (ui->lineEditPlot4Xcolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot4Xcolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot4Xcolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot4Xinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot4Xcs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot4Xmodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot4Xepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot4Xprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot4Xpostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot4Xfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot4Xoutput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot4Xsatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot4Xsatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot4Xsatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot4Xsatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot4Xsbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot4Xsbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot4Xsbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot4Xsbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot4Xsbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot4Xdgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot4Xuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the X column line edit
void gLAB_GUI::on_comboBoxPlot4Xinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xcs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xmodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xpostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xoutput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xsbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xdgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Xuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Xcolumn->setText("");
    else if (index>0) ui->lineEditPlot4Xcolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the X column line edit

// Function to set the correct value of the combo box X column from line edit
void gLAB_GUI::on_lineEditPlot4Ycolumn_textChanged() {
    int index;
    if (ui->lineEditPlot4Ycolumn->text().contains(QRegularExpression("[^0-9]"))==true) {
        index=-1;
    } else {
        index = ui->lineEditPlot4Ycolumn->text().toInt();
    }
    switch ( ui->stackedWidgetPlot4Ycolumn->currentIndex() ) {
        case 1 : { // Input
            ui->comboBoxPlot4Yinput->setCurrentIndex(index);
            break;
        }
        case 2 : { // Cycle slips
            ui->comboBoxPlot4Ycs->setCurrentIndex(index);
            break;
        }
        case 3 : { // Model
            ui->comboBoxPlot4Ymodel->setCurrentIndex(index);
            break;
        }
        case 4 : { // Epochsat
            ui->comboBoxPlot4Yepochsat->setCurrentIndex(index);
            break;
        }
        case 5 : { // Prefit
            ui->comboBoxPlot4Yprefit->setCurrentIndex(index);
            break;
        }
        case 6 : { // Postfit
            ui->comboBoxPlot4Ypostfit->setCurrentIndex(index);
            break;
        }
        case 7 : { // Filter
            ui->comboBoxPlot4Yfilter->setCurrentIndex(index);
            break;
        }
        case 8 : { // Output
            ui->comboBoxPlot4Youtput->setCurrentIndex(index);
            break;
        }
        case 9 : { // Satdiff
            ui->comboBoxPlot4Ysatdiff->setCurrentIndex(index);
            break;
        }
        case 10 : { // Satstat
            ui->comboBoxPlot4Ysatstat->setCurrentIndex(index);
            break;
        }
        case 11 : { // Satstattot
            ui->comboBoxPlot4Ysatstattot->setCurrentIndex(index);
            break;
        }
        case 12 : { // Satpvt
            ui->comboBoxPlot4Ysatpvt->setCurrentIndex(index);
            break;
        }
        case 13 : { // SBASCORR
            ui->comboBoxPlot4Ysbascorr->setCurrentIndex(index);
            break;
        }
        case 14 : { // SBASVAR
            ui->comboBoxPlot4Ysbasvar->setCurrentIndex(index);
            break;
        }
        case 15 : { // SBASIONO
            ui->comboBoxPlot4Ysbasiono->setCurrentIndex(index);
            break;
        }
        case 16 : { // SBASUNSEL
            ui->comboBoxPlot4Ysbasunsel->setCurrentIndex(index);
            break;
        }
        case 17 : { // SBASOUT
            ui->comboBoxPlot4Ysbasout->setCurrentIndex(index);
            break;
        }
        case 18 : { // DGNSS
            ui->comboBoxPlot4Ydgnss->setCurrentIndex(index);
            break;
        }
        case 19 : { // USERADDEDERROR
            ui->comboBoxPlot4Yuseraddederror->setCurrentIndex(index);
            break;
        }
    }
}

//// Functions to set the correct number in the Y column line edit
void gLAB_GUI::on_comboBoxPlot4Yinput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ycs_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ymodel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Yepochsat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Yprefit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ypostfit_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Yfilter_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Youtput_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysatdiff_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysatstat_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysatstattot_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysatpvt_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysbascorr_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysbasvar_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysbasiono_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysbasunsel_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ysbasout_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Ydgnss_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
void gLAB_GUI::on_comboBoxPlot4Yuseraddederror_currentIndexChanged(int index) {
    if ( index == 0 ) ui->lineEditPlot4Ycolumn->setText("");
    else if (index>0) ui->lineEditPlot4Ycolumn->setText(QString::number(index));
}
//// End of Functions to set the correct number in the Y column line edit

// Template for NEU Positioning Error
void gLAB_GUI::on_pushButtonTemplateNeuPositioningError_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("NEU Positioning Error");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Error (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(8);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("18");
    ui->lineEditPlot1LegendLabel->setText("North error");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(8);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("19");
    ui->lineEditPlot2LegendLabel->setText("East error");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(8);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("20");
    ui->lineEditPlot3LegendLabel->setText("Up error");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Horizontal Positioning Error
void gLAB_GUI::on_pushButtonTemplateHorizontalError_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Horizontal Positioning Error");
    ui->lineEditPlotXLabel->setText("East error (m)");
    ui->lineEditPlotYLabel->setText("North error (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(8);
    ui->lineEditPlot1Xcolumn->setText("19");
    ui->lineEditPlot1Ycolumn->setText("18");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Zenith Tropospheric Delay
void gLAB_GUI::on_pushButtonTemplateZenithTroposphericDelay_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Zenith Tropospheric Delay");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Troposphere (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(7);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("9");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Ionospheric Combinations
void gLAB_GUI::on_pushButtonTemplateIonosphericCombinations_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Ionospheric Combinations");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Metres of L1-L2 delay (m)");
    this->on_checkBoxAutoLimits_clicked(false);
    ui->lineEditPlotYmin->setText("-10");
    ui->lineEditPlotYmax->setText("10");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot1Condition->setCurrentIndex(1);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("($10-$9)");
    ui->lineEditPlot1LegendLabel->setText("All PRN : PI=(P2-P1)");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot2ColorLine->setCurrentIndex(2);
    ui->comboBoxPlot2Condition->setCurrentIndex(1);
    ui->comboBoxPlot2ConditionPrn->setCurrentIndex(13);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("($10-$9)");
    ui->lineEditPlot2LegendLabel->setText("PRN 13 : PI=(P2-P1)");
    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Dilution Of Precision
void gLAB_GUI::on_pushButtonTemplateDOP_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Dilution Of Precision");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("DOP (adimensional)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(8);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("24");
    ui->lineEditPlot1LegendLabel->setText("Geometric DOP");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(8);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("27");
    ui->lineEditPlot2LegendLabel->setText("Horizontal DOP");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(8);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("28");
    ui->lineEditPlot3LegendLabel->setText("Vertical DOP");
    // Plot Nr. 4
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot4SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot4SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot4TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot4Condition->setCurrentIndex(8);
    ui->lineEditPlot4Xcolumn->setText("4");
    ui->lineEditPlot4Ycolumn->setText("26");
    ui->lineEditPlot4LegendLabel->setText("Time DOP");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Satellite Skyplot
void gLAB_GUI::on_pushButtonTemplateSatelliteSkyplot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Satellite Skyplot");
    this->on_checkBoxAutoLimits_clicked(false);
    ui->lineEditPlotXmin->setText("-1");
    ui->lineEditPlotXmax->setText("1");
    ui->lineEditPlotYmin->setText("-1");
    ui->lineEditPlotYmax->setText("1");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot1Condition->setCurrentIndex(5);
    ui->lineEditPlot1Xcolumn->setText("(math.sin($16*math.pi/180)*(90-$15)/90)");
    ui->lineEditPlot1Ycolumn->setText("(math.cos($16*math.pi/180)*(90-$15)/90)");
    ui->lineEditPlot1LegendLabel->setText("All PRN");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(3);
    ui->comboBoxPlot2ColorLine->setCurrentIndex(2);
    ui->comboBoxPlot2Condition->setCurrentIndex(5);
    ui->comboBoxPlot2ConditionPrn->setCurrentIndex(3);
    ui->lineEditPlot2Xcolumn->setText("(math.sin($16*math.pi/180)*(90-$15)/90)");
    ui->lineEditPlot2Ycolumn->setText("(math.cos($16*math.pi/180)*(90-$15)/90)");
    ui->lineEditPlot2LegendLabel->setText("PRN 3");
    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Carrier Phase Ambiguities Estimations
void gLAB_GUI::on_pushButtonTemplateCarrierPhaseAmbiguities_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Carrier Phase Ambiguities Estimations");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Ambiguities (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(6);
    ui->lineEditPlot1Condition->setText("($1==\"POSTFIT\") & ($7[0]==\"L\")");
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("13");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Measurement Multipath - Noise
void gLAB_GUI::on_pushButtonTemplateMeasurementMultipath_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Measurement Multipath - Noise");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Multipath");
    this->on_checkBoxAutoLimits_clicked(false);
    ui->lineEditPlotYmin->setText("-200");
    ui->lineEditPlotYmax->setText("200");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(1);
    ui->comboBoxPlot1ConditionPrn->setCurrentIndex(31);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("($8-$11-3.09*($11-$12))");
    ui->lineEditPlot1LegendLabel->setText("C1 Multipath");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(1);
    ui->comboBoxPlot2ConditionPrn->setCurrentIndex(31);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("( ( 154*154 ) * $9  - ( 120*120 )*$10 ) / ( ( 154*154 ) - ( 120*120 ) ) - ( ( 154*154 ) * $11 - ( 120*120 )*$12 ) / ( ( 154*154 ) - ( 120*120 ) )");
    ui->lineEditPlot2LegendLabel->setText("PC Multipath");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot3Condition->setCurrentIndex(1);
    ui->comboBoxPlot3ConditionPrn->setCurrentIndex(31);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("( 154 * $9 + 120 * $10 ) / ( 154 + 120 ) - ( 154 * $11  - 120 * $12 ) / ( 154 - 120 )");
    ui->lineEditPlot3LegendLabel->setText("MW Multipath");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Model Components
void gLAB_GUI::on_pushButtonTemplateModelComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Model Components");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Model (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(3);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("22");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Measurement Prefits vs Elevation
void gLAB_GUI::on_pushButtonTemplatePrefitResiduals_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Measurement Prefits vs Elevation");
    ui->lineEditPlotXLabel->setText("Elevation (degrees)");
    ui->lineEditPlotYLabel->setText("Prefits (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(5);
    ui->lineEditPlot1Condition->setText("($1==\"PREFIT\") & ($7[0]==\"P\")");
    ui->lineEditPlot1Xcolumn->setText("15");
    ui->lineEditPlot1Ycolumn->setText("8");
    ui->lineEditPlot1LegendLabel->setText("Pseudorange Prefit Residuals");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(5);
    ui->lineEditPlot2Condition->setText("($1==\"PREFIT\") & ($7[0]==\"L\")");
    ui->lineEditPlot2Xcolumn->setText("15");
    ui->lineEditPlot2Ycolumn->setText("8");
    ui->lineEditPlot2LegendLabel->setText("Carrier Phase Prefit Residuals");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Measurement Postfits vs Elevation
void gLAB_GUI::on_pushButtonTemplatePostfitResiduals_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Measurement Prefits vs Elevation");
    ui->lineEditPlotXLabel->setText("Elevation (degrees)");
    ui->lineEditPlotYLabel->setText("Postfits (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(6);
    ui->lineEditPlot1Condition->setText("($1==\"POSTFIT\") & ($7[0]==\"P\")");
    ui->lineEditPlot1Xcolumn->setText("11");
    ui->lineEditPlot1Ycolumn->setText("8");
    ui->lineEditPlot1LegendLabel->setText("Pseudorange Postfit Residuals");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(6);
    ui->lineEditPlot2Condition->setText("($1==\"POSTFIT\") & ($7[0]==\"L\")");
    ui->lineEditPlot2Xcolumn->setText("11");
    ui->lineEditPlot2Ycolumn->setText("8");
    ui->lineEditPlot2LegendLabel->setText("Carrier Phase Postfit Residuals");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Orbits and Clock Comparison
void gLAB_GUI::on_pushButtonTemplateOrbitAndClockComparison_clicked() {
    QFileInfo OutputFile(ui->lineEditOutputDestination->text());
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Orbits and Clock Comparison");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Discrepancy (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputFileCompare->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators((OutputFile.filePath() + "/diff.out")));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputFileCompare->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(9);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("11");
    ui->lineEditPlot1LegendLabel->setText("Radial");
    // Plot Nr. 2
    if ( ui->lineEditOutputFileCompare->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators((OutputFile.filePath() + "/diff.out")));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputFileCompare->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot2Condition->setCurrentIndex(9);
    ui->lineEditPlot2Xcolumn->setText("4");
    ui->lineEditPlot2Ycolumn->setText("12");
    ui->lineEditPlot2LegendLabel->setText("Along-Track");
    // Plot Nr. 3
    if ( ui->lineEditOutputFileCompare->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators((OutputFile.filePath() + "/diff.out")));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputFileCompare->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot3Condition->setCurrentIndex(9);
    ui->lineEditPlot3Xcolumn->setText("4");
    ui->lineEditPlot3Ycolumn->setText("13");
    ui->lineEditPlot3LegendLabel->setText("Cross-Track");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for DGNSS - Pseudorange Corrections
void gLAB_GUI::on_pushButtonTemplateDifferentialCorrections_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("DGNSS - Pseudorange Corrections");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("PRC (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(18);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("7");
    ui->lineEditPlot1LegendLabel->setText("All PRN");
    // Plot Nr. 2
    ui->comboBoxPlot2ColorLine->setCurrentIndex(1);    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for DGNSS - Sigma of the PRC
void gLAB_GUI::on_pushButtonTemplateSigmaPRC_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("DGNSS - Sigma of the PRC");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Sigma of PRC (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(18);
    ui->lineEditPlot1Xcolumn->setText("4");
    ui->lineEditPlot1Ycolumn->setText("13");
    ui->lineEditPlot1LegendLabel->setText("All PRN");
    // Plot Nr. 2
    ui->comboBoxPlot2ColorLine->setCurrentIndex(2);
    // Plot Nr. 3
    ui->comboBoxPlot3ColorLine->setCurrentIndex(1);
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for HPE and HPL
void gLAB_GUI::on_pushButtonTemplateHplHpeSat_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("HPE vs HPL #Sat");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("HPE/HPL (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(17);
    ui->lineEditPlot1Xcolumn->setText("6");
    ui->lineEditPlot1Ycolumn->setText("13");
    ui->lineEditPlot1LegendLabel->setText("HPE");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(17);
    ui->lineEditPlot2Xcolumn->setText("6");
    ui->lineEditPlot2Ycolumn->setText("14");
    ui->lineEditPlot2LegendLabel->setText("HPL");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(17);
    ui->lineEditPlot3Xcolumn->setText("6");
    ui->lineEditPlot3Ycolumn->setText("19");
    ui->lineEditPlot3LegendLabel->setText("NSAT");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for VPE and VPL
void gLAB_GUI::on_pushButtonTemplateVplVpeSat_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("VPE vs VPL #Sat");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("VPE/VPL (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(17);
    ui->lineEditPlot1Xcolumn->setText("6");
    ui->lineEditPlot1Ycolumn->setText("15");
    ui->lineEditPlot1LegendLabel->setText("VPE");
    // Plot Nr. 2
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot2SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot2SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot2TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot2Condition->setCurrentIndex(17);
    ui->lineEditPlot2Xcolumn->setText("6");
    ui->lineEditPlot2Ycolumn->setText("16");
    ui->lineEditPlot2LegendLabel->setText("VPL");
    // Plot Nr. 3
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot3SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot3SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot3TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot3Condition->setCurrentIndex(17);
    ui->lineEditPlot3Xcolumn->setText("6");
    ui->lineEditPlot3Ycolumn->setText("19");
    ui->lineEditPlot3LegendLabel->setText("NSAT");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Horizontal Stanford Plot
void gLAB_GUI::on_pushButtonHorStanfordPlot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Horizontal Stanford Plot");
    ui->lineEditPlotXLabel->setText("Horizontal Positioning Error (m)");
    ui->lineEditPlotYLabel->setText("Horizontal Protection Level (m)");
    //Show options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(false);

    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(17);
    ui->lineEditPlot1Xcolumn->setText("13");
    ui->lineEditPlot1Ycolumn->setText("14");

    //Disable options not available for Stanford-Plot
    ui->radioButtonPlotNr2->setDisabled(true);
    ui->radioButtonPlotNr3->setDisabled(true);
    ui->radioButtonPlotNr4->setDisabled(true);
    ui->comboBoxPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1ConditionOutput->setDisabled(true);
    ui->lineEditPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1TypeLine->setDisabled(true);
    ui->comboBoxPlot1ColorLine->setDisabled(true);
    ui->comboBoxPlot1Xsbasout->setDisabled(true);
    ui->lineEditPlot1Xcolumn->setDisabled(true);
    ui->lineEditPlot1Ycolumn->setDisabled(true);
    ui->lineEditPlot1LegendLabel->setDisabled(true);

    ui->lineEditFractionalText->setDisabled(true);
    ui->comboBoxLabelPosition->setDisabled(true);
    ui->lineEditPlotXmin->setDisabled(true);
    ui->lineEditPlotYmin->setDisabled(true);

    StanfordPlotSelected = 1;
    StanfordESAPlotSelected = 0;

    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Vertical Stanford Plot
void gLAB_GUI::on_pushButtonVerStanfordPlot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Vertical Stanford Plot");
    ui->lineEditPlotXLabel->setText("Vertical Positioning Error (m)");
    ui->lineEditPlotYLabel->setText("Vertical Protection Level (m)");
    //Show options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(false);

    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(17);
    ui->lineEditPlot1Xcolumn->setText("15");
    ui->lineEditPlot1Ycolumn->setText("16");

    //Disable options not available for Stanford-Plot
    ui->radioButtonPlotNr2->setDisabled(true);
    ui->radioButtonPlotNr3->setDisabled(true);
    ui->radioButtonPlotNr4->setDisabled(true);
    ui->comboBoxPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1ConditionOutput->setDisabled(true);
    ui->lineEditPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1TypeLine->setDisabled(true);
    ui->comboBoxPlot1ColorLine->setDisabled(true);
    ui->comboBoxPlot1Xsbasout->setDisabled(true);
    ui->lineEditPlot1Xcolumn->setDisabled(true);
    ui->lineEditPlot1Ycolumn->setDisabled(true);
    ui->lineEditPlot1LegendLabel->setDisabled(true);

    ui->lineEditFractionalText->setDisabled(true);
    ui->comboBoxLabelPosition->setDisabled(true);
    ui->lineEditPlotXmin->setDisabled(true);
    ui->lineEditPlotYmin->setDisabled(true);
    ui->lineEditPlot1SourceFile->setDisabled(false);

    StanfordPlotSelected = 1;
    StanfordESAPlotSelected = 0;

    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for Stanford-ESA Plot
void gLAB_GUI::on_pushButtonStanfordESAPlot_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("Stanford-ESA Plot");
    ui->lineEditPlotXLabel->setText("Positioning Error (m)");
    ui->lineEditPlotYLabel->setText("Protection Level (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputStanfordEsaPlot->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB_stfd-ESA_plot.txt"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputStanfordEsaPlot->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(1);
    ui->comboBoxPlot1Condition->setCurrentIndex(0);
    ui->lineEditPlot1Xcolumn->setText("");
    ui->lineEditPlot1Ycolumn->setText("");

    //Disable options not available for Stanford-Plot
    ui->radioButtonPlotNr2->setDisabled(true);
    ui->radioButtonPlotNr3->setDisabled(true);
    ui->radioButtonPlotNr4->setDisabled(true);
    ui->comboBoxPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1ConditionOutput->setDisabled(true);
    ui->lineEditPlot1Condition->setDisabled(true);
    ui->comboBoxPlot1TypeLine->setDisabled(true);
    ui->comboBoxPlot1ColorLine->setDisabled(true);
    ui->comboBoxPlot1Xsbasout->setDisabled(true);
    ui->lineEditPlot1Xcolumn->setDisabled(true);
    ui->lineEditPlot1Ycolumn->setDisabled(true);
    ui->lineEditPlot1LegendLabel->setDisabled(true);

    ui->lineEditFractionalText->setDisabled(true);
    ui->comboBoxLabelPosition->setDisabled(true);
    ui->checkBoxAutoLimits->setDisabled(true);
    ui->lineEditPlotXmin->setDisabled(true);
    ui->lineEditPlotYmin->setDisabled(true);
    ui->lineEditPlotXmax->setDisabled(true);
    ui->lineEditPlotYmax->setDisabled(true);
    ui->lineEditPlot1SourceFile->setDisabled(false);

    StanfordPlotSelected = 0;
    StanfordESAPlotSelected = 1;

    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for SBAS Model Components
void gLAB_GUI::on_pushButtonTemplateSBASModelComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("SBAS Model Components");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Model (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(13);
    ui->lineEditPlot1Xcolumn->setText("8");
    ui->lineEditPlot1Ycolumn->setText("23");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for SBAS Sigma Components
void gLAB_GUI::on_pushButtonTemplateSBASSigmaComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("SBAS Sigma Components");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Sigma (m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(14);
    ui->lineEditPlot1Xcolumn->setText("8");
    ui->lineEditPlot1Ycolumn->setText("12");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

// Template for SBAS Iono Components
void gLAB_GUI::on_pushButtonTemplateSBASIonoComponents_clicked() {
    // Global Graphic Configuration
    this->on_pushButtonPlotClear_clicked();
    ui->lineEditPlotTitle->setText("SBAS Iono Components");
    ui->lineEditPlotXLabel->setText("Time (s)");
    ui->lineEditPlotYLabel->setText("Value (L1 m)");
    //Hide options for Stanford-Plot percentiles
    ui->frameStfdPercentiles->setHidden(true);
    // Plot Nr. 1
    if ( ui->lineEditOutputDestination->text() == "" ) ui->lineEditPlot1SourceFile->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + "/gLAB.out"));
    else ui->lineEditPlot1SourceFile->setText(ui->lineEditOutputDestination->text());
    ui->comboBoxPlot1TypeLine->setCurrentIndex(8);
    ui->comboBoxPlot1Condition->setCurrentIndex(15);
    ui->lineEditPlot1Xcolumn->setText("8");
    ui->lineEditPlot1Ycolumn->setText("64");
    // Enable the plot button
    ui->pushButtonPlot->setEnabled(true);
}

///////////////// Start of Context menus (right-click menus) //////////////////
void gLAB_GUI::labelPlot1SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot1SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Plot 1 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot1SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot1SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot1SourceFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPlot1SourceFile->text() == "") {
            messageBox.warning(0, "Error","Plot 1 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot1SourceFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot1SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot1SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelPlot2SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot2SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Plot 2 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot2SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot2SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot2SourceFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPlot2SourceFile->text() == "") {
            messageBox.warning(0, "Error","Plot 2 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot2SourceFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot2SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot2SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelPlot3SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot3SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Plot 3 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot3SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot3SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot3SourceFile->text();
        #endif

        // Execute the program            
        if (ui->lineEditPlot3SourceFile->text() == "") {
            messageBox.warning(0, "Error","Plot 3 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot3SourceFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot3SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot3SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelPlot4SourceFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelPlot4SourceFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    myMenu.addAction("Open Plot 4 Source File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPlot4SourceFile->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPlot4SourceFile->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPlot4SourceFile->text();
        #endif

        // Execute the program
        if (ui->lineEditPlot4SourceFile->text() == "") {
            messageBox.warning(0, "Error","Plot 4 file is empty\n");
        } else if (this->fileExists(ui->lineEditPlot4SourceFile->text())==false) {
            messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot4SourceFile->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(0, "Errors found", "File '" + ui->lineEditPlot4SourceFile->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

void gLAB_GUI::getAnalysisOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    QString auxstring;

    int labelAdded=0;
    *errorString = "";
    *warningString="";
    *saveString = "";
    //// Global Graphic Parameters
    // Check if we have a stanford Plot
    if ( StanfordPlotSelected == 1 ) {
        *saveString += "--sf\n";
        *runString << "--sf";
    } else if ( StanfordESAPlotSelected == 1 ) {
        *saveString += "--sfesa\n";
        *runString << "--sfesa";
    }

    // Title
    if ( ui->lineEditPlotTitle->text() != "" ) {
        auxstring = ui->lineEditPlotTitle->text().replace("\\n","\n");
        *saveString += "-t \"" + ui->lineEditPlotTitle->text() + "\"\n";
        *runString << "-t" <<auxstring;
    }
    // X-label
    if ( ui->lineEditPlotXLabel->text() != "" ) {
        auxstring = ui->lineEditPlotXLabel->text().replace("\\n","\n");
        *saveString += "--xl \"" + ui->lineEditPlotXLabel->text() + "\"\n";
        *runString << "--xl" << auxstring;
    }
    // Y-label
    if ( ui->lineEditPlotYLabel->text() != "" ) {
        auxstring = ui->lineEditPlotYLabel->text().replace("\\n","\n");
        *saveString += "--yl \"" + ui->lineEditPlotYLabel->text() + "\"\n";
        *runString << "--yl" << auxstring;
    }
    // Axis limits
    if ( ui->checkBoxAutoLimits->isChecked() == false ) {
        if ( ui->lineEditPlotXmin->text() != "" && ui->lineEditPlotXmax->text() != "" ) {
            if ( ui->lineEditPlotXmin->text().toDouble()>=ui->lineEditPlotXmax->text().toDouble()) {
                *errorString += "X maximum value must be greater than the X minimum value\n";
            }
        }
        if ( ui->lineEditPlotYmin->text() != "" && ui->lineEditPlotYmax->text() != "" ) {
            if ( ui->lineEditPlotYmin->text().toDouble()>=ui->lineEditPlotYmax->text().toDouble()) {
                *errorString += "Y maximum value must be greater than the Y minimum value\n";
            }
        }
        if ( ui->lineEditPlotXmin->text() != "" ) {
            *saveString += "--xn " + ui->lineEditPlotXmin->text() + "\n";
            *runString << "--xn" << ui->lineEditPlotXmin->text();
        }
        if ( ui->lineEditPlotXmax->text() != "" ) {
            *saveString += "--xx " + ui->lineEditPlotXmax->text() + "\n";
            *runString << "--xx" << ui->lineEditPlotXmax->text();
        }
        if ( ui->lineEditPlotYmin->text() != "" ) {
            *saveString += "--yn " + ui->lineEditPlotYmin->text() + "\n";
            *runString << "--yn" << ui->lineEditPlotYmin->text();
        }
        if ( ui->lineEditPlotYmax->text() != "" ) {
            *saveString += "--yx " + ui->lineEditPlotYmax->text() + "\n";
            *runString << "--yx" << ui->lineEditPlotYmax->text();
        }
    }
    //Ticks limits
    if ( ui->checkBoxAutoTicks->isChecked() == false ) {
        if ( ui->lineEditXTickNum->text() != "" ) {
            if (ui->lineEditXTickNum->text().toDouble()==0) {
                *errorString += "X Ticks Step cannot be 0\n";
            }
            *saveString += "--xts " + ui->lineEditXTickNum->text() + "\n";
            *runString << "--xts" << ui->lineEditXTickNum->text();
        }
        if ( ui->lineEditYTickNum->text() != "" ) {
            if (ui->lineEditYTickNum->text().toDouble()==0) {
                *errorString += "Y Ticks Step cannot be 0\n";
            }
            *saveString += "--yts " + ui->lineEditYTickNum->text() + "\n";
            *runString << "--yts" << ui->lineEditYTickNum->text();
        }
    }
    //Positioning Error and Protection Level Percentiles for Stanford Plot
    if ( StanfordPlotSelected == 1 ) {
        if (ui->checkBoxPEPercentiles->isChecked()==true) {
            *saveString += "--percentileX\n";
            *runString << "--percentileX";
        }
        if (ui->checkBoxPLPercentiles->isChecked()==true) {
            *saveString += "--percentileY\n";
            *runString << "--percentileY";
        }
    }
    //Adjust to margin option
    if ( ui->checkBoxExpandFigureToMargin->isChecked()==true) {
        *saveString += "--atm\n";
        *runString << "--atm";
    }
    //Fractional text
    if ( ui->lineEditFractionalText->text() != "" ) {
        auxstring = ui->lineEditFractionalText->text().replace("\\n","\n");
        *saveString += "--ft \"" +  ui->lineEditFractionalText->text() +"\"\n";
        *runString << "--ft" << auxstring;
    }
    //WaterMark
    if ( ui->lineEditWaterMark->text() != "") {
         auxstring = ui->lineEditWaterMark->text().replace("\\n","\n");
         *saveString += "--wm  \"" +  ui->lineEditWaterMark->text() +"\"\n";
         *runString << "--wm" << auxstring;
    }


    //// End of Global Graphic Parameters

    // Plot Nr 1
    if ( ui->lineEditPlot1SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot1SourceFile->text() ) == false )
            *errorString += "PLOT 1: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot1SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot1SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot1Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot1Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot1Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot1Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot1Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot1Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 1: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot1Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot1Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot1Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 1: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot1Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot1Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot1LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot1LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot1LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot1TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot1ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }

    }

    // Plot Nr 2
    if ( ui->lineEditPlot2SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot2SourceFile->text() ) == false )
            *errorString += "PLOT 2: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot2SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot2SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot2Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot2Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot2Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot2Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot2Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot2Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 2: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot2Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot2Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot2Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 2: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot2Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot2Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot2LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot2LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot2LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot2TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot2ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }

    }

    // Plot Nr 3
    if ( ui->lineEditPlot3SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot3SourceFile->text() ) == false )
            *errorString += "PLOT 3: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot3SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot3SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot3Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot3Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot3Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot3Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot3Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot3Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 3: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot3Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot3Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot3Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 3: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot3Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot3Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot3LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot3LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot3LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot3TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot3ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }

    }

    // Plot Nr 4
    if ( ui->lineEditPlot4SourceFile->text() != "" ) {
        // Source File
        if ( this->fileExists( ui->lineEditPlot4SourceFile->text() ) == false )
            *errorString += "PLOT 4: Source File does not exist.\n";
        else {
            *saveString += "-f " + ui->lineEditPlot4SourceFile->text() +"\n";
            *runString << "-f" << ui->lineEditPlot4SourceFile->text();
        }
        // Condition(s)
        if ( ui->lineEditPlot4Condition->text() != "" ) {
            #ifdef Q_OS_WIN32
            *saveString += "-c \"" + ui->lineEditPlot4Condition->text().replace(QString("\""), QString("'")) +"\"\n";
            *runString << "-c" << ui->lineEditPlot4Condition->text().replace(QString("\""), QString("'"));
            #else
            *saveString += "-c '" + ui->lineEditPlot4Condition->text() +"'\n";
            *runString << "-c" << ui->lineEditPlot4Condition->text();
            #endif
        }
        // X Column
        if ( ui->lineEditPlot4Xcolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 4: X Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-x " + ui->lineEditPlot4Xcolumn->text() +"\n";
            *runString << "-x" << ui->lineEditPlot4Xcolumn->text();
        }
        // Y Column
        if ( ui->lineEditPlot4Ycolumn->text() == "" && StanfordESAPlotSelected == 0 )
            *errorString += "PLOT 4: Y Column empty.\n";
        else if ( StanfordESAPlotSelected == 0 ) {
            *saveString += "-y " + ui->lineEditPlot4Ycolumn->text() +"\n";
            *runString << "-y" << ui->lineEditPlot4Ycolumn->text();
        }
        // Legend-label
        if ( ui->lineEditPlot4LegendLabel->text() != "" ) {
            *saveString += "-l \"" + ui->lineEditPlot4LegendLabel->text() + "\"\n";
            *runString << "-l" << ui->lineEditPlot4LegendLabel->text();
            labelAdded=1;
        }
        // Type
        if (StanfordPlotSelected==0 && StanfordESAPlotSelected==0) {
            //Only set linetype and color line if Stanford/Stanford-ESA are not enabled
            switch ( ui->comboBoxPlot4TypeLine->currentIndex() ) {
                case 0 : {
                    *saveString += "-s -\n";
                    *runString << "-s" << "-";
                    break;
                }
                case 1 : {
                    *saveString += "-s .\n";
                    *runString << "-s" << ".";
                    break;
                }
                case 2 : {
                    *saveString += "-s --\n";
                    *runString << "-s" << "--";
                    break;
                }
                case 3 : {
                    *saveString += "-s o\n";
                    *runString << "-s" << "o";
                    break;
                }
                case 4 : {
                    *saveString += "-s s\n";
                    *runString << "-s" << "s";
                    break;
                }
                case 5 : {
                    *saveString += "-s p\n";
                    *runString << "-s" << "p";
                    break;
                }
                case 6 : {
                    *saveString += "-s +\n";
                    *runString << "-s" << "+";
                    break;
                }
                case 7 : {
                    *saveString += "-s x\n";
                    *runString << "-s" << "x";
                    break;
                }
                case 8 : {
                    *saveString += "-s .-\n";
                    *runString << "-s" << ".-";
                    break;
                }
            }
            // Color
            switch ( ui->comboBoxPlot4ColorLine->currentIndex() ) {
                case 0 : {
                    *saveString += "--cl b\n";
                    *runString << "--cl" << "b";
                    break;
                }
                case 1 : {
                    *saveString += "--cl g\n";
                    *runString << "--cl" << "g";
                    break;
                }
                case 2 : {
                    *saveString += "--cl r\n";
                    *runString << "--cl" << "r";
                    break;
                }
                case 3 : {
                    *saveString += "--cl c\n";
                    *runString << "--cl" << "c";
                    break;
                }
                case 4 : {
                    *saveString += "--cl m\n";
                    *runString << "--cl" << "m";
                    break;
                }
                case 5 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
                case 6 : {
                    *saveString += "--cl y\n";
                    *runString << "--cl" << "y";
                    break;
                }
            }
        }
    }

    // Set label position. This a global option, but only to be set if a label is given
    if ( labelAdded==1 ) {
        switch ( ui->comboBoxLabelPosition->currentIndex() ) {
            case 0: {
                *saveString += "--lp tr\n";
                *runString << "--lp" << "tr";
                break;
            }
            case 1: {
                *saveString += "--lp tc\n";
                *runString << "--lp" << "tc";
                break;
            }
            case 2: {
                *saveString += "--lp tl\n";
                *runString << "--lp" << "tl";
                break;
            }
            case 3: {
                *saveString += "--lp cr\n";
                *runString << "--lp" << "cr";
                break;
            }
            case 4: {
                *saveString += "--lp c\n";
                *runString << "--lp" << "c";
                break;
            }
            case 5: {
                *saveString += "--lp cl\n";
                *runString << "--lp" << "cl";
                break;
            }
            case 6: {
                *saveString += "--lp br\n";
                *runString << "--lp" << "br";
                break;
            }
            case 7: {
                *saveString += "--lp bc\n";
                *runString << "--lp" << "bc";
                break;
            }
            case 8: {
                *saveString += "--lp bl\n";
                *runString << "--lp" << "bl";
                break;
            }
        }
    }
}
