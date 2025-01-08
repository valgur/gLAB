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
#include "date_converter.h"
#include "ui_date_converter.h"
#include "math.h"


GNSS_Date_Converter::GNSS_Date_Converter(QWidget *parent) :
    QDialog(parent),
    uiDate(new Ui::GNSS_Date_Converter)
{
    uiDate->setupUi(this);

    // Set StyleSheet
    #if (defined Q_OS_WIN32)
        QFile qss(":/data/WinStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #elif (defined Q_OS_MAC)
        QFile qss(":/data/MacStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #else
        QFile qss(":/data/LinuxStyle.qss");
        qss.open(QFile::ReadOnly);
        this->setStyleSheet(qss.readAll());
        qss.close();
    #endif

    #ifdef Q_OS_WIN32
        uiDate->dateTimeEditDateConverterCalendar->setMinimumWidth(155);
        uiDate->frame->setMinimumWidth(155);
    #elif defined Q_OS_MAC
        setMaximumWidth(720);
        setMinimumWidth(720);
        uiDate->dateTimeEditDateConverterCalendar->setMinimumWidth(190);
        uiDate->frame->setMinimumWidth(190);
    #endif

    QLocale qlocale(QLocale::C);
    qlocale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto ldoublePositiveSoD = new QDoubleValidator(0, 86400,4, this);
    ldoublePositiveSoD->setLocale(qlocale); // lineEdit validation
    auto ldoublePositiveSoW = new QDoubleValidator(0, 604800,4, this);
    ldoublePositiveSoW->setLocale(qlocale); // lineEdit validation
    auto lintPositive = new QIntValidator(0, 9999999, this);
    lintPositive->setLocale(qlocale); // lineEdit validation for seconds
    auto lintDoY = new QIntValidator(1, 365, this);
    lintDoY->setLocale(qlocale); // lineEdit validation for DoY
    auto lintDoW = new QIntValidator(0, 6, this);
    lintDoW->setLocale(qlocale); // lineEdit validation for DoW

    uiDate->lineEditDateConverterYear->setValidator(lintPositive);
    uiDate->lineEditDateConverterDoY->setValidator(lintDoY);
    uiDate->lineEditDateConverterSoD->setValidator(ldoublePositiveSoD);
    uiDate->lineEditDateConverterGPSWeek->setValidator(lintPositive);
    uiDate->lineEditDateConverterDoW->setValidator(lintDoW);
    uiDate->lineEditDateConverterSoW->setValidator(ldoublePositiveSoW);
    uiDate->lineEditDateConverterMJDN->setValidator(lintPositive);
    uiDate->lineEditDateConverterSoD_MJDN->setValidator(ldoublePositiveSoD);

     QDate date = QDate(2000, 1,1);
     QTime time = QTime(0,0,0,0);
     uiDate->dateTimeEditDateConverterCalendar->blockSignals(true);
     uiDate->dateTimeEditDateConverterCalendar->setDate(date);
     uiDate->dateTimeEditDateConverterCalendar->setTime(time);
     this->on_dateTimeEditDateConverterCalendar_dateTimeChanged();
     uiDate->dateTimeEditDateConverterCalendar->blockSignals(false);

}

GNSS_Date_Converter::~GNSS_Date_Converter()
{
    delete uiDate;
}

void GNSS_Date_Converter::on_pushButtonDateConverterClose_clicked()
{
    DateConverterWindow=0;
    this->close();
}

void GNSS_Date_Converter::closeEvent (QCloseEvent *event) {
    DateConverterWindow=0;
    event->accept();
}


void GNSS_Date_Converter::on_dateTimeEditDateConverterCalendar_dateTimeChanged() {
    QDate       Date;
    QTime       Time;
    struct tm   tmstruct;
    TTime       t;
    int         GPSweek;
    int         DoW;
    double      SoW;
    double      SoD;

    if (uiDate->dateTimeEditDateConverterCalendar->date().isValid()==false || uiDate->dateTimeEditDateConverterCalendar->time().isValid()==false) {
        return;
    }

    Date=uiDate->dateTimeEditDateConverterCalendar->date();
    Time=uiDate->dateTimeEditDateConverterCalendar->time();
    SoD= static_cast<double>(Time.hour())*3600. + static_cast<double>(Time.minute())*60. + static_cast<double>(Time.second()) + (static_cast<double>(Time.msec()))/1000.;

    if (Date.year()<1980||(Date.year()==1980 && Date.dayOfYear()<6)) return;

    //Fill tm struct
    this->datetime2tmstruct(&tmstruct, &Date, &Time);
    //Fill TTime struct
    this->tm2t(&t,&tmstruct,&SoD);
    //Get GPSWeek and SoW
    this->ttime2gpsweek(&t, &GPSweek, &DoW, &SoW);

    //Fill Year/DoY/SoD
    uiDate->lineEditDateConverterYear->setText(QString("%1").arg(Date.year()));
    uiDate->lineEditDateConverterDoY->setText(QString("%1").arg(Date.dayOfYear()));
    uiDate->lineEditDateConverterSoD->setText(QString("%1").arg(SoD,0,'g',8));

    //Fill GPSweek and SoW
    uiDate->lineEditDateConverterGPSWeek->setText(QString("%1").arg(GPSweek));
    uiDate->lineEditDateConverterDoW->setText(QString("%1").arg(DoW));
    uiDate->lineEditDateConverterSoW->setText(QString("%1").arg(SoW,0,'g',9));

    //Fill MJDN and SoD
    uiDate->lineEditDateConverterMJDN->setText(QString("%1").arg(t.MJDN));
    uiDate->lineEditDateConverterSoD_MJDN->setText(QString("%1").arg(SoD,0,'g',8));
}

void GNSS_Date_Converter::on_lineEditDateConverterYear_textEdited()
{
    int             year;
    int             doy;
    int             sodint;
    int             GPSweek;
    int             DoW;
    double          SoW;
    double          SoD;
    TTime           t;
    QDate           date;
    QTime           time;

    if (uiDate->lineEditDateConverterYear->text()=="" || uiDate->lineEditDateConverterDoY->text()=="" || uiDate->lineEditDateConverterSoD->text()=="")  {
        return;
    }

    //Fill Ttime struct
    year=uiDate->lineEditDateConverterYear->text().toInt();
    doy=uiDate->lineEditDateConverterDoY->text().toInt();
    SoD=uiDate->lineEditDateConverterSoD->text().toDouble();

    if(year<1980||doy<1||(year==1980 && doy<6)) return;

    sodint=static_cast<int>(SoD);
    t.MJDN=static_cast<int>(this->yeardoy2MJDN (year,doy, sodint));
    t.SoD=SoD;
    //Fill QDate and QTime
    this->doy2date(year, doy, &date);
    this->SoD2time(SoD,&time);
    //Get GPSWeek and SoW
    this->ttime2gpsweek(&t, &GPSweek, &DoW, &SoW);

    //Fill QDateTime Widget
    uiDate->dateTimeEditDateConverterCalendar->blockSignals(true);
    uiDate->dateTimeEditDateConverterCalendar->setDate(date);
    uiDate->dateTimeEditDateConverterCalendar->setTime(time);
    uiDate->dateTimeEditDateConverterCalendar->blockSignals(false);

    //Fill GPSweek and SoW
    uiDate->lineEditDateConverterGPSWeek->setText(QString("%1").arg(GPSweek));
    uiDate->lineEditDateConverterDoW->setText(QString("%1").arg(DoW));
    uiDate->lineEditDateConverterSoW->setText(QString("%1").arg(SoW,0,'g',9));

    //Fill MJDN and SoD
    uiDate->lineEditDateConverterMJDN->setText(QString("%1").arg(t.MJDN));
    uiDate->lineEditDateConverterSoD_MJDN->setText(QString("%1").arg(SoD,0,'g',8));

}

void GNSS_Date_Converter::on_lineEditDateConverterDoY_textEdited()
{
    this->on_lineEditDateConverterYear_textEdited();
}

void GNSS_Date_Converter::on_lineEditDateConverterSoD_textEdited()
{
    this->on_lineEditDateConverterYear_textEdited();
}

void GNSS_Date_Converter::on_lineEditDateConverterGPSWeek_textEdited()
{
    QDate       date;
    QTime       time;
    struct tm   tmstruct;
    TTime       t;
    int         GPSweek;
    int         DoW;
    int         year;
    double      doy;
    double      SoW;
    double      SoD;

    if (uiDate->lineEditDateConverterGPSWeek->text()=="" || uiDate->lineEditDateConverterSoW->text()=="")  {
        return;
    }

    GPSweek=uiDate->lineEditDateConverterGPSWeek->text().toInt();
    SoW=uiDate->lineEditDateConverterSoW->text().toDouble();

    if(GPSweek<0||SoW<0.) return;

    //Fill TTime
    t=this->gpsws2ttime(GPSweek,SoW);
    //Fill tm struct
    this->t2tm (&t, &tmstruct, &SoD);
    //Fill QDate QTime
    this->tmstruct2datetime(&tmstruct, &date,&time,SoD);
    //Fill Year/DoY
    this->t2doy (&t,&year, &doy);

    //Fill QDateTime Widget
    uiDate->dateTimeEditDateConverterCalendar->blockSignals(true);
    uiDate->dateTimeEditDateConverterCalendar->setDate(date);
    uiDate->dateTimeEditDateConverterCalendar->setTime(time);
    uiDate->dateTimeEditDateConverterCalendar->blockSignals(false);

    //Fill DoW
    DoW=static_cast<int>(static_cast<double>(SoW)/86400.0);
    uiDate->lineEditDateConverterDoW->setText(QString("%1").arg(DoW));

    //Fill Year/DoY/SoD
    uiDate->lineEditDateConverterYear->setText(QString("%1").arg(year));
    uiDate->lineEditDateConverterDoY->setText(QString("%1").arg(static_cast<int>(doy)));
    uiDate->lineEditDateConverterSoD->setText(QString("%1").arg(t.SoD,0,'g',8));

    //Fill MJDN and SoD
    uiDate->lineEditDateConverterMJDN->setText(QString("%1").arg(t.MJDN));
    uiDate->lineEditDateConverterSoD_MJDN->setText(QString("%1").arg(t.SoD,0,'g',8));

}

void GNSS_Date_Converter::on_lineEditDateConverterDoW_textEdited()
{
    int     DoW;
    int     DoW_SoW;
    double  SoD;
    double  SoW;

    if (uiDate->lineEditDateConverterGPSWeek->text()=="" || uiDate->lineEditDateConverterSoW->text()=="")  {
        return;
    }

    DoW = uiDate->lineEditDateConverterDoW->text().toInt();
    SoW = uiDate->lineEditDateConverterSoW->text().toDouble();

    if(DoW<0||SoW<0.) return;

    DoW_SoW = static_cast<int>(SoW/86400.0);
    SoD = SoW-DoW_SoW*86400;
    SoW = static_cast<double>(DoW)*86400. + SoD;

    uiDate->lineEditDateConverterSoW->setText(QString("%1").arg(SoW,0,'g',9));

    this->on_lineEditDateConverterGPSWeek_textEdited();



}

void GNSS_Date_Converter::on_lineEditDateConverterSoW_textEdited()
{
    this->on_lineEditDateConverterGPSWeek_textEdited();
}

void GNSS_Date_Converter::on_lineEditDateConverterMJDN_textEdited()
{
    QDate       date;
    QTime       time;
    struct tm   tmstruct;
    TTime       t;
    int         GPSweek;
    int         DoW;
    int         year;
    double      doy;
    double      SoW;
    double      SoD;

    if (uiDate->lineEditDateConverterMJDN->text()=="" || uiDate->lineEditDateConverterSoD_MJDN->text()=="")  {
        return;
    }


    //Fill TTime struct
    t.MJDN=uiDate->lineEditDateConverterMJDN->text().toInt();
    t.SoD=uiDate->lineEditDateConverterSoD_MJDN->text().toDouble();

    if(t.MJDN<44244||t.SoD<0.) return; //MJDN 44244 is 06/01/1980, or GPSWeek/DoW 0/0, the start of GPS time

    //Fill tm struct
    this->t2tm (&t, &tmstruct, &SoD);
    //Get GPSWeek and SoW
    this->ttime2gpsweek(&t, &GPSweek, &DoW, &SoW);
    //Fill QDate QTime
    this->tmstruct2datetime(&tmstruct, &date,&time,SoD);
    //Fill Year/DoY
    this->t2doy (&t,&year, &doy);

    //Fill QDateTime Widget
    uiDate->dateTimeEditDateConverterCalendar->blockSignals(true);
    uiDate->dateTimeEditDateConverterCalendar->setDate(date);
    uiDate->dateTimeEditDateConverterCalendar->setTime(time);
    uiDate->dateTimeEditDateConverterCalendar->blockSignals(false);

    //Fill GPSweek and SoW
    uiDate->lineEditDateConverterGPSWeek->setText(QString("%1").arg(GPSweek));
    uiDate->lineEditDateConverterDoW->setText(QString("%1").arg(DoW));
    uiDate->lineEditDateConverterSoW->setText(QString("%1").arg(SoW,0,'g',9));

    //Fill Year/DoY/SoD
    uiDate->lineEditDateConverterYear->setText(QString("%1").arg(year));
    uiDate->lineEditDateConverterDoY->setText(QString("%1").arg(static_cast<int>(doy)));
    uiDate->lineEditDateConverterSoD->setText(QString("%1").arg(t.SoD,0,'g',8));

}

void GNSS_Date_Converter::on_lineEditDateConverterSoD_MJDN_textEdited()
{
    this->on_lineEditDateConverterMJDN_textEdited();
}

//Does the modulo mod of a number
double GNSS_Date_Converter::modulo (double a, double mod) {
    return a - (static_cast<int>(a/mod))*mod;
}

////////////////////////////////////////////////////
// Date Conversion functions

//Convert from tm struct to QDate and QTime
void GNSS_Date_Converter::tmstruct2datetime(struct  tm *tmstruct, QDate *date, QTime *time, double SoD) {
    int ms;
    ms=static_cast<int>(round((SoD-static_cast<double>(static_cast<int>(SoD)))*1000.));
    date->setDate(tmstruct->tm_year+1900,tmstruct->tm_mon+1, tmstruct->tm_mday);
    time->setHMS(tmstruct->tm_hour,tmstruct->tm_min,tmstruct->tm_sec,ms);
}

//Convert from QDate and QTime to tm struct
void GNSS_Date_Converter::datetime2tmstruct(struct  tm *tmstruct, QDate *date, QTime *time) {
    tmstruct->tm_year=date->year()-1900;
    tmstruct->tm_yday=date->dayOfYear()-1;
    tmstruct->tm_mon=date->month()-1;
    tmstruct->tm_mday=date->day();

    tmstruct->tm_hour=time->hour();
    tmstruct->tm_min=time->minute();
    tmstruct->tm_sec=time->second();
}

//Convert from tm struct to MJDN
int GNSS_Date_Converter::MJDN (struct tm *tm) {
    int y,m;

    y = tm->tm_year + 1900;
    m = tm->tm_mon + 1;
    if (m<=2) {
        y--;
        m+=12;
    }

    return static_cast<int>(365.25*y) + static_cast<int>(30.6001*(m+1)) + tm->tm_mday - 679019;
}

//Convert from tm struct to TTime
void GNSS_Date_Converter::tm2t (TTime *t, struct tm *tm, double *seconds) {

    t->MJDN=MJDN(tm);
    t->SoD=*seconds;
}

//Convert from TTime to tm struct
void GNSS_Date_Converter::t2tm (TTime *t, struct tm *tm, double *seconds) {
    int             year;
    int             day_of_month;
    int             month_days;
    int             month_number;
    double          doy;

    t2doy(t,&year,&doy);

    tday_of_month(t,&day_of_month, &month_days, &month_number);

    //IMPORTANT NOTE!! Read man page ctime ('man ctime') to understand how the system tm structure is defined
    tm->tm_year = year - 1900;  // The number of years since 1900.
    tm->tm_mday = day_of_month; // The day of the month, in the range 1 to 31.
    tm->tm_yday = static_cast<int>(doy) -1;  // The number of days since January 1, in the range 0 to 365
    tm->tm_mon = month_number-1;    // The number of months since January, in the range 0 to 11.
    tm->tm_hour = static_cast<int>(t->SoD/3600.); // The number of hours past midnight, in the range 0 to 23.
    tm->tm_min = static_cast<int>(modulo(t->SoD,3600.)/60.); // The number of minutes after the hour, in the range 0 to 59.
    tm->tm_sec = static_cast<int>(modulo(t->SoD,60.)); // The number of seconds after the minute, normally in the range 0 to 59, but can be up to 60 to allow for leap seconds.
    tm->tm_isdst = -1;  // A  flag that indicates whether daylight saving time is in effect at the time described.  The value is positive if
                //    daylight saving time is in effect, zero if it is not, and negative if the information is not available.
    *seconds =  modulo(t->SoD,60);
}

//Get the Year/doy from a TTime structure
void GNSS_Date_Converter::t2doy (TTime *t, int *year, double *doy) {
    const int   MJD_1980 = 44239;
    int         day;
    int         ref = 1980;
    int         day_aux;
    int         iy;

    day = t->MJDN - MJD_1980;

    day_aux = static_cast<int>(modulo(day,1461.));
    if (day_aux>365) {
        day_aux -= 366;
        *doy = modulo (day_aux,365.) + 1;
        iy = static_cast<int>(static_cast<double>(day_aux)/365.) + 1;
    } else {
        *doy = static_cast<double>(day_aux + 1);
        iy = 0;
    }
    *year = ref + 4*static_cast<int>(static_cast<double>(day)/1461.) + iy;
    *doy += t->SoD/86400.;
}

//Transforms between GPSweek and Seconds of Week to TTime structure
TTime GNSS_Date_Converter::gpsws2ttime (int GPSweek, double SoW) {
    TTime       t;
    int         DoW;

    // GPSweek = 0 and SoW = 0 corresponds to MJDN = 44244
    // Check if Seconds of week is negative (meaning that is from previous week)
    if(SoW<0) {
        SoW+=604800.;
        GPSweek--;
    } else if (SoW>=604800.) {
        SoW-=604800.;
        GPSweek++;
    }
    DoW = static_cast<int>(SoW/86400.0);
    t.MJDN = static_cast<int>(44244 + GPSweek * 7.0 + DoW);
    t.SoD = SoW - DoW*86400.0;

    return t;
}

//Get the modified julian day from Year/DoY/SoD
double GNSS_Date_Converter::yeardoy2MJDN (int year, int doy, int sod) {
    double tmp;

    tmp = static_cast<int>(365.25 * (year-1)) + 428 + doy;
    tmp = tmp + 1720981.5 + static_cast<double>(sod)/86400. - 2400000.5;

    return tmp;
}


//Transforms between TTime structure to GPSweek (without rollover) and Seconds of Week
void GNSS_Date_Converter::ttime2gpsweek (TTime *t, int *GPSweek, int *DoW, double *SoW) {
    int gpsday;

    //44244 comes from adding 2400000.5 to convert to Julian Date and then substracting 2444244.5 to get the first day of GPS time
    gpsday = t->MJDN - 44244;
    *DoW = abs(gpsday%7);

    *GPSweek = static_cast<int>(gpsday - (gpsday%7)) / 7;
    *SoW = static_cast<double>(*DoW) * 86400. + t->SoD;
}

//Compute day of month from Ttime structure
void GNSS_Date_Converter::tday_of_month (TTime *t, int *day_of_month, int *month_days, int *month_number) {
    int         year;
    int         leapyear = 0;
    int         daysum = 0, prevdaysum = 0;
    double      doy;

    // The following array has the number of days for each month, for a normal year and for a leap year
    static int number_days_month[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};

    t2doy(t,&year,&doy);

    // Check if we are in a leap year
    if ( year%400 == 0 )        leapyear = 1;
    else if ( year%100 == 0 )   leapyear = 0;
    else if ( year%4 == 0 )     leapyear = 1;
    else                        leapyear = 0;


    // Check for the month we are currently in
    *month_number = 0;
    *month_days = 0;
    while ( *month_days == 0 ) {
        daysum += number_days_month[leapyear][*month_number];
        if ( static_cast<int>(doy) <= daysum ) {
            *month_days = number_days_month[leapyear][*month_number];
            *day_of_month = static_cast<int>(doy) - prevdaysum;
        }
        *month_number = *month_number + 1;
        prevdaysum = daysum;
    }
}

//Convert Year/DoY to QDate
void GNSS_Date_Converter::doy2date (int year, int doy, QDate *date) {
    int i = -1;
    int res, month, day;
    int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ( doy > 366 ) return;

    if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 )
        daysmonth[2] += 1;

    res = doy;
    while ( res > 0 ) {
        i += 1;
        res -= daysmonth[i];
    }

    month = i;
    day = daysmonth[i] + res;
    *date=QDate(year,month,day);
}

//Convert SoD to QTime
void GNSS_Date_Converter::SoD2time (double SoD,QTime *time) {
    int hour, minute,second;
    int ms;
    hour=static_cast<int>(SoD/3600.);
    minute=static_cast<int>(SoD/60.)%60;
    second=static_cast<int>(SoD)%60;
    ms=static_cast<int>(round((SoD-static_cast<double>(static_cast<int>(SoD)))*1000.));

    *time=QTime(hour,minute,second,ms);
}

//Convert from GPSWeek and SoW to QDate and QTime
void GNSS_Date_Converter::GPSTime2DateTime(int GPSWeek, double SoW, QDate *date, QTime *time) {
    int DoW;
    double SoD;

    DoW=static_cast<int>(SoW/86400.0);
    SoD=SoW-DoW*86400;
    *date=QDate(1980,1,6); //Start of GPS time
    *date=date->addDays(qint64(GPSWeek*7+DoW));
    SoD2time(SoD,time);
}
