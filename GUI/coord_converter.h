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

#ifndef COORD_CONVERTER_H
#define COORD_CONVERTER_H

#include <QDialog>
#include <QCloseEvent>
#include <QDoubleValidator>
#include <QDebug>

#define Pi                                      3.14159265358979
#define d2r                                     (Pi/180.)
#define r2d                                     (180./Pi)

namespace Ui {
    class GNSS_Coord_converter;
}

class GNSS_Coord_converter : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_Coord_converter(QWidget *parent = 0);
    ~GNSS_Coord_converter();

private slots:
    void on_pushButtonCoordConvOK_clicked();
    void on_lineEditCoordConvX_textEdited();
    void on_lineEditCoordConvY_textEdited();
    void on_lineEditCoordConvZ_textEdited();
    void on_lineEditCoordConvGeodLon_textEdited();
    void on_lineEditCoordConvGeodLat_textEdited();
    void on_lineEditCoordConvGeodHeight_textEdited();
    void on_lineEditCoordConvGeocLon_textEdited();
    void on_lineEditCoordConvGeocLat_textEdited();
    void on_lineEditCoordConvGeocRadius_textEdited();
    void XYZ2Geod(double *positionXYZ, double *positionNEU);
    void Geod2XYZ(double *positionNEU, double *positionXYZ);
    void XYZ2Geoc(double *positionXYZ, double *positionGeoc);
    void Geoc2XYZ(double *positionGeoc, double *positionXYZ);

private:
    Ui::GNSS_Coord_converter *uiCoord;
};

#endif // COORD_CONVERTER_H
