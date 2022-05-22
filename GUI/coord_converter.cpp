#include "coord_converter.h"
#include "ui_coord_converter.h"
#include "math.h"

GNSS_Coord_converter::GNSS_Coord_converter(QWidget *parent) :
    QDialog(parent),
    uiCoord(new Ui::GNSS_Coord_converter)
{
    uiCoord->setupUi(this);


    #ifdef Q_OS_WIN32
        setMaximumWidth(700);
        setMinimumWidth(700);
    #elif defined Q_OS_MAC
        setMaximumWidth(800);
        setMinimumWidth(800);
    #endif

    QLocale qlocale(QLocale::C);
    qlocale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto ldouble = new QDoubleValidator(-100000000, 100000000,6, this);
    ldouble->setLocale(qlocale); // lineEdit validation for coordinates XYZ
    auto ldoublePositive = new QDoubleValidator(0, 100000000,6, this);
    ldoublePositive->setLocale(qlocale); // lineEdit validation
    auto ldoubleHeight = new QDoubleValidator(-10000, 100000000,6, this);
    ldoubleHeight->setLocale(qlocale); // lineEdit validation for Geocentric Height (-10Km onwards)
    auto lLongitude = new QDoubleValidator(-180, 180,14, this);
    lLongitude->setLocale(qlocale); // lineEdit validation for longitude
    auto lLatitude = new QDoubleValidator(-90, 90,14, this);
    lLatitude->setLocale(qlocale); // lineEdit validation for longitude

    uiCoord->lineEditCoordConvX->setValidator(ldouble);
    uiCoord->lineEditCoordConvY->setValidator(ldouble);
    uiCoord->lineEditCoordConvZ->setValidator(ldouble);
    uiCoord->lineEditCoordConvGeodLon->setValidator(lLongitude);
    uiCoord->lineEditCoordConvGeodLat->setValidator(lLatitude);
    uiCoord->lineEditCoordConvGeodHeight->setValidator(ldoubleHeight);
    uiCoord->lineEditCoordConvGeocLon->setValidator(lLongitude);
    uiCoord->lineEditCoordConvGeocLat->setValidator(lLatitude);
    uiCoord->lineEditCoordConvGeocRadius->setValidator(ldoublePositive);

    uiCoord->lineEditCoordConvX->setText("6378137.0000");
    uiCoord->lineEditCoordConvY->setText("0");
    uiCoord->lineEditCoordConvZ->setText("0");
    this->on_lineEditCoordConvX_textEdited();

}

GNSS_Coord_converter::~GNSS_Coord_converter()
{
    delete uiCoord;
}

void GNSS_Coord_converter::on_pushButtonCoordConvOK_clicked()
{
    this->close();
}

