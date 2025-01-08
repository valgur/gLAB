#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include <QDialog>

namespace Ui {
    class GNSS_Multi_Threading;
}

class GNSS_Multi_Threading : public QDialog
{
    Q_OBJECT

public:
    explicit GNSS_Multi_Threading(QWidget *parent = nullptr);
    ~GNSS_Multi_Threading();

    int nThreads;

private slots:
    void on_spinBoxNumberThreads_valueChanged(int iValue);

    void on_pushButtonNumberThreadsDefault_clicked();
    void on_pushButtonNumberThreadsOk_clicked();
    void on_pushButtonNumberThreadsCancel_clicked();

public:
    void setThreadNumber(int numT);

private:
    Ui::GNSS_Multi_Threading *uiMThread;
};

#endif // MULTI_THREADING_H
