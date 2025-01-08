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
#include "glab_tooltip.h"
#include "ui_glab_tooltip.h"

gLAB_ToolTip::gLAB_ToolTip(QWidget *parent) :
    QDialog(parent),
    uiToolTip(new Ui::gLAB_ToolTip)
{
    uiToolTip->setupUi(this);

    QFont font;
    #ifdef Q_OS_LINUX
      font.setPointSize(9);
    #elif defined(Q_OS_WIN32)
      font.setPointSize(9);
    #elif defined(Q_OS_MAC)
      font.setPointSize(13);
    #endif

    uiToolTip->textBrowserToolTip->setFont(font);
    QPalette pal = uiToolTip->textBrowserToolTip->palette();
    pal.setBrush(QPalette::Base,QColor("#FFFFDC"));
    uiToolTip->textBrowserToolTip->setPalette(pal);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}

gLAB_ToolTip::~gLAB_ToolTip()
{
    delete uiToolTip;
}

int gLAB_ToolTip::tHeight(){
    return static_cast<int>(uiToolTip->textBrowserToolTip->document()->size().height());
}
int gLAB_ToolTip::tWidth(){
    return static_cast<int>(uiToolTip->textBrowserToolTip->document()->size().width());
}
void gLAB_ToolTip::setTooltip(const QString strTooltip){
    uiToolTip->textBrowserToolTip->setText(strTooltip);
}

bool gLAB_ToolTip::event(QEvent *event){
    if (event->type()==QEvent::Leave){
        this->close();
    }
    /*if (event->type()==QEvent::MouseMove){
        int mouseX=;
    }*/
    return QWidget::event(event);
}