void GNSS_Coord_converter::on_lineEditCoordConvX_textEdited()
{
    double  positionXYZ[3];
    double  positionGeod[3];
    double  positionGeoc[3];

    if (uiCoord->lineEditCoordConvX->text()==""|| uiCoord->lineEditCoordConvY->text()==""|| uiCoord->lineEditCoordConvZ->text()=="") {
        return;
    }
    positionXYZ[0]=uiCoord->lineEditCoordConvX->text().toDouble();
    positionXYZ[1]=uiCoord->lineEditCoordConvY->text().toDouble();
    positionXYZ[2]=uiCoord->lineEditCoordConvZ->text().toDouble();

    //Get geodesic coordinates
    this->XYZ2Geod(positionXYZ,positionGeod);
    //Get geocentric coordinates
    this->XYZ2Geoc(positionXYZ,positionGeoc);

    //Set geodesic coordinates
    uiCoord->lineEditCoordConvGeodLon->setText(QString("%1").arg(positionGeod[1]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeodLat->setText(QString("%1").arg(positionGeod[0]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeodHeight->setText(QString("%1").arg(positionGeod[2],0,'f',4));

    //Set geocentric coordinates
    uiCoord->lineEditCoordConvGeocLon->setText(QString("%1").arg(positionGeoc[1]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeocLat->setText(QString("%1").arg(positionGeoc[0]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeocRadius->setText(QString("%1").arg(positionGeoc[2],0,'f',4));
}

void GNSS_Coord_converter::on_lineEditCoordConvY_textEdited()
{
    this->on_lineEditCoordConvX_textEdited();
}

void GNSS_Coord_converter::on_lineEditCoordConvZ_textEdited()
{
    this->on_lineEditCoordConvX_textEdited();
}

void GNSS_Coord_converter::on_lineEditCoordConvGeodLon_textEdited()
{
    double  positionXYZ[3];
    double  positionGeod[3];
    double  positionGeoc[3];

    if (uiCoord->lineEditCoordConvGeodLat->text()==""|| uiCoord->lineEditCoordConvGeodLon->text()==""|| uiCoord->lineEditCoordConvGeodHeight->text()=="") {
        return;
    }

    positionGeod[0]=uiCoord->lineEditCoordConvGeodLat->text().toDouble()*d2r;
    positionGeod[1]=uiCoord->lineEditCoordConvGeodLon->text().toDouble()*d2r;
    positionGeod[2]=uiCoord->lineEditCoordConvGeodHeight->text().toDouble();

    //Get cartesian coordinates
    this->Geod2XYZ(positionGeod,positionXYZ);
    //Get geocentric coordinates
    this->XYZ2Geoc(positionXYZ,positionGeoc);

    //Set cartesian coordinates
    uiCoord->lineEditCoordConvX->setText(QString("%1").arg(positionXYZ[0],0,'f',4));
    uiCoord->lineEditCoordConvY->setText(QString("%1").arg(positionXYZ[1],0,'f',4));
    uiCoord->lineEditCoordConvZ->setText(QString("%1").arg(positionXYZ[2],0,'f',4));

    //Set geocentric coordinates
    uiCoord->lineEditCoordConvGeocLon->setText(QString("%1").arg(positionGeoc[1]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeocLat->setText(QString("%1").arg(positionGeoc[0]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeocRadius->setText(QString("%1").arg(positionGeoc[2],0,'f',4));

}

void GNSS_Coord_converter::on_lineEditCoordConvGeodLat_textEdited()
{
    this->on_lineEditCoordConvGeodLon_textEdited();
}

void GNSS_Coord_converter::on_lineEditCoordConvGeodHeight_textEdited()
{
    this->on_lineEditCoordConvGeodLon_textEdited();
}

void GNSS_Coord_converter::on_lineEditCoordConvGeocLon_textEdited()
{
    double  positionXYZ[3];
    double  positionGeod[3];
    double  positionGeoc[3];

    if (uiCoord->lineEditCoordConvGeocLat->text()==""|| uiCoord->lineEditCoordConvGeocLon->text()==""|| uiCoord->lineEditCoordConvGeocRadius->text()=="") {
        return;
    }

    positionGeoc[0]=uiCoord->lineEditCoordConvGeocLat->text().toDouble()*d2r;
    positionGeoc[1]=uiCoord->lineEditCoordConvGeocLon->text().toDouble()*d2r;
    positionGeoc[2]=uiCoord->lineEditCoordConvGeocRadius->text().toDouble();

    //Get cartesian coordinates
    this->Geoc2XYZ(positionGeoc,positionXYZ);
    //Get geodetic coordinates
    this->XYZ2Geod(positionXYZ,positionGeod);

    //Set cartesian coordinates
    uiCoord->lineEditCoordConvX->setText(QString("%1").arg(positionXYZ[0],0,'f',4));
    uiCoord->lineEditCoordConvY->setText(QString("%1").arg(positionXYZ[1],0,'f',4));
    uiCoord->lineEditCoordConvZ->setText(QString("%1").arg(positionXYZ[2],0,'f',4));

    //Set geodesic coordinates
    uiCoord->lineEditCoordConvGeodLon->setText(QString("%1").arg(positionGeod[1]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeodLat->setText(QString("%1").arg(positionGeod[0]*r2d,0,'f',10));
    uiCoord->lineEditCoordConvGeodHeight->setText(QString("%1").arg(positionGeod[2],0,'f',4));

}

void GNSS_Coord_converter::on_lineEditCoordConvGeocLat_textEdited()
{
    this->on_lineEditCoordConvGeocLon_textEdited();
}

void GNSS_Coord_converter::on_lineEditCoordConvGeocRadius_textEdited()
{
    this->on_lineEditCoordConvGeocLon_textEdited();
}

////////////////////////////////////////////////////
// Coordinate Conversion functions

//Convert XYZ to Geodetic
void GNSS_Coord_converter::XYZ2Geod (double *positionXYZ, double *positionNEU) {
    const double    tol = 1e-11;
    const double    a = 6378137.; //a = EARTH_RADIUS = 6378137.
    const double    f = 1/298.257223563;
    const double    b = a*(1-f);
    const double    e2 = (a*a-b*b)/(a*a);
    double          p;
    double          longitude;
    double          latitude,latitudePrev;
    double          xn;
    double          heightOverElipsoide=0.;

    // WGS84 parameters (in meters)
    //positionNEU[0] -> latitude (rad)
    //positionNEU[1] -> longitude (rad)
    //positionNEU[2] -> height (m)

    longitude = atan2(positionXYZ[1],positionXYZ[0]);
    p = sqrt(positionXYZ[0]*positionXYZ[0]+positionXYZ[1]*positionXYZ[1]);
    if (p==0) p=0.00001;
    latitude = atan((positionXYZ[2]/p)/(1-e2));

    latitudePrev = latitude + tol*2; // To overbound the following while
    while (fabs(latitude-latitudePrev) > tol) {
        latitudePrev = latitude;
        xn = a*a/sqrt((a*cos(latitude))*(a*cos(latitude)) + (b*sin(latitude))*(b*sin(latitude)));
        heightOverElipsoide = p/cos(latitude)-xn;
        if ((xn+heightOverElipsoide)!=0)
            latitude = atan((positionXYZ[2]/p)/(1-e2*(xn/(xn+heightOverElipsoide))));
        else
            latitude = 0;
    }

    positionNEU[0] = latitude;
    positionNEU[1] = longitude;
    positionNEU[2] = heightOverElipsoide;
}

//Convert Geodetic to XYZ
void GNSS_Coord_converter::Geod2XYZ (double *positionNEU, double *positionXYZ) {
    const double    a = 6378137.; //a = EARTH_RADIUS = 6378137.
    const double    f = 1/298.257223563;
    const double    b = a*(1-f);
    const double    e2 = (a*a-b*b)/(a*a);
    double          N;

    // WGS84 parameters (in meters)
    //positionNEU[0] -> latitude (rad)
    //positionNEU[1] -> longitude (rad)
    //positionNEU[2] -> height (m)


    N=a/sqrt(1-e2*sin(positionNEU[0])*sin(positionNEU[0]));

    positionXYZ[0] = (N+positionNEU[2])*cos(positionNEU[0])*cos(positionNEU[1]);
    positionXYZ[1] = (N+positionNEU[2])*cos(positionNEU[0])*sin(positionNEU[1]);
    positionXYZ[2] = ((1-e2)*N+positionNEU[2])*sin(positionNEU[0]);
}


//Convert XYZ to Geocentric
void GNSS_Coord_converter::XYZ2Geoc(double *positionXYZ, double *positionGeoc) {

    //positionGeoc[0] -> latitude (rad)
    //positionGeoc[1] -> longitude (rad)
    //positionGeoc[2] -> radius (m)
    //positionGeoc[0]=atan2(sqrt(positionXYZ[0]*positionXYZ[0]+positionXYZ[1]*positionXYZ[1]),positionXYZ[2]);
    if (positionXYZ[2]==0.) {
        positionGeoc[0]=0;
    } else {
        positionGeoc[0]=asin(positionXYZ[2]/(sqrt(positionXYZ[0]*positionXYZ[0]+positionXYZ[1]*positionXYZ[1]+positionXYZ[2]*positionXYZ[2])));
    }
    positionGeoc[1]=atan2(positionXYZ[1],positionXYZ[0]);
    positionGeoc[2]=sqrt(positionXYZ[0]*positionXYZ[0]+positionXYZ[1]*positionXYZ[1]+positionXYZ[2]*positionXYZ[2]);

}

//Convert Geocentric to XYZ
void GNSS_Coord_converter::Geoc2XYZ(double *positionGeoc, double *positionXYZ) {

    //positionGeoc[0] -> latitude (rad)
    //positionGeoc[1] -> longitude (rad)
    //positionGeoc[2] -> radius (m)
    positionXYZ[0]=positionGeoc[2]*cos(positionGeoc[0])*cos(positionGeoc[1]);
    positionXYZ[1]=positionGeoc[2]*cos(positionGeoc[0])*sin(positionGeoc[1]);
    positionXYZ[2]=positionGeoc[2]*sin(positionGeoc[0]);
}
