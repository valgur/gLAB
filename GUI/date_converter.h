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

#ifndef GNSS_DATE_CONVERTER_H
#define GNSS_DATE_CONVERTER_H

#include <QDialog>
#include <QCloseEvent>
#include <QDebug>


extern int DateConverterWindow;

typedef struct {
    int             MJDN;
    double          SoD;
} TTime;

namespace Ui {
    class GNSS_Date_Converter;
}

class GNSS_Date_Converter : public QDialog
{
    Q_OBJECT

public:

    explicit GNSS_Date_Converter(QWidget *parent = 0);
    ~GNSS_Date_Converter();

private slots:
    void on_pushButtonDateConverterOk_clicked();
    void closeEvent (QCloseEvent *event);

    double modulo (double a, double mod);
    void on_dateTimeEditDateConverterCalendar_dateTimeChanged();
    void on_lineEditDateConverterYear_textEdited();
    void on_lineEditDateConverterDoY_textEdited();
    void on_lineEditDateConverterSoD_textEdited();
    void on_lineEditDateConverterGPSWeek_textEdited();
    void on_lineEditDateConverterDoW_textEdited();
    void on_lineEditDateConverterSoW_textEdited();
    void on_lineEditDateConverterMJDN_textEdited();
    void on_lineEditDateConverterSoD_MJDN_textEdited();
    void tmstruct2datetime(struct  tm *tmstruct, QDate *date, QTime *time, double SoD);
    void datetime2tmstruct(struct  tm *tmstruct, QDate *date, QTime *time);
    int    MJDN (struct tm *tm);
    void tm2t (TTime *t, struct tm *tm, double *seconds);
    void t2tm (TTime *t, struct tm *tm, double *seconds);
    void t2doy (TTime *t, int *year, double *doy);
    TTime gpsws2ttime (int GPSweek, double SoW);
    double yeardoy2MJDN (int year, int doy, int sod);
    void ttime2gpsweek (TTime *t, int *GPSweek, int *DoW, double *SoW);
    void tday_of_month (TTime *t, int *day_of_month, int *month_days, int *month_number);
    void doy2date (int year, int doy, QDate *date);
    void SoD2time (double SoD,QTime *time);
    void GPSTime2DateTime(int GPSWeek, double SoW, QDate *date, QTime *time);

private:
    Ui::GNSS_Date_Converter *uiDate;
};

#endif // GNSS_DATE_CONVERTER_H
