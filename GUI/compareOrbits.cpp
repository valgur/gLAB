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

//Function to show or hide start time
void gLAB_GUI::on_checkBoxStartTimeCompareOrbits_clicked(bool checked) {
    ui->frame_StartTimeCalendar_CompareOrbits->setHidden(!checked);
}

//Function to show or hide end time
void gLAB_GUI::on_checkBoxEndTimeCompareOrbits_clicked(bool checked) {
    ui->frame_EndTimeCalendar_CompareOrbits->setHidden(!checked);
}

// Function to show or hide the ANTEX input
void gLAB_GUI::on_checkBoxAntexCompareOrbitsFile2_clicked(bool checked) {
    ui->checkBoxAntexCompareOrbitsFile2->setChecked(checked);
    ui->frameAntexCompareOrbitsLineEditFile2->setHidden(!checked);
    if (checked==true && (ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true) && (ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true)) {
        ui->frameAntexWarningCompareOrbit->setHidden(false);
    } else {
        ui->frameAntexWarningCompareOrbit->setHidden(true);
    }
}

// Function for showing lineEdit for Navigation File 1
void gLAB_GUI::on_radioButtonOrbitNavCompareFile1_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile1->setCurrentIndex(0);
    ui->radioButtonOrbitNavCompareFile1->setChecked(true);
    ui->radioButtonOrbitPrecise1filesCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile1->setChecked(false);
    if(ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==false && ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==false ) {
         ui->groupBoxPreciseProductsInterpolationCompare->setHidden(true);
         ui->groupBoxAntexFileCompare->setHidden(true);
    }
    ui->frameAntexWarningCompareOrbit->setHidden(true);
    ui->groupBoxCompareNavMessageTypes->setHidden(false);
    if (ui->radioButtonOrbitNavCompareFile2->isChecked()){
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(1);
    } else {
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(0);
    }
    this->on_pushButtonCompareNavMessageTypesSetDefault_clicked();
}

// Function for showing lineEdit for SP3 File 1
void gLAB_GUI::on_radioButtonOrbitPrecise1filesCompareFile1_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile1->setCurrentIndex(1);
    ui->radioButtonOrbitNavCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile1->setChecked(true);
    ui->radioButtonOrbitPrecise2filesCompareFile1->setChecked(false);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    ui->groupBoxAntexFileCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
    if (ui->radioButtonOrbitNavCompareFile2->isChecked()){
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(0);
        this->on_pushButtonCompareNavMessageTypesSetDefault_clicked();
    } else {
        ui->groupBoxCompareNavMessageTypes->setHidden(true);
    }
}

// Function for showing lineEdit for SP3+CLK File 1
void gLAB_GUI::on_radioButtonOrbitPrecise2filesCompareFile1_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile1->setCurrentIndex(2);
    ui->radioButtonOrbitNavCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile1->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile1->setChecked(true);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    ui->groupBoxAntexFileCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
    if (ui->radioButtonOrbitNavCompareFile2->isChecked()){
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(0);
        this->on_pushButtonCompareNavMessageTypesSetDefault_clicked();
    } else {
        ui->groupBoxCompareNavMessageTypes->setHidden(true);
    }
}

// Function for showing lineEdit for Navigation File 2
void gLAB_GUI::on_radioButtonOrbitNavCompareFile2_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile2->setCurrentIndex(0);
    ui->radioButtonOrbitNavCompareFile2->setChecked(true);
    ui->radioButtonOrbitPrecise1filesCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile2->setChecked(false);
    ui->frameAntexWarningCompareOrbit->setHidden(true);
    if(ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==false && ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==false ) {
         ui->groupBoxPreciseProductsInterpolationCompare->setHidden(true);
         ui->groupBoxAntexFileCompare->setHidden(true);
    }
    ui->groupBoxCompareNavMessageTypes->setHidden(false);
    if (ui->radioButtonOrbitNavCompareFile1->isChecked()){
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(1);
    } else {
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(0);
    }
    this->on_pushButtonCompareNavMessageTypesSetDefault_clicked();
}

// Function for showing lineEdit for SP3 File 2
void gLAB_GUI::on_radioButtonOrbitPrecise1filesCompareFile2_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile2->setCurrentIndex(1);
    ui->radioButtonOrbitNavCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile2->setChecked(true);
    ui->radioButtonOrbitPrecise2filesCompareFile2->setChecked(false);
    ui->groupBoxAntexFileCompare->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
    if (ui->radioButtonOrbitNavCompareFile1->isChecked()){
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(0);
        this->on_pushButtonCompareNavMessageTypesSetDefault_clicked();
    } else {
        ui->groupBoxCompareNavMessageTypes->setHidden(true);
    }
}

// Function for showing lineEdit for SP3+CLK File 2
void gLAB_GUI::on_radioButtonOrbitPrecise2filesCompareFile2_clicked() {
    ui->stackedWidgetOrbitAndClockCompareFile2->setCurrentIndex(2);
    ui->radioButtonOrbitNavCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise1filesCompareFile2->setChecked(false);
    ui->radioButtonOrbitPrecise2filesCompareFile2->setChecked(true);
    ui->groupBoxAntexFileCompare->setHidden(false);
    ui->groupBoxPreciseProductsInterpolationCompare->setHidden(false);
    if (ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
        if (ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true || ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true) {
            ui->frameAntexWarningCompareOrbit->setHidden(false);
        }
    }
    if (ui->radioButtonOrbitNavCompareFile1->isChecked()){
        ui->stackedWidgetCompareNavMessageTypes->setCurrentIndex(0);
        this->on_pushButtonCompareNavMessageTypesSetDefault_clicked();
    } else {
        ui->groupBoxCompareNavMessageTypes->setHidden(true);
    }
}

//Function to show or hide concatenated SP3/CLK options
void gLAB_GUI::on_groupBoxConcatenedPreciseFilesCompare_clicked(bool checked) {
    ui->groupBoxConcatenedPreciseFilesCompare->setChecked(checked);
    ui->frameConcatenedPreciseFilesCompare->setHidden(!checked);
}

////////////////////// Push buttons /////////////////////
void gLAB_GUI::on_pushButtonRinexNavCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditNavCompareFile1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise1FileCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareSP3File1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise2FilesCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareOrbFile1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPreciseClkCompareFile1_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Clock Files (*.clk *.clk_30s *.clk_05s);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareClkFile1->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonRinexNavCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Broadcast Files (*.??n *.??g *.??l *.??p *.??h *n.rnx);;All Files (*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditNavCompareFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise1FileCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareSP3File2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPrecise2FilesCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Precise Files (*.sp3 *.eph);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareOrbFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonPreciseClkCompareFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("Clock Files (*.clk *.clk_30s *.clk_05s);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditPreciseFilesCompareClkFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

void gLAB_GUI::on_pushButtonAntexCompareOrbitsFile2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("ANTEX Files (*.atx);;All Files (*.*)"));
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditAntexCompareOrbitsFile2->setText(QDir::toNativeSeparators(fileName[0]));
            //If output file is empty, set a default value
            if (ui->lineEditOutputFileCompare->text() == "" ) {
                ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0].section("/",0,-2)+"/diff.out"));
            }
        }
    }
}

// Open dialog to set the output filename and path
void gLAB_GUI::on_pushButtonOutputFileCompare_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    //dialog.setAcceptMode(QFileDialog::AcceptSave); //This to confirm overwriting files
    dialog.setNameFilter(tr("gLAB Output Files (*.out);;All Files (*.*)"));
    dialog.selectFile(".out");
    QStringList fileName;
    if ( dialog.exec() ) {
        fileName = dialog.selectedFiles();
        if ( !fileName.isEmpty() ) {
            ui->lineEditOutputFileCompare->setText(QDir::toNativeSeparators(fileName[0]));
        }
    }
}

//Set all output messages button
void gLAB_GUI::on_pushButtonOrbitsCompareMessagesAll_clicked() {
    ui->checkBoxPrintInfoCompare->setChecked(true);
    ui->checkBoxPrintSatdiffCompare->setChecked(true);
    ui->checkBoxPrintSatstatCompare->setChecked(true);
    ui->checkBoxPrintSatstattotCompare->setChecked(true);
}

//Unset all output messages button
void gLAB_GUI::on_pushButtonOrbitsCompareMessagesNone_clicked() {
    ui->checkBoxPrintInfoCompare->setChecked(false);
    ui->checkBoxPrintSatdiffCompare->setChecked(false);
    ui->checkBoxPrintSatstatCompare->setChecked(false);
    ui->checkBoxPrintSatstattotCompare->setChecked(false);
}

