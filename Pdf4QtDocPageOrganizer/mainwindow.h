//    Copyright (C) 2021 Jakub Melka
//
//    This file is part of Pdf4Qt.
//
//    Pdf4Qt is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    with the written consent of the copyright owner, any later version.
//
//    Pdf4Qt is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with Pdf4Qt.  If not, see <https://www.gnu.org/licenses/>.

#ifndef PDFDOCPAGEORGANIZER_MAINWINDOW_H
#define PDFDOCPAGEORGANIZER_MAINWINDOW_H

#include <QMainWindow>

#include "pageitemmodel.h"
#include "pageitemdelegate.h"

namespace Ui
{
class MainWindow;
}

namespace pdfdocpage
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent);
    virtual ~MainWindow() override;

    QSize getMinPageImageSize() const;
    QSize getDefaultPageImageSize() const;
    QSize getMaxPageImageSize() const;

private slots:
    void on_actionClose_triggered();
    void on_actionAddDocument_triggered();
    void updateActions();

private:
    void loadSettings();
    void saveSettings();
    void addDocument(const QString& fileName);

    struct Settings
    {
        QString directory;
    };

    Ui::MainWindow* ui;

    PageItemModel* m_model;
    PageItemDelegate* m_delegate;
    Settings m_settings;
};

}   // namespace pdfdocpage

#endif // PDFDOCPAGEORGANIZER_MAINWINDOW_H
