//    Copyright (C) 2019 Jakub Melka
//
//    This file is part of PdfForQt.
//
//    PdfForQt is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    PdfForQt is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with PDFForQt.  If not, see <https://www.gnu.org/licenses/>.

#include "pdfrenderingerrorswidget.h"
#include "pdfdrawwidget.h"
#include "ui_pdfrenderingerrorswidget.h"

namespace pdf
{

PDFRenderingErrorsWidget::PDFRenderingErrorsWidget(QWidget* parent, PDFWidget* pdfWidget) :
    QDialog(parent),
    ui(new Ui::PDFRenderingErrorsWidget)
{
    ui->setupUi(this);

    ui->renderErrorsTreeWidget->setColumnCount(3);
    ui->renderErrorsTreeWidget->setColumnWidth(0, 100);
    ui->renderErrorsTreeWidget->setColumnWidth(1, 300);
    ui->renderErrorsTreeWidget->setHeaderLabels({ tr("Page"), tr("Error type"), tr("Description") });

    Q_ASSERT(pdfWidget);
    std::vector<PDFInteger> currentPages = pdfWidget->getDrawWidget()->getCurrentPages();
    qSort(currentPages);

    QTreeWidgetItem* scrollToItem = nullptr;
    const PDFWidget::PageRenderingErrors* pageRenderingErrors = pdfWidget->getPageRenderingErrors();
    for (const auto& pageRenderingError : *pageRenderingErrors)
    {
        // TODO: udelat realna cisla stranek
        const PDFInteger pageIndex = pageRenderingError.first;
        QTreeWidgetItem* root = new QTreeWidgetItem(ui->renderErrorsTreeWidget, QStringList() << QString::number(pageIndex + 1) << QString() << QString());

        for (const PDFRenderError& error : pageRenderingError.second)
        {
            QString typeString;
            switch (error.type)
            {
                case RenderErrorType::Error:
                {
                    typeString = tr("Error");
                    break;
                }

                case RenderErrorType::NotImplemented:
                {
                    typeString = tr("Not implemented");
                    break;
                }

                default:
                {
                    Q_ASSERT(false);
                    break;
                }
            }

            new QTreeWidgetItem(root, QStringList() << QString() << typeString << error.message);
        }

        bool isCurrentPage = std::binary_search(currentPages.cbegin(), currentPages.cend(), pageIndex);
        ui->renderErrorsTreeWidget->setItemExpanded(root, isCurrentPage);

        if (isCurrentPage && !scrollToItem)
        {
            scrollToItem = root;
        }
    }

    if (scrollToItem)
    {
        ui->renderErrorsTreeWidget->scrollToItem(scrollToItem, QAbstractItemView::EnsureVisible);
    }
}

PDFRenderingErrorsWidget::~PDFRenderingErrorsWidget()
{
    delete ui;
}

}   // namespace pdf
