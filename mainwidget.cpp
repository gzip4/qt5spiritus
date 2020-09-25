#include <QDoubleValidator>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QDebug>
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "mydelegate.h"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(11);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

    auto headers = QStringList()
            << QString::fromUtf8("Колво, мл")
            << QString::fromUtf8("Обороты, %")
            << QString::fromUtf8("Чистый, мл")
            << QString::fromUtf8("Водка, мл");

    ui->tableWidget->setHorizontalHeaderLabels(headers);
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setItemDelegate(new MyDelegate(this));

    connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), SLOT(onCellChanged(int, int)));

    for (int row = 0; row < ui->tableWidget->rowCount(); row++ ) {
        for (int col = 0; col < 3; col++) {
            auto item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->tableWidget->setItem(row, col, item);
        }
        auto i3 = new QTableWidgetItem(); i3->setFlags(i3->flags() ^ Qt::ItemIsEditable);
        i3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 3, i3);
    }
}

static double toDouble(QString s)
{
    bool ok;
    s.replace(",", ".");
    double r = s.toDouble(&ok);
    if (!ok) r = 0.0;
    return r;
}

void MainWidget::onCellChanged(int row, int column)
{
    qDebug() << row << column << ui->tableWidget->item(row, column)->text();

    if (ui->tableWidget->item(row, column)->text().length() == 0) {
        return;
    }

    double val0 = toDouble(ui->tableWidget->item(row, 0)->text());
    double val1 = toDouble(ui->tableWidget->item(row, 1)->text());
    double val2 = toDouble(ui->tableWidget->item(row, 2)->text());
    double val3 = 0.0;
    switch (column) {
    case 0:
    case 1:
        val2 = val0 * val1 / 100.0;
        val3 = val2 * 100.0 / 40.0;
        ui->tableWidget->item(row, 2)->setText(QString().setNum(val2));
        ui->tableWidget->item(row, 3)->setText(QString().setNum(val3));
        break;
    case 2:
        if (val0 == 0.0) {
            val1 = 0.0;
        } else {
            val1 = val2 * 100 / val0;
        }
        val3 = val2 * 100.0 / 40.0;
        ui->tableWidget->item(row, 1)->setText(QString().setNum(val1));
        ui->tableWidget->item(row, 3)->setText(QString().setNum(val3));
        break;
    }

    double sum0 = 0.0, sum1 = 0.0, sum2 = 0.0, sum3;
    for (int row = 0; row < ui->tableWidget->rowCount() - 1; row++) {
        sum0 += toDouble(ui->tableWidget->item(row, 0)->text());
        sum2 += toDouble(ui->tableWidget->item(row, 2)->text());
    }

    int rlast = ui->tableWidget->rowCount() - 1;
    if (sum0 == 0.0) {
        ui->tableWidget->item(rlast, 0)->setText("0");
        ui->tableWidget->item(rlast, 1)->setText("0");
        ui->tableWidget->item(rlast, 2)->setText("0");
        ui->tableWidget->item(rlast, 3)->setText("0");
        qDebug() << "Empty";
    } else {
        sum1 = sum2 * 100.0 / sum0;
        sum3 = sum2 * 100.0 / 40.0;
        qDebug() << "Qty:" << sum0 << "Alc%:" << sum1 << "Spirit:" << sum2 << "Vdk:" << sum3;
        ui->tableWidget->item(rlast, 0)->setText(QString().setNum(sum0));
        ui->tableWidget->item(rlast, 1)->setText(QString().setNum(sum1));
        ui->tableWidget->item(rlast, 2)->setText(QString().setNum(sum2));
        ui->tableWidget->item(rlast, 3)->setText(QString().setNum(sum3));
    }

}

MainWidget::~MainWidget()
{
    delete ui;
}

