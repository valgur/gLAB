#ifndef GLAB_TOOLTIP_H
#define GLAB_TOOLTIP_H

#include <QDialog>
#include <QFile>
#include "glab_const.h"

namespace Ui {
class gLAB_ToolTip;
}

class gLAB_ToolTip : public QDialog
{
    Q_OBJECT

public:
    explicit gLAB_ToolTip(QWidget *parent = nullptr);
    ~gLAB_ToolTip();

public:
    int tHeight();
    int tWidth();
    void setTooltip(const QString strTooltip);

private:
    Ui::gLAB_ToolTip *uiToolTip;

protected:
    bool event(QEvent *event);
};

#endif // GLAB_TOOLTIP_H