//Navigation Message Types
void gLAB_GUI::command_2_CompareNavMessageTypes(QString const *navMessageTypesCmd,QString const *navMessageTypesOption,QString *warningString){
    if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==0) {
        //GPS
        if ( QString::compare(*navMessageTypesCmd, "-model:brdc:gps", Qt::CaseInsensitive)==0 ){
            if ( QString::compare(*navMessageTypesOption, "PreferLNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,GPS);
            } else if ( QString::compare(*navMessageTypesOption, "PreferCNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,GPS);
                //Move CNAV first
                ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGPS->item(0,1));
                this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGPS,1,0,0);
                ui->tableWidgetCompareNavMessageTypeGPS->clearSelection();
            } else {
                int typeOK=0;
                QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
                this->selectGNSS_CompareNavMessageTypes(0,GPS);
                for (int i=0; i<strNavMT.count(); i++){
                    int itemTab=0;
                    for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeGPS->columnCount(); itemTab++){
                        if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeGPS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetCompareNavMessageTypeGPS->item(0,itemTab)->background().color().name()==RedColor ) {
                            //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                            ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGPS->item(0,itemTab));
                            navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeGPS->item(0,itemTab));
                            typeOK++;
                            break;
                        }
                    }
                    if ( itemTab>=ui->tableWidgetCompareNavMessageTypeGPS->columnCount() ){
                        *warningString += "Parameter '-model:brdc:gps' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                    }
                }
                if ( typeOK<1 ){
                    *warningString += "Parameter '-model:brdc:gps' has no available value. It was set as Default.\n";
                    this->selectGNSS_CompareNavMessageTypes(1,GPS);
                }
            }

        //Galileo
        } else if ( QString::compare(*navMessageTypesCmd, "-model:brdc:gal", Qt::CaseInsensitive)==0 ){
            if ( QString::compare(*navMessageTypesOption, "PreferINAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,Galileo);
            } else if ( QString::compare(*navMessageTypesOption, "PreferFNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,Galileo);
                //Move FNAV first
                ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGalileo->item(0,3));
                this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGalileo,3,0,0);
                ui->tableWidgetCompareNavMessageTypeGalileo->clearSelection();
            } else if ( QString::compare(*navMessageTypesOption, "INAV", Qt::CaseInsensitive)==0 ){
                //INAV is INAVE1E5b, INAVE1, INAVE5b
                this->selectGNSS_CompareNavMessageTypes(1,Galileo);
                //Disable FNAV
                ui->tableWidgetCompareNavMessageTypeGalileo->item(0,3)->setBackgroundColor(RedColor);
            } else {
                int typeOK=0;
                QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
                this->selectGNSS_CompareNavMessageTypes(0,Galileo);
                for (int i=0; i<strNavMT.count(); i++){
                    int itemTab=0;
                    for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeGalileo->columnCount(); itemTab++){
                        if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeGalileo->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetCompareNavMessageTypeGalileo->item(0,itemTab)->background().color().name()==RedColor ) {
                            //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                            ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGalileo->item(0,itemTab));
                            navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeGalileo->item(0,itemTab));
                            typeOK++;
                            break;
                        }
                    }
                    if ( itemTab>=ui->tableWidgetCompareNavMessageTypeGalileo->columnCount() ) {
                        *warningString += "Parameter '-model:brdc:gal' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                    }
                }
                if ( typeOK<1 ){
                    *warningString += "Parameter '-model:brdc:gal' has no available value. It was set as Default.\n";
                    this->selectGNSS_CompareNavMessageTypes(1,Galileo);
                }
            }

        //BDS
        } else if ( QString::compare(*navMessageTypesCmd, "-model:brdc:bds", Qt::CaseInsensitive)==0 ){
            if ( QString::compare(*navMessageTypesOption, "PreferD1", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,BDS);
            } else {
                int typeOK=0;
                QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
                this->selectGNSS_CompareNavMessageTypes(0,BDS);
                for (int i=0; i<strNavMT.count(); i++){
                    int itemTab=0;
                    for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeBDS->columnCount(); itemTab++){
                        if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeBDS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetCompareNavMessageTypeBDS->item(0,itemTab)->background().color().name()==RedColor ) {
                            //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                            ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(ui->tableWidgetCompareNavMessageTypeBDS->item(0,itemTab));
                            navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeBDS->item(0,itemTab));
                            typeOK++;
                            break;
                        }
                    }
                    if ( itemTab>=ui->tableWidgetCompareNavMessageTypeBDS->columnCount() ){
                        *warningString += "Parameter '-model:brdc:bds' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                    }
                }
                if ( typeOK<1 ){
                    *warningString += "Parameter '-model:brdc:bds' has no available value. It was set as Default.\n";
                    this->selectGNSS_CompareNavMessageTypes(1,BDS);
                }
            }

        //QZSS
        } else if ( QString::compare(*navMessageTypesCmd, "-model:brdc:qzss", Qt::CaseInsensitive)==0 || QString::compare(*navMessageTypesCmd, "-model:brdc:qzs", Qt::CaseInsensitive)==0 ){
            if ( QString::compare(*navMessageTypesOption, "PreferLNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,QZSS);
            } else {
                int typeOK=0;
                QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
                this->selectGNSS_CompareNavMessageTypes(0,QZSS);
                for (int i=0; i<strNavMT.count(); i++){
                    int itemTab=0;
                    for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeQZSS->columnCount(); itemTab++){
                        if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeQZSS->item(0,itemTab)->text(), Qt::CaseInsensitive)==0 && ui->tableWidgetCompareNavMessageTypeQZSS->item(0,itemTab)->background().color().name()==RedColor ) {
                            //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                            ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(ui->tableWidgetCompareNavMessageTypeQZSS->item(0,itemTab));
                            navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeQZSS->item(0,itemTab));
                            typeOK++;
                            break;
                        }
                    }
                    if ( itemTab>=ui->tableWidgetCompareNavMessageTypeQZSS->columnCount() ){
                        *warningString += "Parameter '" + *navMessageTypesCmd + "' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                    }
                }
                if ( typeOK<1 ){
                    *warningString += "Parameter '" + *navMessageTypesCmd + "' has no available value. It was set as Default.\n";
                    this->selectGNSS_CompareNavMessageTypes(1,QZSS);
                }
            }
        }

    } else if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==1){
        //GPS
        if ( QString::compare(*navMessageTypesCmd, "-model:brdc:gps", Qt::CaseInsensitive)==0 ){
            if ( QString::compare(*navMessageTypesOption, "PreferLNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,GPS);
                //Disable "vs" slots
                int numColumn=ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount();
                for(int i=(numColumn-NUMGPSVSNAVTYPES);i<numColumn;i++) {
                    ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setBackgroundColor(RedColor);
                }
            } else if ( QString::compare(*navMessageTypesOption, "PreferCNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,GPS);
                //Move CNAV first
                ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,1));
                this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGPS_2,1,0,0);
                ui->tableWidgetCompareNavMessageTypeGPS_2->clearSelection();
                //Disable "vs" slots
                int numColumn=ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount();
                for(int i=(numColumn-NUMGPSVSNAVTYPES);i<numColumn;i++) {
                    ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setBackgroundColor(RedColor);
                }
            } else {
                int typeOK=0;
                QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
                this->selectGNSS_CompareNavMessageTypes(0,GPS);
                for (int i=0; i<strNavMT.count(); i++){
                    int itemTab=0;
                    for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount(); itemTab++){
                        if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,itemTab)->text().replace(" ",""), Qt::CaseInsensitive)==0 && ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,itemTab)->background().color().name()==RedColor ) {
                            //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                            ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,itemTab));
                            navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,itemTab));
                            typeOK++;
                            break;
                        }
                    }
                    if ( itemTab>=ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount() ){
                        *warningString += "Parameter '-model:brdc:gps' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                    }
                }
                if ( typeOK<1 ){
                    *warningString += "Parameter '-model:brdc:gps' has no available value. It was set as Default.\n";
                    this->selectGNSS_CompareNavMessageTypes(1,GPS);
                }
            }
        //Galileo
        } else if ( QString::compare(*navMessageTypesCmd, "-model:brdc:gal", Qt::CaseInsensitive)==0 ) {
            if ( QString::compare(*navMessageTypesOption, "PreferINAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,Galileo);
                //Disable "vs" slots
                int numColumn=ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount();
                for(int i=(numColumn-NUMGALVSNAVTYPES);i<numColumn;i++) {
                    ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setBackgroundColor(RedColor);
                }
            } else if ( QString::compare(*navMessageTypesOption, "PreferFNAV", Qt::CaseInsensitive)==0 ){
                this->selectGNSS_CompareNavMessageTypes(1,Galileo);
                //Move FNAV first
                ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,3));
                this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGalileo_2,3,0,0);
                ui->tableWidgetCompareNavMessageTypeGalileo_2->clearSelection();
                //Disable "vs" slots
                int numColumn=ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount();
                for(int i=(numColumn-NUMGALVSNAVTYPES);i<numColumn;i++) {
                    ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setBackgroundColor(RedColor);
                }
            } else if ( QString::compare(*navMessageTypesOption, "INAV", Qt::CaseInsensitive)==0 ){
                //INAV is INAVE1E5b, INAVE1, INAVE5b
                this->selectGNSS_CompareNavMessageTypes(1,Galileo);
                //Disable FNAV
                ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,3)->setBackgroundColor(RedColor);
                //Disable "vs" slots
                int numColumn=ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount();
                for(int i=(numColumn-NUMGALVSNAVTYPES);i<numColumn;i++) {
                    ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setBackgroundColor(RedColor);
                }
            } else {
                int typeOK=0;
                QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
                this->selectGNSS_CompareNavMessageTypes(0,Galileo);
                for (int i=0; i<strNavMT.count(); i++){
                    int itemTab=0;
                    for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount(); itemTab++){
                        if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,itemTab)->text().replace(" ",""), Qt::CaseInsensitive)==0
                             && ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,itemTab)->background().color().name()==RedColor ) {
                            //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                            ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,itemTab));
                            navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,itemTab));
                            typeOK++;
                            break;
                        }
                    }
                    if ( itemTab>=ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount() ){
                        *warningString += "Parameter '-model:brdc:gal' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                    }
                }
                if ( typeOK<1 ){
                    *warningString += "Parameter '-model:brdc:gal' has no available value. It was set as Default.\n";
                    this->selectGNSS_CompareNavMessageTypes(1,Galileo);
                }
            }
        //BDS
        } else if ( QString::compare(*navMessageTypesCmd, "-model:brdc:bds", Qt::CaseInsensitive)==0 ){
            int typeOK=0;
            QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
            this->selectGNSS_CompareNavMessageTypes(0,BDS);
            for (int i=0; i<strNavMT.count(); i++){
                int itemTab=0;
                for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeBDS_2->columnCount(); itemTab++){
                    if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,itemTab)->text().replace(" ",""), Qt::CaseInsensitive)==0
                         && ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,itemTab)->background().color().name()==RedColor ) {
                        //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                        ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,itemTab));
                        navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,itemTab));
                        typeOK++;
                        break;
                    }
                }
                if ( itemTab>=ui->tableWidgetCompareNavMessageTypeBDS_2->columnCount() ){
                    *warningString += "Parameter '-model:brdc:bds' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                }
            }
            if ( typeOK<1 ){
                *warningString += "Parameter '-model:brdc:bds' has no available value. It was set as Default.\n";
                this->selectGNSS_CompareNavMessageTypes(1,BDS);
            }

        //QZSS
        } else if ( QString::compare(*navMessageTypesCmd, "-model:brdc:qzss", Qt::CaseInsensitive)==0 || QString::compare(*navMessageTypesCmd, "-model:brdc:qzs", Qt::CaseInsensitive)==0 ){
            int typeOK=0;
            QStringList strNavMT=navMessageTypesOption->split(",", QString::SkipEmptyParts);
            this->selectGNSS_CompareNavMessageTypes(0,QZSS);
            for (int i=0; i<strNavMT.count(); i++){
                int itemTab=0;
                for (itemTab=0; itemTab<ui->tableWidgetCompareNavMessageTypeQZSS_2->columnCount(); itemTab++){
                    if ( QString::compare(strNavMT[i], ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,itemTab)->text().replace(" ",""), Qt::CaseInsensitive)==0 && ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,itemTab)->background().color().name()==RedColor ) {
                        //Select item to be moved (this is necessary otherwise navMessageTypesItem_doubleClicked function does not move the item)
                        ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,itemTab));
                        navMessageTypesItem_doubleClicked(ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,itemTab));
                        typeOK++;
                        break;
                    }
                }
                if ( itemTab>=ui->tableWidgetCompareNavMessageTypeQZSS_2->columnCount() ){
                    *warningString += "Parameter '" + *navMessageTypesCmd + "' has unknown type '" + strNavMT[i] +"'. It was skipped.\n";
                }
            }
            if ( typeOK<1 ){
                *warningString += "Parameter '" + *navMessageTypesCmd + "' has no available value. It was set as Default.\n";
                this->selectGNSS_CompareNavMessageTypes(1,QZSS);
            }
        }
    }
}
void gLAB_GUI::selectGNSS_CompareNavMessageTypes(int selectFlag,int iGNSS){
    if (selectFlag>0){
        //GPS
        if (iGNSS==GPS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->setText(CompareNavMT[GPS][0][i]);
            ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->setBackground(gnssSelected);
        }
        //Galileo
        if (iGNSS==Galileo) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->setText(CompareNavMT[Galileo][0][i]);
            ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->setBackground(gnssSelected);
        }
        //GLONASS
        if (iGNSS==GLONASS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->setText(CompareNavMT[GLONASS][0][i]);
            ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->setBackground(gnssSelected);
        }
        //GEO
        if (iGNSS==GEO) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->setText(CompareNavMT[GEO][0][i]);
            ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->setBackground(gnssSelected);
        }
        //BDS
        if (iGNSS==BDS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->setText(CompareNavMT[BDS][0][i]);
            ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->setBackground(gnssSelected);
        }
        //QZSS
        if (iGNSS==QZSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->setText(CompareNavMT[QZSS][0][i]);
            ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->setBackground(gnssSelected);
        }
        //IRNSS
        if (iGNSS==IRNSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->setText(CompareNavMT[IRNSS][0][i]);
            ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->setBackground(gnssSelected);
        }
        //GPS
        if (iGNSS==GPS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setText(CompareNavMT[GPS][1][i]);
            ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setBackground(gnssSelected);
        }
        //Galileo
        if (iGNSS==Galileo) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setText(CompareNavMT[Galileo][1][i]);
            ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setBackground(gnssSelected);
        }
        //GLONASS
        if (iGNSS==GLONASS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->setText(CompareNavMT[GLONASS][1][i]);
            ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->setBackground(gnssSelected);
        }
        //GEO
        if (iGNSS==GEO) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->setText(CompareNavMT[GEO][1][i]);
            ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->setBackground(gnssSelected);
        }
        //BDS
        if (iGNSS==BDS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->setText(CompareNavMT[BDS][1][i]);
            ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->setBackground(gnssSelected);
        }
        //QZSS
        if (iGNSS==QZSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->setText(CompareNavMT[QZSS][1][i]);
            ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->setBackground(gnssSelected);
        }
        //IRNSS
        if (iGNSS==IRNSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->setText(CompareNavMT[IRNSS][1][i]);
            ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->setBackground(gnssSelected);
        }
    } else {
        //GPS
        if (iGNSS==GPS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->setText(CompareNavMT[GPS][0][i]);
            ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->setBackground(gnssUnSelected);
        }
        //Galileo
        if (iGNSS==Galileo) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->setText(CompareNavMT[Galileo][0][i]);
            ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->setBackground(gnssUnSelected);
        }
        //GLONASS
        if (iGNSS==GLONASS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->setText(CompareNavMT[GLONASS][0][i]);
            ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->setBackground(gnssUnSelected);
        }
        //GEO
        if (iGNSS==GEO) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->setText(CompareNavMT[GEO][0][i]);
            ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->setBackground(gnssUnSelected);
        }
        //BDS
        if (iGNSS==BDS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->setText(CompareNavMT[BDS][0][i]);
            ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->setBackground(gnssUnSelected);
        }
        //QZSS
        if (iGNSS==QZSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->setText(CompareNavMT[QZSS][0][i]);
            ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->setBackground(gnssUnSelected);
        }
        //IRNSS
        if (iGNSS==IRNSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->setText(CompareNavMT[IRNSS][0][i]);
            ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->setBackground(gnssUnSelected);
        }
        //GPS
        if (iGNSS==GPS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setText(CompareNavMT[GPS][1][i]);
            ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setBackground(gnssUnSelected);
        }
        //Galileo
        if (iGNSS==Galileo) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setText(CompareNavMT[Galileo][1][i]);
            ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setBackground(gnssUnSelected);
        }
        //GLONASS
        if (iGNSS==GLONASS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->setText(CompareNavMT[GLONASS][1][i]);
            ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->setBackground(gnssUnSelected);
        }
        //GEO
        if (iGNSS==GEO) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->setText(CompareNavMT[GEO][1][i]);
            ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->setBackground(gnssUnSelected);
        }
        //BDS
        if (iGNSS==BDS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->setText(CompareNavMT[BDS][1][i]);
            ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->setBackground(gnssUnSelected);
        }
        //QZSS
        if (iGNSS==QZSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->setText(CompareNavMT[QZSS][1][i]);
            ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->setBackground(gnssUnSelected);
        }
        //IRNSS
        if (iGNSS==IRNSS) for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->setText(CompareNavMT[IRNSS][1][i]);
            ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->setBackground(gnssUnSelected);
        }
    }
}
void gLAB_GUI::on_pushButtonCompareNavMessageTypesSetDefault_clicked(){
    if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==0){
        //GPS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->setText(CompareNavMT[GPS][0][i]);
            ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->setBackground(gnssSelected);
        }
        //Galileo
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->setText(CompareNavMT[Galileo][0][i]);
            ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->setBackground(gnssSelected);
        }
        //GLONASS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->setText(CompareNavMT[GLONASS][0][i]);
            ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->setBackground(gnssSelected);
        }
        //GEO
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->setText(CompareNavMT[GEO][0][i]);
            ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->setBackground(gnssSelected);
        }
        //BDS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->setText(CompareNavMT[BDS][0][i]);
            ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->setBackground(gnssSelected);
        }
        //QZSS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->setText(CompareNavMT[QZSS][0][i]);
            ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->setBackground(gnssSelected);
        }
        //IRNSS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->setText(CompareNavMT[IRNSS][0][i]);
            ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->setBackground(gnssSelected);
        }

        on_checkBoxCompareNavMessageTypeGPS_clicked(true);
        on_checkBoxCompareNavMessageTypeGalileo_clicked(true);
        on_checkBoxCompareNavMessageTypeGLONASS_clicked(true);
        on_checkBoxCompareNavMessageTypeGEO_clicked(true);
        on_checkBoxCompareNavMessageTypeBDS_clicked(true);
        on_checkBoxCompareNavMessageTypeQZSS_clicked(true);
        on_checkBoxCompareNavMessageTypeIRNSS_clicked(true);
        ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
        ui->lineEditCompareNavFreshTime->setText(DEFAULT_PREFERRED_NAV_TIME);
    } else if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==1){
        //GPS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setText(CompareNavMT[GPS][1][i]);
            if (CompareNavMT[GPS][1][i].contains("vs",Qt::CaseSensitive)) ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setBackground(gnssUnSelected);
            else ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->setBackground(gnssSelected);
        }
        //Galileo
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setText(CompareNavMT[Galileo][1][i]);
            if (CompareNavMT[Galileo][1][i].contains("vs",Qt::CaseSensitive)) ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setBackground(gnssUnSelected);
            else ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->setBackground(gnssSelected);
        }
        //GLONASS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->setText(CompareNavMT[GLONASS][1][i]);
            if (CompareNavMT[GLONASS][1][i].contains("vs",Qt::CaseSensitive)) ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->setBackground(gnssUnSelected);
            else ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->setBackground(gnssSelected);
        }
        //GEO
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->setText(CompareNavMT[GEO][1][i]);
            if (CompareNavMT[GEO][1][i].contains("vs",Qt::CaseSensitive)) ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->setBackground(gnssUnSelected);
            else ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->setBackground(gnssSelected);
        }
        //BDS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->setText(CompareNavMT[BDS][1][i]);
            if (CompareNavMT[BDS][1][i].contains("vs",Qt::CaseSensitive)) ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->setBackground(gnssUnSelected);
            else ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->setBackground(gnssSelected);
        }
        //QZSS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->setText(CompareNavMT[QZSS][1][i]);
            if (CompareNavMT[QZSS][1][i].contains("vs",Qt::CaseSensitive)) ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->setBackground(gnssUnSelected);
            else ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->setBackground(gnssSelected);
        }
        //IRNSS
        for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS_2->columnCount();i++){
            ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->setText(CompareNavMT[IRNSS][1][i]);
            if (CompareNavMT[IRNSS][1][i].contains("vs",Qt::CaseSensitive)) ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->setBackground(gnssUnSelected);
            else ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->setBackground(gnssSelected);
        }
        on_checkBoxCompareNavMessageTypeGPS_2_clicked(true);
        on_checkBoxCompareNavMessageTypeGalileo_2_clicked(true);
        on_checkBoxCompareNavMessageTypeGLONASS_2_clicked(true);
        on_checkBoxCompareNavMessageTypeGEO_2_clicked(true);
        on_checkBoxCompareNavMessageTypeBDS_2_clicked(true);
        on_checkBoxCompareNavMessageTypeQZSS_2_clicked(true);
        on_checkBoxCompareNavMessageTypeIRNSS_2_clicked(true);
        ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
        ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
    }
}
void gLAB_GUI::on_pushButtonCompareNavMessageTypesBoost_clicked(){
    if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==0){
        //GPS
        if (ui->tableWidgetCompareNavMessageTypeGPS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGPS,ui->tableWidgetCompareNavMessageTypeGPS->currentColumn(),ui->tableWidgetCompareNavMessageTypeGPS->currentColumn()-1,0);
        }
        //Galileo
        if (ui->tableWidgetCompareNavMessageTypeGalileo->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGalileo,ui->tableWidgetCompareNavMessageTypeGalileo->currentColumn(),ui->tableWidgetCompareNavMessageTypeGalileo->currentColumn()-1,0);
        }
        //GLONASS
        if (ui->tableWidgetCompareNavMessageTypeGLONASS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGLONASS,ui->tableWidgetCompareNavMessageTypeGLONASS->currentColumn(),ui->tableWidgetCompareNavMessageTypeGLONASS->currentColumn()-1,0);
        }
        //GEO
        if (ui->tableWidgetCompareNavMessageTypeGEO->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGEO,ui->tableWidgetCompareNavMessageTypeGEO->currentColumn(),ui->tableWidgetCompareNavMessageTypeGEO->currentColumn()-1,0);
        }
        //BDS
        if (ui->tableWidgetCompareNavMessageTypeBDS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeBDS,ui->tableWidgetCompareNavMessageTypeBDS->currentColumn(),ui->tableWidgetCompareNavMessageTypeBDS->currentColumn()-1,0);
        }
        //QZSS
        if (ui->tableWidgetCompareNavMessageTypeQZSS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeQZSS,ui->tableWidgetCompareNavMessageTypeQZSS->currentColumn(),ui->tableWidgetCompareNavMessageTypeQZSS->currentColumn()-1,0);
        }
        //IRNSS
        if (ui->tableWidgetCompareNavMessageTypeIRNSS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeIRNSS,ui->tableWidgetCompareNavMessageTypeIRNSS->currentColumn(),ui->tableWidgetCompareNavMessageTypeIRNSS->currentColumn()-1,0);
        }
    } else if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==1){
        //GPS
        if (ui->tableWidgetCompareNavMessageTypeGPS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGPS_2,ui->tableWidgetCompareNavMessageTypeGPS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGPS_2->currentColumn()-1,0);
        }
        //Galileo
        if (ui->tableWidgetCompareNavMessageTypeGalileo_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGalileo_2,ui->tableWidgetCompareNavMessageTypeGalileo_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGalileo_2->currentColumn()-1,0);
        }
        //GLONASS
        if (ui->tableWidgetCompareNavMessageTypeGLONASS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGLONASS_2,ui->tableWidgetCompareNavMessageTypeGLONASS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGLONASS_2->currentColumn()-1,0);
        }
        //GEO
        if (ui->tableWidgetCompareNavMessageTypeGEO_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGEO_2,ui->tableWidgetCompareNavMessageTypeGEO_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGEO_2->currentColumn()-1,0);
        }
        //BDS
        if (ui->tableWidgetCompareNavMessageTypeBDS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeBDS_2,ui->tableWidgetCompareNavMessageTypeBDS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeBDS_2->currentColumn()-1,0);
        }
        //QZSS
        if (ui->tableWidgetCompareNavMessageTypeQZSS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeQZSS_2,ui->tableWidgetCompareNavMessageTypeQZSS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeQZSS_2->currentColumn()-1,0);
        }
        //IRNSS
        if (ui->tableWidgetCompareNavMessageTypeIRNSS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeIRNSS_2,ui->tableWidgetCompareNavMessageTypeIRNSS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeIRNSS_2->currentColumn()-1,0);
        }
    }
}
void gLAB_GUI::on_pushButtonCompareNavMessageTypesLower_clicked(){
    if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==0){
        //GPS
        if (ui->tableWidgetCompareNavMessageTypeGPS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGPS,ui->tableWidgetCompareNavMessageTypeGPS->currentColumn(),ui->tableWidgetCompareNavMessageTypeGPS->currentColumn()+1,0);
        }
        //Galileo
        if (ui->tableWidgetCompareNavMessageTypeGalileo->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGalileo,ui->tableWidgetCompareNavMessageTypeGalileo->currentColumn(),ui->tableWidgetCompareNavMessageTypeGalileo->currentColumn()+1,0);
        }
        //GLONASS
        if (ui->tableWidgetCompareNavMessageTypeGLONASS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGLONASS,ui->tableWidgetCompareNavMessageTypeGLONASS->currentColumn(),ui->tableWidgetCompareNavMessageTypeGLONASS->currentColumn()+1,0);
        }
        //GEO
        if (ui->tableWidgetCompareNavMessageTypeGEO->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGEO,ui->tableWidgetCompareNavMessageTypeGEO->currentColumn(),ui->tableWidgetCompareNavMessageTypeGEO->currentColumn()+1,0);
        }
        //BDS
        if (ui->tableWidgetCompareNavMessageTypeBDS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeBDS,ui->tableWidgetCompareNavMessageTypeBDS->currentColumn(),ui->tableWidgetCompareNavMessageTypeBDS->currentColumn()+1,0);
        }
        //QZSS
        if (ui->tableWidgetCompareNavMessageTypeQZSS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeQZSS,ui->tableWidgetCompareNavMessageTypeQZSS->currentColumn(),ui->tableWidgetCompareNavMessageTypeQZSS->currentColumn()+1,0);
        }
        //IRNSS
        if (ui->tableWidgetCompareNavMessageTypeIRNSS->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeIRNSS,ui->tableWidgetCompareNavMessageTypeIRNSS->currentColumn(),ui->tableWidgetCompareNavMessageTypeIRNSS->currentColumn()+1,0);
        }
    } else if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==1){
        //GPS
        if (ui->tableWidgetCompareNavMessageTypeGPS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGPS_2,ui->tableWidgetCompareNavMessageTypeGPS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGPS_2->currentColumn()+1,0);
        }
        //Galileo
        if (ui->tableWidgetCompareNavMessageTypeGalileo_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGalileo_2,ui->tableWidgetCompareNavMessageTypeGalileo_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGalileo_2->currentColumn()+1,0);
        }
        //GLONASS
        if (ui->tableWidgetCompareNavMessageTypeGLONASS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGLONASS_2,ui->tableWidgetCompareNavMessageTypeGLONASS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGLONASS_2->currentColumn()+1,0);
        }
        //GEO
        if (ui->tableWidgetCompareNavMessageTypeGEO_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeGEO_2,ui->tableWidgetCompareNavMessageTypeGEO_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeGEO_2->currentColumn()+1,0);
        }
        //BDS
        if (ui->tableWidgetCompareNavMessageTypeBDS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeBDS_2,ui->tableWidgetCompareNavMessageTypeBDS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeBDS_2->currentColumn()+1,0);
        }
        //QZSS
        if (ui->tableWidgetCompareNavMessageTypeQZSS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeQZSS_2,ui->tableWidgetCompareNavMessageTypeQZSS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeQZSS_2->currentColumn()+1,0);
        }
        //IRNSS
        if (ui->tableWidgetCompareNavMessageTypeIRNSS_2->currentColumn()>=0){
            this->moveNavMessageTypesColumn(ui->tableWidgetCompareNavMessageTypeIRNSS_2,ui->tableWidgetCompareNavMessageTypeIRNSS_2->currentColumn(),ui->tableWidgetCompareNavMessageTypeIRNSS_2->currentColumn()+1,0);
        }
    }
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGPS_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGPS->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGPS->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGPS->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGLONASS_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGLONASS->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGLONASS->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGLONASS->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGalileo_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGalileo->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGalileo->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGalileo->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGEO_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGEO->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGEO->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGEO->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeBDS_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeBDS->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeBDS->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeBDS->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeQZSS_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeQZSS->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeQZSS->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeQZSS->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeIRNSS_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeIRNSS->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeIRNSS->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeIRNSS->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGPS_2_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGPS_2->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGPS_2->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGPS_2->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGLONASS_2_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGLONASS_2->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGLONASS_2->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGLONASS_2->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGalileo_2_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGalileo_2->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGalileo_2->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGalileo_2->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeGEO_2_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeGEO_2->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeGEO_2->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeGEO_2->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeBDS_2_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeBDS_2->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeBDS_2->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeBDS_2->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeQZSS_2_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeQZSS_2->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeQZSS_2->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeQZSS_2->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_checkBoxCompareNavMessageTypeIRNSS_2_clicked(bool checked){
    ui->checkBoxCompareNavMessageTypeIRNSS_2->setChecked(checked);
    if (checked==true) ui->tableWidgetCompareNavMessageTypeIRNSS_2->setHidden(false);
    else ui->tableWidgetCompareNavMessageTypeIRNSS_2->setHidden(true);
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGPS_clicked(){
    ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGalileo_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGLONASS_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGEO_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeBDS_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeQZSS_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeIRNSS_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGPS_2_clicked(){
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGalileo_2_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGLONASS_2_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeGEO_2_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeBDS_2_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeQZSS_2_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeIRNSS_2->setCurrentItem(nullptr);
}
void gLAB_GUI::on_tableWidgetCompareNavMessageTypeIRNSS_2_clicked(){
    ui->tableWidgetCompareNavMessageTypeGPS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGalileo_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGLONASS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeGEO_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeBDS_2->setCurrentItem(nullptr);
    ui->tableWidgetCompareNavMessageTypeQZSS_2->setCurrentItem(nullptr);
}
////////////////// End of Push buttons //////////////////

///////////////// Start of Context menus (right-click menus) //////////////////
void gLAB_GUI::labelCompareRinexNavFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareRinexNavFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditNavCompareFile1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditNavCompareFile1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditNavCompareFile1->text();
        #endif

        // Execute the program
        if (ui->lineEditNavCompareFile1->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 1 is empty\n");
        } else if (this->fileExists(ui->lineEditNavCompareFile1->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditNavCompareFile1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditNavCompareFile1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
void gLAB_GUI::labelCompareSP3OrbitsClocksFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsClocksFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open SP3 File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareSP3File1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareSP3File1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareSP3File1->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareSP3File1->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file 1 is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesCompareSP3File1->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareSP3OrbitsFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open SP3 File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareOrbFile1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareOrbFile1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareOrbFile1->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareOrbFile1->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file 1 is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesCompareOrbFile1->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareClockFile1Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareClockFile1->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Clock File 1");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareClkFile1->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareClkFile1->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareClkFile1->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareClkFile1->text() == "") {
            messageBox.warning(nullptr, "Error","Clock file 1 is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesCompareClkFile1->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile1->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile1->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareRinexNavFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareRinexNavFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open RINEX Navigation File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditNavCompareFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditNavCompareFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditNavCompareFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditNavCompareFile2->text() == "") {
            messageBox.warning(nullptr, "Error","RINEX Navigation file 2 is empty\n");
        } else if (this->fileExists(ui->lineEditNavCompareFile2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditNavCompareFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditNavCompareFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareSP3OrbitsClocksFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsClocksFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open SP3 File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareSP3File2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareSP3File2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareSP3File2->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareSP3File2->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file 2 is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesCompareSP3File2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareSP3File2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareSP3OrbitsFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareSP3OrbitsFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open SP3 File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareOrbFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareOrbFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareOrbFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareOrbFile2->text() == "") {
            messageBox.warning(nullptr, "Error","SP3 file 2 is empty\n");
        } else if (this->fileExists(ui->lineEditPreciseFilesCompareOrbFile2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareOrbFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareClockFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareClockFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Clock File 2");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditPreciseFilesCompareClkFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditPreciseFilesCompareClkFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditPreciseFilesCompareClkFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditPreciseFilesCompareClkFile2->text() == "") {
            messageBox.warning(nullptr, "Error","Clock file 2 is empty\n");
        } else if  (this->fileExists(ui->lineEditPreciseFilesCompareClkFile2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditPreciseFilesCompareClkFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::checkBoxAntexCompareOrbitsFile2Menu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->checkBoxAntexCompareOrbitsFile2->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open ANTEX File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditAntexCompareOrbitsFile2->text();
        #elif defined(Q_OS_WIN32)
            QString programFilesPath(getenv("PROGRAMFILES"));
            program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            arguments << ui->lineEditAntexCompareOrbitsFile2->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditAntexCompareOrbitsFile2->text();
        #endif

        // Execute the program
        if (ui->lineEditAntexCompareOrbitsFile2->text() == "") {
            messageBox.warning(nullptr, "Error","ANTEX file is empty\n");
        } else if (this->fileExists(ui->lineEditAntexCompareOrbitsFile2->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditAntexCompareOrbitsFile2->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditAntexCompareOrbitsFile2->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}

void gLAB_GUI::labelCompareOutputFileMenu(const QPoint& pos) { // this is a slot

    // for most widgets
    QPoint globalPos = ui->labelCompareOutputFile->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    myMenu.addAction("Open Output File");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {

        QProcess *processShow = new QProcess(this);
        QString program;
        QStringList arguments;

        // Based on the OS open the text editor
        #ifdef Q_OS_LINUX
            program = QString("gedit");
            arguments << ui->lineEditOutputFileCompare->text();
        #elif defined(Q_OS_WIN32)
            //QString programFilesPath(getenv("PROGRAMFILES"));
            //program = programFilesPath + QString("\\Windows NT\\Accessories\\wordpad.exe");
            program = QString("notepad");
            arguments << ui->lineEditOutputFileCompare->text();
        #elif defined(Q_OS_MAC)
            program = QString("open");
            arguments << "-t" << ui->lineEditOutputFileCompare->text();
        #endif

        // Execute the program
        if (ui->lineEditOutputFileCompare->text() == "") {
            messageBox.warning(nullptr, "Error","Output file is empty\n");
        } else if (this->fileExists(ui->lineEditOutputFileCompare->text())==false) {
            messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditOutputFileCompare->text() + "' does not exist.\n");
        } else {
            processShow->start(program, arguments);
            sleep(100);
            if (processShow->state()==QProcess::NotRunning||processShow->atEnd()==true) {
                if (processShow->exitCode()!=0) {
                    messageBox.critical(nullptr, "Errors found", "File '" + ui->lineEditOutputFileCompare->text() + "' could not be opened with default text editor.\n");
                }
            }
        }
    }
}
///////////////// End of Context menus (right-click menus) //////////////////

void gLAB_GUI::getCompareOrbitOptions(QString *errorString, QString *warningString, QString *saveString, QStringList *runString) {

    QDate       date;
    QTime       time;
    int         NumMessages=3;
    int         SP3File=0;
    int         badDate=0;

    *errorString = "";
    *warningString="";
    *saveString = "";

    //Check File 1
    if ( ui->radioButtonOrbitNavCompareFile1->isChecked()==true) {
        //File 1 is navigation file
        if ( ui->lineEditNavCompareFile1->text() == "" ) {
            *errorString += "File 1: Navigation source file is empty.\n";
        } else if ( this->fileExists(ui->lineEditNavCompareFile1->text())==false ) {
            *errorString += "File 1: Navigation source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditNavCompareFile1->text())==1) {
            *errorString += "File 1: Navigation source file has non ASCII characters\n";
        } else {
            *saveString += "-input:nav " + ui->lineEditNavCompareFile1->text() + "\n";
            *runString << "-input:nav" << ui->lineEditNavCompareFile1->text();
        }
    } else if ( ui->radioButtonOrbitPrecise1filesCompareFile1->isChecked()==true) {
        //File 1 is SP3
        if ( ui->lineEditPreciseFilesCompareSP3File1->text() == "" ) {
            *errorString += "File 1: SP3 source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareSP3File1->text()) ==false) {
            *errorString += "File 1: SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareSP3File1->text())==1) {
            *errorString += "File 1: SP3 source file has non ASCII characters\n";
        } else {
            *saveString += "-input:sp3 " +  ui->lineEditPreciseFilesCompareSP3File1->text() + "\n";
            *runString << "-input:sp3" << ui->lineEditPreciseFilesCompareSP3File1->text();
        }
        SP3File=1;
    } else if ( ui->radioButtonOrbitPrecise2filesCompareFile1->isChecked()==true ) {
        //File 1 is SP3 + CLK
        if ( ui->lineEditPreciseFilesCompareOrbFile1->text() == "" ) {
            *errorString += "File 1: Orbit SP3 source file is empty.\n";
        } else if ( this->fileExists( ui->lineEditPreciseFilesCompareOrbFile1->text() )==false) {
            *errorString += "File 1: Orbit SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareOrbFile1->text())==1) {
            *errorString += "File 1: Orbit SP3 source file has non ASCII characters\n";
        } else {
            *saveString += "-input:orb " + ui->lineEditPreciseFilesCompareOrbFile1->text() + "\n";
            *runString << "-input:orb" << ui->lineEditPreciseFilesCompareOrbFile1->text();
        }
        if ( ui->lineEditPreciseFilesCompareClkFile1->text() == "" ) {
            *errorString += "File 1: Clock source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareClkFile1->text())==false) {
            *errorString += "File 1: Clock source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareClkFile1->text())==1) {
            *errorString += "File 1: Clock source file has non ASCII characters\n";
        } else {
            *saveString += "-input:clk " + ui->lineEditPreciseFilesCompareClkFile1->text() + "\n";
            *runString << "-input:clk" << ui->lineEditPreciseFilesCompareClkFile1->text();
        }
        SP3File=1;
    }
    //Check File 2
    if ( ui->radioButtonOrbitNavCompareFile2->isChecked()==true) {
        //File 2 is navigation file
        if ( ui->lineEditNavCompareFile2->text() == "" ) {
            *errorString += "File 2: Navigation source file is empty.\n";
        } else if ( this->fileExists(ui->lineEditNavCompareFile2->text())==false ) {
            *errorString += "File 2: Navigation source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditNavCompareFile2->text())==1) {
            *errorString += "File 2: Navigation source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:nav " + ui->lineEditNavCompareFile2->text() + "\n";
            *runString <<  "-input:nav" << ui->lineEditNavCompareFile2->text();
        }
    } else if ( ui->radioButtonOrbitPrecise1filesCompareFile2->isChecked()==true) {
        //File 2 is SP3
        if ( ui->lineEditPreciseFilesCompareSP3File2->text() == "" ) {
            *errorString += "File 2: SP3 source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareSP3File2->text()) ==false) {
            *errorString += "File 2: SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareSP3File2->text())==1) {
            *errorString += "File 2: SP3 source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:sp3 " + ui->lineEditPreciseFilesCompareSP3File2->text() + "\n";
            *runString <<  "-input:sp3" << ui->lineEditPreciseFilesCompareSP3File2->text();
        }
        SP3File=1;
        //Check ANTEX
        if ( ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
            if ( ui->lineEditAntexCompareOrbitsFile2->text() == "" ) {
                *errorString += "ANTEX option selected, but source file is empty.\n";
            } else if  (  this->fileExists(ui->lineEditAntexCompareOrbitsFile2->text() )==false) {
                *errorString += "ANTEX source file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditAntexCompareOrbitsFile2->text())==1) {
                *errorString += "ANTEX source file has non ASCII characters\n";
            } else {
                *saveString +=  "-input:ant " + ui->lineEditAntexCompareOrbitsFile2->text() + "\n";
                *runString <<  "-input:ant" << ui->lineEditAntexCompareOrbitsFile2->text();
            }
        } else {
            *saveString += "--model:satphasecenter\n";
            *runString << "--model:satphasecenter";
        }
    } else if ( ui->radioButtonOrbitPrecise2filesCompareFile2->isChecked()==true ) {
        //File 2 is SP3 + CLK
        if ( ui->lineEditPreciseFilesCompareOrbFile2->text() == "" ) {
            *errorString += "File 2: Orbit SP3 source file is empty.\n";
        } else if ( this->fileExists( ui->lineEditPreciseFilesCompareOrbFile2->text() )==false) {
            *errorString += "File 2: Orbit SP3 source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareOrbFile2->text())==1) {
            *errorString += "File 2: Orbit SP3 source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:orb " + ui->lineEditPreciseFilesCompareOrbFile2->text() + "\n";
            *runString <<  "-input:orb" << ui->lineEditPreciseFilesCompareOrbFile2->text();
        }
        SP3File=1;
        if ( ui->lineEditPreciseFilesCompareClkFile2->text() == "" ) {
            *errorString += "File 2: Clock source file is empty.\n";
        } else if (  this->fileExists(ui->lineEditPreciseFilesCompareClkFile2->text())==false) {
            *errorString += "File 2: Clock source file does not exist.\n";
        } else if (this->checknonASCIIcharacters(ui->lineEditPreciseFilesCompareClkFile2->text())==1) {
            *errorString += "File 2: Clock source file has non ASCII characters\n";
        } else {
            *saveString +=  "-input:clk " + ui->lineEditPreciseFilesCompareClkFile2->text() + "\n";
            *runString <<  "-input:clk" << ui->lineEditPreciseFilesCompareClkFile2->text();
        }
        //Check ANTEX
        if ( ui->checkBoxAntexCompareOrbitsFile2->isChecked()==true) {
            if ( ui->lineEditAntexCompareOrbitsFile2->text() == "" ) {
                *errorString += "ANTEX option selected, but source file is empty.\n";
            } else if  (  this->fileExists(ui->lineEditAntexCompareOrbitsFile2->text() )==false) {
                *errorString += "ANTEX source file does not exist.\n";
            } else if (this->checknonASCIIcharacters(ui->lineEditAntexCompareOrbitsFile2->text())==1) {
                *errorString += "ANTEX source file has non ASCII characters\n";
            } else {
                *saveString +=  "-input:ant " + ui->lineEditAntexCompareOrbitsFile2->text() + "\n";
                *runString <<  "-input:ant" << ui->lineEditAntexCompareOrbitsFile2->text();
            }
        } else {
            *saveString += "--model:satphasecenter\n";
            *runString << "--model:satphasecenter";
        }
    }

    ///Check modeling options
    //Decimation
    if (ui->lineEditDecimationCompareOrbit->text()=="") {
        *errorString += "Data Decimation value is empty.\n";
    } else if (ui->lineEditDecimationCompareOrbit->text().toDouble()==0.) {
        *errorString += "Data Decimation can not be set to 0.\n";
    } else if (ui->lineEditDecimationCompareOrbit->text().toDouble()!= 300.) {
        //By default it is set to 300
        *saveString +=  "-pre:dec " + ui->lineEditDecimationCompareOrbit->text() + "\n";
        *runString <<  "-pre:dec" << ui->lineEditDecimationCompareOrbit->text();
    }

    //Check eclipse condition. By default disabled
    if (ui->checkBoxDiscardEclipseCompare->isChecked()==true) {
        *saveString +=  "-pre:eclipse\n";
        *runString <<  "-pre:eclipse";
    }

    //Check start time is greater than end time (if both are enabled)
    if ( ui->checkBoxStartTimeCompareOrbits->isChecked()==true && ui->checkBoxEndTimeCompareOrbits->isChecked()==true) {
        date = ui->StartTimeCompareOrbits->date();
        time = ui->StartTimeCompareOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set.\n";
            badDate=1;
        }
        date = ui->EndTimeCompareOrbits->date();
        time = ui->EndTimeCompareOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End Time' is set.\n";
            badDate=1;
        }
        if (badDate==0) {
            if (ui->StartTimeCompareOrbits->date().operator >(ui->EndTimeCompareOrbits->date()) ) {
                *errorString += "'End Time' must be greater than the 'Start Time' if both are set.\n";
                badDate=1;
            } else if (ui->StartTimeCompareOrbits->date().operator ==(ui->EndTimeCompareOrbits->date()) ) {
                if (ui->StartTimeCompareOrbits->time().operator >(ui->EndTimeCompareOrbits->time()) ) {
                    *errorString += "'End Time' must be greater than the 'Start Time' if both are set.\n";
                    badDate=1;
                }
            }
        }
    }

    //Start time
    if (ui->checkBoxStartTimeCompareOrbits->isChecked()==true) {
        date = ui->StartTimeCompareOrbits->date();
        time = ui->StartTimeCompareOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'Start Time' is set.\n";
            }
        } else {
                *saveString += "-pre:starttime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
                *runString << "-pre:starttime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    //End time
    if (ui->checkBoxEndTimeCompareOrbits->isChecked()==true) {
        date = ui->EndTimeCompareOrbits->date();
        time = ui->EndTimeCompareOrbits->time();
        if ( date.day() == 31 && date.month() == 12 && date.year() == 1979 && time.hour() == 0 && time.minute()==0 && time.second()==0) {
            if (badDate==0) {
                *errorString += "Date (DD/MM/YYYY) and GPS Time (HH:MM:SS) are a required input if 'End time' is set.\n";
            }
        } else {
            *saveString += "-pre:endtime " + date.toString("yyyy/MM/dd") + " " + time.toString("HH:mm:ss") + "\n";
            *runString << "-pre:endtime" << date.toString("yyyy/MM/dd") << time.toString("HH:mm:ss");
        }
    }

    //Clock correction. By default enabled
    if (ui->checkBoxSatClockOffsetCompare->isChecked()==false) {
        *saveString +=  "--model:satclocks\n";
        *runString <<  "--model:satclocks";
    }

    //Broadcast transmission time. By default enabled
    if (ui->checkBoxCheckBroadcastTransmissionTimeCompare->isChecked()==false) {
        *saveString +=  "--model:brdctranstime\n";
        *runString <<  "--model:brdctranstime";
    }

    // Precise products interpolation data (only when a precise product is given)
    if ( SP3File==1) {
        if ( ui->lineEditOrbitInterpolationDegreeCompare->text() == "" ) {
            *errorString += "Orbit interpolation degree cannot be empty.\n";
        } else if ( ui->lineEditOrbitInterpolationDegreeCompare->text().toInt() == 0 ) {
            *errorString += "Orbit interpolation degree cannot be 0.\n";
        } else if ( ui->lineEditOrbitConsecutiveGapsCompare->text() == "" ) {
            *errorString += "Number of consecutive gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGapsCompare->text() == "" ) {
            *errorString += "Number of maximum gaps in orbit interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockInterpolationDegreeCompare->text() == "" ) {
            *errorString += "Clock interpolation degree cannot be empty.\n";
        } else if ( ui->lineEditClockConsecutiveGapsCompare->text() == "" ) {
            *errorString += "Number of consecutive gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditClockMaxGapsCompare->text() == "" ) {
            *errorString += "Number of maximum gaps in clock interpolation cannot be empty.\n";
        } else if ( ui->lineEditOrbitMaxGapsCompare->text().toInt()< ui->lineEditOrbitConsecutiveGapsCompare->text().toInt()) {
            *errorString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else if ( ui->lineEditClockMaxGapsCompare->text().toInt()< ui->lineEditClockConsecutiveGapsCompare->text().toInt()) {
            *errorString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
        } else {
            if ( ui->lineEditOrbitInterpolationDegreeCompare->text().toInt() !=10) {
                *saveString += "-model:orbit:deg " + ui->lineEditOrbitInterpolationDegreeCompare->text() + "\n";
                *runString << "-model:orbit:deg" << ui->lineEditOrbitInterpolationDegreeCompare->text();
            }
            if (ui->lineEditOrbitConsecutiveGapsCompare->text().toInt()!=8) {
                *saveString += "-model:orbmaxgaps " + ui->lineEditOrbitConsecutiveGapsCompare->text() + "\n";
                *runString << "-model:orbmaxgaps" << ui->lineEditOrbitConsecutiveGapsCompare->text();
            }
            if (ui->lineEditOrbitMaxGapsCompare->text().toInt()!=16) {
                *saveString += "-model:orbtotmaxgaps " + ui->lineEditOrbitMaxGapsCompare->text() + "\n";
                *runString << "-model:orbtotmaxgaps" << ui->lineEditOrbitMaxGapsCompare->text();
            }
            if ( ui->lineEditClockInterpolationDegreeCompare->text().toInt()!=1) {
                *saveString += "-model:clock:deg " + ui->lineEditClockInterpolationDegreeCompare->text() + "\n";
                *runString << "-model:clock:deg" << ui->lineEditClockInterpolationDegreeCompare->text();
            }
            if (ui->lineEditClockConsecutiveGapsCompare->text().toInt()!=2) {
                *saveString += "-model:clkmaxgaps " + ui->lineEditClockConsecutiveGapsCompare->text() + "\n";
                *runString << "-model:clkmaxgaps" << ui->lineEditClockConsecutiveGapsCompare->text() + "\n";
            }
            if (ui->lineEditClockMaxGapsCompare->text().toInt()!=4) {
                *saveString += "-model:clktotmaxgaps " + ui->lineEditClockMaxGapsCompare->text() + "\n";
                *runString << "-model:clktotmaxgaps" << ui->lineEditClockMaxGapsCompare->text() + "\n";
            }
        }
        //Current or Previous sample interpolation option for concatenated orbit files
        if (ui->radioButtonOrbitCurrentDayCompare->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:orbprevsample\n";
            *runString << "-model:orbprevsample";
        }
        if (ui->radioButtonClockCurrentDayCompare->isChecked()==true) {
            //This is not the default option
            *saveString += "-model:clkprevsample\n";
            *runString << "-model:clkprevsample";
        }
    }

    //Navigation message types
    //Single file
    if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==0){
        //GPS
        QString cmdNavMT="",cmdNavMT2="";
        int cmdOK=0,nOk=0;
        if (ui->checkBoxCompareNavMessageTypeGPS->isChecked()) {
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->text()!=CompareNavMT[GPS][0][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGPS->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                if ( nOk==ui->tableWidgetCompareNavMessageTypeGPS->columnCount() && ui->tableWidgetCompareNavMessageTypeGPS->item(0,0)->text()=="CNAV" ) {
                    *saveString += "-model:brdc:gps PreferCNAV\n";
                    *runString << "-model:brdc:gps" << "PreferCNAV";
                } else {
                    *saveString += "-model:brdc:gps " + cmdNavMT + "\n";
                    *runString << "-model:brdc:gps" << cmdNavMT;
                }

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:gps PreferLNAV\n";
                *runString << "-model:brdc:gps" << "PreferLNAV";
            }
        }
        //Galileo
        if (ui->checkBoxCompareNavMessageTypeGalileo->isChecked()) {
            cmdNavMT="";
            cmdNavMT2="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->text()!=CompareNavMT[Galileo][0][i]) {
                    cmdOK=1;
                }
                if (ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->text().replace(" ","") + ",";
                if (i>0) {
                    cmdNavMT2 += ui->tableWidgetCompareNavMessageTypeGalileo->item(0,i)->text() + ",";
                }
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                cmdNavMT2.chop(1);
                if ( nOk==ui->tableWidgetCompareNavMessageTypeGalileo->columnCount() && ui->tableWidgetCompareNavMessageTypeGalileo->item(0,0)->text()=="FNAV" && cmdNavMT2== GalINAVDefaultOrder ) {
                    *saveString += "-model:brdc:gal PreferFNAV\n";
                    *runString << "-model:brdc:gal" << "PreferFNAV";
                } else {
                    if (cmdNavMT==GalINAVDefaultOrder) {
                        *saveString += "-model:brdc:gal INAV\n";
                        *runString << "-model:brdc:gal" << "INAV";
                    } else {
                        *saveString += "-model:brdc:gal " + cmdNavMT + "\n";
                        *runString << "-model:brdc:gal" << cmdNavMT;
                    }
                }

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:gal PreferINAV\n";
                *runString << "-model:brdc:gal" << "PreferINAV";
            }
        }
        //GLONASS
        if ( 0 ) {
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->text()!=CompareNavMT[GLONASS][0][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGLONASS->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:glo " + cmdNavMT + "\n";
                *runString << "-model:brdc:glo" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:glo FDMA\n";
                *runString << "-model:brdc:glo" << "FDMA";
            }
        }
        //GEO
        if ( 0 ) {
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->text()!=CompareNavMT[GEO][0][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGEO->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:geo " + cmdNavMT + "\n";
                *runString << "-model:brdc:geo" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:geo CNAV\n";
                *runString << "-model:brdc:geo" << "CNAV";
            }
        }
        //BDS
        if (ui->checkBoxCompareNavMessageTypeBDS->isChecked()) {
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->text()!=CompareNavMT[BDS][0][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeBDS->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:bds " + cmdNavMT + "\n";
                *runString << "-model:brdc:bds" << cmdNavMT;
            }
            else if (WriteAllParameters){
                *saveString += "-model:brdc:bds D1\n";
                *runString << "-model:brdc:bds" << "D1";
            }
        }
        //QZSS
        if (ui->checkBoxCompareNavMessageTypeQZSS->isChecked()) {
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->text()!=CompareNavMT[QZSS][0][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeQZSS->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:qzs " + cmdNavMT + "\n";
                *runString << "-model:brdc:qzs" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:qzs LNAV\n";
                *runString << "-model:brdc:qzs" << "LNAV";
            }
        }
        //IRNSS
        if ( 0 ){
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->text()!=CompareNavMT[IRNSS][0][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeIRNSS->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:irnss " + cmdNavMT + "\n";
                *runString << "-model:brdc:irnss" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:irnss CNAV\n";
                *runString << "-model:brdc:irnss" << "CNAV";
            }
        }

    //Double file
    } else if (ui->stackedWidgetCompareNavMessageTypes->currentIndex()==1){
        //GPS
        QString cmdNavMT="",cmdNavMT2="";
        int cmdOK=0,nOk=0;
        if (ui->checkBoxCompareNavMessageTypeGPS_2->isChecked()) {
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->text()!=CompareNavMT[GPS][1][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) {
                        if (i!=(ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount()-NUMGPSVSNAVTYPES-1) && !ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->text().contains("vs") ) {
                            //Only set cmdOK if the current disabled cell is not the first containing the "vs" text in the default order
                            cmdOK=1;
                        }
                    }
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                if ( nOk==(ui->tableWidgetCompareNavMessageTypeGPS_2->columnCount()-NUMGPSVSNAVTYPES) && ui->tableWidgetCompareNavMessageTypeGPS_2->item(0,0)->text()=="CNAV" ) {
                    *saveString += "-model:brdc:gps PreferCNAV\n";
                    *runString << "-model:brdc:gps" << "PreferCNAV";
                } else if (cmdNavMT!=GPSNAVDefaultOrder) {
                    *saveString += "-model:brdc:gps " + cmdNavMT + "\n";
                    *runString << "-model:brdc:gps" << cmdNavMT;
                }

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:gps PreferLNAV\n";
                *runString << "-model:brdc:gps" << "PreferLNAV";
            }
        }
        //Galileo
        if (ui->checkBoxCompareNavMessageTypeGalileo_2->isChecked()) {
            cmdNavMT="";
            cmdOK=0;nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->text()!=CompareNavMT[Galileo][1][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) {
                        if (i!=(ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount()-NUMGALVSNAVTYPES-1) && !ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->text().contains("vs") ) {
                            //Only set cmdOK if the current disabled cell is not the first containing the "vs" text in the default order
                            cmdOK=1;
                        }
                    }
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->text().replace(" ","") + ",";
                if (i>0) {
                    cmdNavMT2 += ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,i)->text().replace(" ","") + ",";
                }
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                cmdNavMT2.chop(1);
                if ( nOk==(ui->tableWidgetCompareNavMessageTypeGalileo_2->columnCount()-NUMGALVSNAVTYPES) && ui->tableWidgetCompareNavMessageTypeGalileo_2->item(0,0)->text()=="FNAV" && cmdNavMT2== GalINAVDefaultOrder ) {
                    *saveString += "-model:brdc:gal PreferFNAV\n";
                    *runString << "-model:brdc:gal" << "PreferFNAV";
                } else {
                    if (cmdNavMT==GalINAVDefaultOrder) {
                        *saveString += "-model:brdc:gal INAV\n";
                        *runString << "-model:brdc:gal" << "INAV";
                    } else if (cmdNavMT!=(GalINAVDefaultOrder+",FNAV")) {
                        *saveString += "-model:brdc:gal " + cmdNavMT + "\n";
                        *runString << "-model:brdc:gal" << cmdNavMT;
                    }
                }
            } else if (WriteAllParameters){
                *saveString += "-model:brdc:gal PreferINAV\n";
                *runString << "-model:brdc:gal" << "PreferINAV";
            }
        }
        //GLONASS
        if ( 0 ){
            cmdNavMT="";
            cmdOK=0;nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGLONASS_2->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->text()!=CompareNavMT[GLONASS][1][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGLONASS_2->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:glo " + cmdNavMT + "\n";
                *runString << "-model:brdc:glo" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:glo FDMA\n";
                *runString << "-model:brdc:glo" << "FDMA";
            }
        }
        //GEO
        if ( 0 ){
            cmdNavMT="";
            cmdOK=0;nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeGEO_2->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->text()!=CompareNavMT[GEO][1][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeGEO_2->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:geo " + cmdNavMT + "\n";
                *runString << "-model:brdc:geo" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:geo CNAV\n";
                *runString << "-model:brdc:geo" << "CNAV";
            }
        }
        //BDS
        if (ui->checkBoxCompareNavMessageTypeBDS_2->isChecked()) {
            cmdNavMT="";
            cmdOK=0;nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeBDS_2->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->text()!=CompareNavMT[BDS][1][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeBDS_2->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:bds " + cmdNavMT + "\n";
                *runString << "-model:brdc:bds" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:bds D1\n";
                *runString << "-model:brdc:bds" << "D1";
            }
        }
        //QZSS
        if (ui->checkBoxCompareNavMessageTypeQZSS_2->isChecked()) {
            cmdNavMT="";
            cmdOK=0;nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeQZSS_2->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->text()!=CompareNavMT[QZSS][1][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeQZSS_2->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:qzs " + cmdNavMT + "\n";
                *runString << "-model:brdc:qzs" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:qzs LNAV\n";
                *runString << "-model:brdc:qzs" << "LNAV";
            }
        }
        //IRNSS
        if ( 0 ){
            cmdNavMT="";
            cmdOK=0;
            nOk=0;
            for (int i=0; i<ui->tableWidgetCompareNavMessageTypeIRNSS_2->columnCount();i++){
                if (ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->text()!=CompareNavMT[IRNSS][1][i]) cmdOK=1;
                if (ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->background().color().name()==RedColor) {
                    if (i>0) cmdOK=1;
                    break;
                }
                cmdNavMT += ui->tableWidgetCompareNavMessageTypeIRNSS_2->item(0,i)->text().replace(" ","") + ",";
                nOk++;
            }
            if (cmdOK==1){
                cmdNavMT.chop(1);
                *saveString += "-model:brdc:irnss " + cmdNavMT + "\n";
                *runString << "-model:brdc:irnss" << cmdNavMT;

            } else if (WriteAllParameters){
                *saveString += "-model:brdc:irnss CNAV\n";
                *runString << "-model:brdc:irnss" << "CNAV";
            }
        }
    }

    //Check Output file
    if ( ui->lineEditOutputFileCompare->text() == "" ) {
        *errorString += "Output file is empty.\n";
    } else if (this->checknonASCIIcharacters(ui->lineEditOutputFileCompare->text())==1) {
        *errorString += "Output file has non ASCII characters\n";
    } else {
        *saveString += "-output:file " + ui->lineEditOutputFileCompare->text() + "\n";
        *runString << "-output:file" << ui->lineEditOutputFileCompare->text();
    }

    //Check output messages
    //All compare messages are by default enabled
    if (ui->checkBoxPrintInfoCompare->isChecked()==false) {
        *saveString += "--print:info\n";
        *runString << "--print:info";
    }
    if (ui->checkBoxPrintSatdiffCompare->isChecked()==false) {
       *saveString += "--print:satdiff\n";
       *runString << "--print:satdiff";
       NumMessages--;
    }
    if (ui->checkBoxPrintSatstatCompare->isChecked()==false) {
       *saveString += "--print:satstat\n";
       *runString << "--print:satstat";
       NumMessages--;
    }
    if (ui->checkBoxPrintSatstattotCompare->isChecked()==false) {
       *saveString += "--print:satstattot\n";
       *runString << "--print:satstattot";
       NumMessages--;
    }

    //Clock units
    if (ui->radioButtonNanosecondsUnitOutputClockSATDIFF->isChecked()==true) {
        *saveString += "-print:clkns\n";
        *runString << "-print:clkns";
    } else if (WriteAllParameters==1) {
        *saveString += "--print:clkns\n";
        *runString << "--print:clkns";
    }

    //V5 messages
    if (this->v5Message>0) {
        *saveString += "-print:v5format\n";
        *runString << "-print:v5format";
    }
    if (NumMessages==0) {
        *errorString += "One or more of these output messages must be selected: SATDIFF, SATSTAT or SATSTATTOT.\n";
    }
}

void gLAB_GUI::compareOrbitsLoadParameters(QFile *file) {

    QString line;
    QString option;
    QString userInput;
    QString userInputSingleSpace;
    QString errorString = "";
    QString warningString = "";
    QStringList ParametersList;
    QMessageBox messageBox;
    messageBox.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; background-color: rgb(239, 235, 231); }");
    QTextStream InputFile(file);
    InputFile.setAutoDetectUnicode(true);
    QDate date;
    QTime hour;

    int numNav=0;
    int numSP3=0;
    int numOrb=0;
    int numClk=0;
    int numAnt=0;
    int numInputOrbFiles=0;
    int numInputClKFiles=0;
    int noAntParameter=0;
    int OrbitSP3first=-1,OrbitBRDCfirst=-1;
    int numOutput=0;
    int HashPos;
    int ValidDate, addDay, leapYear;
    int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysmonthLeapYear[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year, month,day, doy, hour2, minute, second,sod,GPSWeek,sow;

    //First loop: Check for errors
    while ( !InputFile.atEnd() ) {
        line = QString(InputFile.readLine());
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        line.remove(QRegularExpression("^\\s+"));
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the line only contained spaces and it has been emptied
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        HashPos=line.indexOf("#");
        if (HashPos!=-1) line.remove(HashPos,line.length()-HashPos); //Remove comments from line
        if ( line.at(0) == '\n' || line.at(0) == '\r') continue;
        option = line.section(" ", 0, 0);
        option.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput = line.section(" ", 1);
        userInput.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput.remove(QRegularExpression("^\\s+"));
        userInput.remove(QRegularExpression("\\s+$"));
        userInputSingleSpace = userInput;
        userInputSingleSpace.replace(QRegularExpression("\\s+")," ");
        userInputSingleSpace.remove(QRegularExpression("\\s$"));
        ParametersList.clear();
        ParametersList = userInput.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

        if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
            numNav++;
            numInputOrbFiles++;
            if(numOrb==0) OrbitSP3first=0;
            if (numOrb==0 && numSP3==0) OrbitBRDCfirst=1;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Navigation", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0  ) {
            numSP3++;
            numInputOrbFiles++;
            if(numOrb==0) OrbitSP3first=0;
            if (numNav==0) OrbitBRDCfirst=0;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("SP3", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0  ) {
            numOrb++;
            numInputOrbFiles++;
            if(numNav==0 && numSP3==0) OrbitSP3first=1;            
            else OrbitSP3first=0;
            if (numNav==0) OrbitBRDCfirst=0;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("SP3 orbit", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
            numClk++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Clock", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
            numAnt++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("ANTEX", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            noAntParameter=1;
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            numOutput++;
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                checkConfigurationFileInputFilePaths("Output", &warningString,&errorString,userInput);
            }
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            noAntParameter=1;
        }
    }

    //Check for errors in number of files
    if (numInputOrbFiles>2) {
        //More than one orbit file given
        if (numNav>2) {
            errorString += "More than two navigation files ('-input:nav' option) are provided.\n";
        }
        if (numSP3>2) {
            errorString += "More than two SP3 file ('-input:sp3' option) are provided.\n";
        }
        if (numOrb>2) {
            errorString += "More than two orbit SP3 file ('-input:orb' option) are provided.\n";
        }
        if (numNav>0 && numSP3>0 && numOrb>0) {
            errorString += "Navigation file, SP3 file and orbit SP3 file were provided, but only two types can be given.\n";
        } else if (numNav>0 && numSP3>1) {
            errorString += "One navigation file and two SP3 files were provided, but only two files can be given.\n";
        } else if (numNav>0 && numOrb>1) {
            errorString += "One navigation file and two orbit SP3 files were provided, but only two files can be given.\n";
        } else if (numNav>1 && numSP3>0) {
            errorString += "Two navigation files and one SP3 files were provided, but only two files can be given.\n";
        } else if (numNav>1 && numOrb>0) {
            errorString += "Two navigation files and one orbit SP3 file were provided, but only two files can be given.\n";
        } else if (numSP3>0 && numOrb>1) {
            errorString += "One SP3 file and two orbit SP3 files were provided, but only two files can be given.\n";
        } else if (numSP3>1 && numOrb>0) {
            errorString += "Two SP3 files and one orbit SP3 file were provided, but only two files can be given.\n";
        }
    }

    //Check number of CLK files
    if (numClk>2) {
        errorString += "More than two CLK file ('-input:clk' option) are provided.\n";
    } else if (numClk<numOrb) {
        errorString += "There are more CLK files ('-input:clk' option) than orbit SP3 files provided.\n";
    }
    //Check if a orbit SP3 was given but not a CLK file
    if (numOrb!= numClk) {
        warningString += "Number of orbit SP3 files provided do not match the number of clock files given.\n";
    }

    //Check if more than ANTEX was given
    if (numAnt>1) {
        errorString += "More than one ANTEX file ('-input:ant' option) is provided.\n";
    }
    //Check if ANTEX file provided, but option for no ANTEX provided
    if (numAnt>0 && noAntParameter==1) {
        warningString += "ANTEX file provided, but also option to not to use ANTEX is provided. Last action read will prevail.\n";
    }
    //Check number of output files
    if (numOutput>1) {
        errorString += "More than one Output file ('-output:file' option) is provided.\n";
    }

    //If errors ocurred, show them and return
    if (!errorString.isEmpty()) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setText("gLAB did not load the the configuration file due to the following errors:\n\n" + errorString);
        messageBox.setIcon(QMessageBox::Critical);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
        return;
    }
    //Second loop: Load parameters
    file->seek(0); //Go back to beginning of file
    setInitialCompareOrbitValues(); //Set default values in compare page

    numInputOrbFiles=0;

    while ( !InputFile.atEnd() ) {
        line = QString(InputFile.readLine());
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the file has empty lines
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        line.remove(QRegularExpression("^\\s+"));
        if ( line == "") continue; //Do not erase this instruction or it will crash in Windows if the line only contained spaces and it has been emptied
        if ( line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == '\r') continue;
        HashPos=line.indexOf("#");
        if (HashPos!=-1) line.remove(HashPos,line.length()-HashPos); //Remove comments from line
        if ( line.at(0) == '\n' || line.at(0) == '\r') continue;
        option = line.section(" ", 0, 0);
        option.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput = line.section(" ", 1);
        userInput.remove(QRegularExpression("[\\n\\t\\r\"']"));
        userInput.remove(QRegularExpression("^\\s+"));
        userInput.remove(QRegularExpression("\\s+$"));
        userInputSingleSpace = userInput;
        userInputSingleSpace.replace(QRegularExpression("\\s+")," ");
        userInputSingleSpace.remove(QRegularExpression("\\s$"));
        ParametersList.clear();
        ParametersList = userInput.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

        if ( QString::compare(option, "-input:nav", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                if(numInputOrbFiles==0) {
                    this->on_radioButtonOrbitNavCompareFile1_clicked();
                    ui->lineEditNavCompareFile1->setText(userInput);
                } else {
                    this->on_radioButtonOrbitNavCompareFile2_clicked();
                    ui->lineEditNavCompareFile2->setText(userInput);
                }
                numInputOrbFiles++;
            }
        } else if ( QString::compare(option, "-input:sp3", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                if(numInputOrbFiles==0) {
                    this->on_radioButtonOrbitPrecise1filesCompareFile1_clicked();
                    ui->lineEditPreciseFilesCompareSP3File1->setText(userInput);
                } else {
                    this->on_radioButtonOrbitPrecise1filesCompareFile2_clicked();
                    ui->lineEditPreciseFilesCompareSP3File2->setText(userInput);
                }
                numInputOrbFiles++;
            }
        } else if ( QString::compare(option, "-input:orb", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                if(numInputOrbFiles==0 && OrbitBRDCfirst==0) {
                    this->on_radioButtonOrbitPrecise2filesCompareFile1_clicked();
                    ui->lineEditPreciseFilesCompareOrbFile1->setText(userInput);
                } else {
                    this->on_radioButtonOrbitPrecise2filesCompareFile2_clicked();
                    ui->lineEditPreciseFilesCompareOrbFile2->setText(userInput);
                }
                numInputOrbFiles++;
            }
        } else if ( QString::compare(option, "-input:clk", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                if(numOrb==1) {
                    if(OrbitSP3first==0 ) {
                        this->on_radioButtonOrbitPrecise2filesCompareFile2_clicked();
                        ui->lineEditPreciseFilesCompareClkFile2->setText(userInput);
                    } else {
                        this->on_radioButtonOrbitPrecise2filesCompareFile1_clicked();
                        ui->lineEditPreciseFilesCompareClkFile1->setText(userInput);
                    }
                } else {
                    if(numInputClKFiles==0) {
                        this->on_radioButtonOrbitPrecise2filesCompareFile1_clicked();
                        ui->lineEditPreciseFilesCompareClkFile1->setText(userInput);
                    } else {
                        this->on_radioButtonOrbitPrecise2filesCompareFile2_clicked();
                        ui->lineEditPreciseFilesCompareClkFile2->setText(userInput);
                    }
                }
                numInputClKFiles++;
            }
        } else if ( QString::compare(option, "-input:ant", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()>=1) {
                this->on_checkBoxAntexCompareOrbitsFile2_clicked(true);
                ui->lineEditAntexCompareOrbitsFile2->setText(userInput);
            }
        } else if ( QString::compare(option, "-pre:dec", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            }  else  if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<=0.) {
                    warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()<1E-4) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0.0001. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").toDouble()>86400.) {
                warningString += "Parameter '" + option + "' has to be smaller or equal than 86400. It was skipped.\n";
            } else {
                   ui->lineEditDecimationCompareOrbit->setText(QString("%1").arg(ParametersList[0]).replace(",",""));
            }
        } else if ( QString::compare(option, "--pre:dec", Qt::CaseInsensitive)==0 ) {
            warningString += "Parameter '" + option + "' is not valid in compare orbit mode. It was skipped.\n";
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-pre:eclipse", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardEclipseCompare->setChecked(false);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--pre:eclipse", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxDiscardEclipseCompare->setChecked(false);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-pre:starttime", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()<2) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                ValidDate=1;
                addDay=0;
                leapYear=0;
                year=0;
                month=0;
                day=0;
                hour2=-1;
                minute=-1;
                second=-1;
                extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                if(userInputSingleSpace.section(" ", 1,1).contains(":")==true) {
                    //Time has ":" symbol.
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Time is in YYYY/MM/DD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=10) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                             if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                 warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                 ValidDate=0;
                             } else {
                                 year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                 month=userInputSingleSpace.section(" ", 0,0).mid(5,2).toInt();
                                 day=userInputSingleSpace.section(" ", 0,0).mid(8,2).toInt();
                             }
                        }
                    } else {
                        //Time is in YYYYMMDD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=8) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                ValidDate=0;
                            } else {
                                year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                                day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                            }
                        }
                    }
                    if (ValidDate==1) {
                        //Check date values and time length
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(month<1||month>12) {
                            warningString += "Parameter '" + option + "' has an invalid month. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (day<1||day>31|| (leapYear==1 && day>daysmonthLeapYear[month]) || (leapYear==0 && day>daysmonth[month])) {
                            warningString += "Parameter '" + option + "' has an invalid day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                            warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                    if (ValidDate==1) {
                        //Read time in HH:MM:SS format and check values
                        hour2=userInputSingleSpace.section(" ", 1,1).left(2).toInt();
                        minute=userInputSingleSpace.section(" ", 1,1).mid(3,2).toInt();
                        second=userInputSingleSpace.section(" ", 1,1).mid(6,2).toInt();
                        if(hour2<0||hour2>24) {
                            warningString += "Parameter '" + option + "' has an invalid hour. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(minute<0||minute>60) {
                            warningString += "Parameter '" + option + "' has an invalid minute. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(second<0||second>60) {
                            warningString += "Parameter '" + option + "' has an invalid second. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                     if (ValidDate==1) {
                         if(second==60) {
                             second-=60;
                             minute++;
                         }
                         if(minute==60) {
                             minute-=60;
                             hour2++;
                         }
                         if(hour2==24) {
                             hour2-=24;
                             addDay=1;
                         }
                         date=QDate(year,month,day);
                         if(addDay==1) {
                            date=date.addDays(qint64(1));
                         }
                         hour=QTime(hour2,minute,second);
                         ui->StartTimeCompareOrbits->setDate(date);
                         ui->StartTimeCompareOrbits->setTime(hour);
                         this->on_checkBoxStartTimeCompareOrbits_clicked(true);
                     }
                } else {
                    //Time can be in YYYY/DoY or GPSWeek
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Date is in YYYY/DoY SoD format
                        year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                        doy=userInputSingleSpace.section(" ", 0,0).mid(5).toInt();
                        sod=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(doy<0||(doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                            warningString += "Parameter '" + option + "' has an invalid day of year. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sod<0||sod>86400) {
                            warningString += "Parameter '" + option + "' has an invalid second of day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sod==86400) {
                                sod-=86400;
                                doy++;
                            }
                            if((doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                doy=1;
                                year++;
                            }
                            doy2date(year,doy,&date);
                            SoD2time(sod,&hour);
                            ui->StartTimeCompareOrbits->setDate(date);
                            ui->StartTimeCompareOrbits->setTime(hour);
                            this->on_checkBoxStartTimeCompareOrbits_clicked(true);
                        }
                    } else {
                        //Date is in GPSWeek SoW format
                        GPSWeek=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                        sow=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(GPSWeek<1) {
                            warningString += "Parameter '" + option + "' has an invalid GPS week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sow<0||sow>604800) {
                            warningString += "Parameter '" + option + "' has an invalid second of week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sow==604800) {
                                sow-=604800;
                                GPSWeek++;
                            }
                            GPSTime2DateTime(GPSWeek,sow,&date,&hour);
                            ui->StartTimeCompareOrbits->setDate(date);
                            ui->StartTimeCompareOrbits->setTime(hour);
                            this->on_checkBoxStartTimeCompareOrbits_clicked(true);
                        }
                    }
                }
            }
        } else if ( QString::compare(option, "-pre:endtime", Qt::CaseInsensitive)==0 ) {
            if (ParametersList.count()<2) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else {
                ValidDate=1;
                addDay=0;
                leapYear=0;
                year=0;
                month=0;
                day=0;
                hour2=-1;
                minute=-1;
                second=-1;
                extraArgumentsToWarningStr(2,&warningString,option,ParametersList);
                if(userInputSingleSpace.section(" ", 1,1).contains(":")==true) {
                    //Time has ":" symbol.
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Time is in YYYY/MM/DD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=10) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                             if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                 warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                 ValidDate=0;
                             } else {
                                 year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                 month=userInputSingleSpace.section(" ", 0,0).mid(5,2).toInt();
                                 day=userInputSingleSpace.section(" ", 0,0).mid(8,2).toInt();
                             }
                        }
                    } else {
                        //Time is in YYYYMMDD HH:MM:SS format
                        if(userInputSingleSpace.section(" ", 0,0).length()!=8) {
                            //Invalid date
                            warningString += "Parameter '" + option + "' has an invalid date. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                                warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                                ValidDate=0;
                            } else {
                                year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                                month=userInputSingleSpace.section(" ", 0,0).mid(4,2).toInt();
                                day=userInputSingleSpace.section(" ", 0,0).mid(6,2).toInt();
                            }
                        }
                    }
                    if (ValidDate==1) {
                        //Check date values and time length
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(month<1||month>12) {
                            warningString += "Parameter '" + option + "' has an invalid month. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (day<1||day>31|| (leapYear==1 && day>daysmonthLeapYear[month]) || (leapYear==0 && day>daysmonth[month])) {
                            warningString += "Parameter '" + option + "' has an invalid day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(userInputSingleSpace.section(" ", 1,1).length()!=8) {
                            warningString += "Parameter '" + option + "' has an invalid time. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                    if (ValidDate==1) {
                        //Read time in HH:MM:SS format and check values
                        hour2=userInputSingleSpace.section(" ", 1,1).left(2).toInt();
                        minute=userInputSingleSpace.section(" ", 1,1).mid(3,2).toInt();
                        second=userInputSingleSpace.section(" ", 1,1).mid(6,2).toInt();
                        if(hour2<0||hour2>24) {
                            warningString += "Parameter '" + option + "' has an invalid hour. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(minute<0||minute>60) {
                            warningString += "Parameter '" + option + "' has an invalid minute. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(second<0||second>60) {
                            warningString += "Parameter '" + option + "' has an invalid second. It was skipped.\n";
                            ValidDate=0;
                        }
                    }
                     if (ValidDate==1) {
                         if(second==60) {
                             second-=60;
                             minute++;
                         }
                         if(minute==60) {
                             minute-=60;
                             hour2++;
                         }
                         if(hour2==24) {
                             hour2-=24;
                             addDay=1;
                         }
                         date=QDate(year,month,day);
                         if(addDay==1) {
                            date=date.addDays(qint64(1));
                         }
                         hour=QTime(hour2,minute,second);
                         ui->EndTimeCompareOrbits->setDate(date);
                         ui->EndTimeCompareOrbits->setTime(hour);
                         this->on_checkBoxEndTimeCompareOrbits_clicked(true);
                     }
                } else {
                    //Time can be in YYYY/DoY or GPSWeek
                    if(userInputSingleSpace.section(" ", 0,0).contains("/")==true) {
                        //Date is in YYYY/DoY SoD format
                        year=userInputSingleSpace.section(" ", 0,0).left(4).toInt();
                        doy=userInputSingleSpace.section(" ", 0,0).mid(5).toInt();
                        sod=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(year<=1970) {
                            warningString += "Parameter '" + option + "' has date prior to 1970. It was skipped.\n";
                            ValidDate=0;
                        } else {
                            //Check leap year
                            if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 ) {
                                leapYear=1;
                            }
                        }
                        if(doy<0||(doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                            warningString += "Parameter '" + option + "' has an invalid day of year. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sod<0||sod>86400) {
                            warningString += "Parameter '" + option + "' has an invalid second of day. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sod==86400) {
                                sod-=86400;
                                doy++;
                            }
                            if((doy>366 && leapYear==1)|| (doy>365 && leapYear==0)) {
                                doy=1;
                                year++;
                            }
                            doy2date(year,doy,&date);
                            SoD2time(sod,&hour);
                            ui->EndTimeCompareOrbits->setDate(date);
                            ui->EndTimeCompareOrbits->setTime(hour);
                            this->on_checkBoxEndTimeCompareOrbits_clicked(true);
                        }
                    } else {
                        //Date is in GPSWeek SoW format
                        GPSWeek=userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt();
                        sow=userInputSingleSpace.section(" ", 1,1).replace(",","").section(".",0,0).toInt();
                        if(GPSWeek<1) {
                            warningString += "Parameter '" + option + "' has an invalid GPS week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if(sow<0||sow>604800) {
                            warningString += "Parameter '" + option + "' has an invalid second of week. It was skipped.\n";
                            ValidDate=0;
                        }
                        if (ValidDate==1) {
                            if(sow==604800) {
                                sow-=604800;
                                GPSWeek++;
                            }
                            GPSTime2DateTime(GPSWeek,sow,&date,&hour);
                            ui->EndTimeCompareOrbits->setDate(date);
                            ui->EndTimeCompareOrbits->setTime(hour);
                            this->on_checkBoxEndTimeCompareOrbits_clicked(true);
                        }
                    }
                }
            }
        } else if ( QString::compare(option, "-model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetCompare->setChecked(true);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:satclocks", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxSatClockOffsetCompare->setChecked(false);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeCompare->setChecked(true);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "--model:brdctranstime", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxCheckBroadcastTransmissionTimeCompare->setChecked(false);
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
        } else if ( QString::compare(option, "-model:orbit:deg", Qt::CaseInsensitive)==0 || QString::compare(option, "-model:orb:deg", Qt::CaseInsensitive)==0) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<=0) {
                warningString += "Parameter '" + option + "' has to be greater than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitInterpolationDegreeCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitConsecutiveGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitConsecutiveGapsCompare->setText("0");
        } else if ( QString::compare(option, "-model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditOrbitMaxGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:orbtotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditOrbitMaxGapsCompare->setText("0");
        } else if ( (QString::compare(option, "-model:clock:deg", Qt::CaseInsensitive)==0 ) || QString::compare(option, "-model:clk:deg", Qt::CaseInsensitive)==0) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockInterpolationDegreeCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "-model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockConsecutiveGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clkmaxgaps", Qt::CaseInsensitive)==0 ) {
             extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
             ui->lineEditClockConsecutiveGapsCompare->setText("0");
        } else if ( QString::compare(option, "-model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(1,&warningString,option,ParametersList);
            if (ParametersList.count()<1) {
                warningString += "Parameter '" + option + "' has missing values. It was skipped.\n";
            } else if (userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0).toInt()<0) {
                warningString += "Parameter '" + option + "' has to be greater or equal than 0. It was skipped.\n";
            } else {
               ui->lineEditClockMaxGapsCompare->setText(QString("%1").arg(userInputSingleSpace.section(" ", 0,0).replace(",","").section(".",0,0)));
            }
        } else if ( QString::compare(option, "--model:clktotmaxgaps", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->lineEditClockMaxGapsCompare->setText("0");
        } else if ( QString::compare(option, "-model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexCompareOrbitsFile2_clicked(true);
        } else if ( QString::compare(option, "--model:satphasecenter", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            this->on_checkBoxAntexCompareOrbitsFile2_clicked(false);
        } else if ( QString::compare(option, "-model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayCompare->setChecked(true);
            ui->radioButtonOrbitNextDayCompare->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesCompare_clicked(true);
        } else if ( QString::compare(option, "--model:orbprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonOrbitCurrentDayCompare->setChecked(false);
            ui->radioButtonOrbitNextDayCompare->setChecked(true);
        } else if ( QString::compare(option, "-model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayCompare->setChecked(true);
            ui->radioButtonClockNextDayCompare->setChecked(false);
            this->on_groupBoxConcatenedPreciseFilesCompare_clicked(true);
        } else if ( QString::compare(option, "--model:clkprevsample", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->radioButtonClockCurrentDayCompare->setChecked(false);
            ui->radioButtonClockNextDayCompare->setChecked(true);
        } else if ( option.left(12).contains("-model:brdc:", Qt::CaseInsensitive)==true ){
            this->command_2_CompareNavMessageTypes(&option,&ParametersList[0],&warningString);
        } else if ( QString::compare(option, "-output:file", Qt::CaseInsensitive)==0 ) {
            ui->lineEditOutputFileCompare->setText(userInput);
        } else if ( QString::compare(option, "--output:file", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            warningString += "Parameter '" + option + "' is for setting output messages to standard output, which will be lost after execution finishes. It was skipped.\n";
        } else if ( QString::compare(option, "-print:info", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:info", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintInfoCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:satdiff", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatdiffCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:satdiff", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatdiffCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:satstat", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstatCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:satstat", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstatCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:satstattot", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstattotCompare->setChecked(true);
        } else if ( QString::compare(option, "--print:satstattot", Qt::CaseInsensitive)==0 ) {
            extraArgumentsToWarningStr(0,&warningString,option,ParametersList);
            ui->checkBoxPrintSatstattotCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:all", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoCompare->setChecked(true);
            ui->checkBoxPrintSatdiffCompare->setChecked(true);
            ui->checkBoxPrintSatstatCompare->setChecked(true);
            ui->checkBoxPrintSatstattotCompare->setChecked(true);
        } else if ( QString::compare(option, "-print:none", Qt::CaseInsensitive)==0 || QString::compare(option, "--print:none", Qt::CaseInsensitive)==0 ) {
            ui->checkBoxPrintInfoCompare->setChecked(false);
            ui->checkBoxPrintSatdiffCompare->setChecked(false);
            ui->checkBoxPrintSatstatCompare->setChecked(false);
            ui->checkBoxPrintSatstattotCompare->setChecked(false);
        } else if ( QString::compare(option, "-print:clkns", Qt::CaseInsensitive)==0 ) {
            ui->radioButtonNanosecondsUnitOutputClockSATDIFF->setChecked(true);
        } else if ( QString::compare(option, "--print:clkns", Qt::CaseInsensitive)==0 ) {
            ui->radioButtonMetresUnitOutputClockSATDIFF->setChecked(true);
        } else if ( QString::compare(option, "-print:v5format", Qt::CaseInsensitive)==0 ) {
            this->v5Message=1;
        }
    }

    if ( ui->lineEditOrbitMaxGapsCompare->text().toInt()< ui->lineEditOrbitConsecutiveGapsCompare->text().toInt()) {
        warningString += "Number of maximum gaps in orbit interpolation must be equal or greater than then number of consecutive gaps.\n";
    } else if ( ui->lineEditClockMaxGapsCompare->text().toInt()< ui->lineEditClockConsecutiveGapsCompare->text().toInt()) {
        warningString += "Number of maximum gaps in clock interpolation must be equal or greater than then number of consecutive gaps.\n";
    }

    if (!warningString.isEmpty()) {
        messageBox.setWindowTitle("Errors found");
        messageBox.setText("gLAB loaded the configuration file, but found the following errors:\n\n" + warningString);
        messageBox.setIcon(QMessageBox::Warning);
        QSpacerItem* horizontalSpacer = new QSpacerItem(800, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = static_cast<QGridLayout*>(messageBox.layout());
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        messageBox.exec();
    }
}
