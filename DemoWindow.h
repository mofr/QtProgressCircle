#pragma once

#include "ui_DemoWindow.h"
#include "DemoItem.h"

#include <QMainWindow>
#include <QScopedPointer>
#include <QBoxLayout>
#include <QLabel>
#include <QTimer>


class DemoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DemoWindow(QWidget *parent = 0) :
        QMainWindow(parent),
        ui(new Ui::DemoWindow)
    {
        ui->setupUi(this);
        ui->itemListLayout->addStretch();

        connect(ui->indefiniteButton, &QPushButton::clicked, this, &DemoWindow::addIndefinite);
        connect(ui->successfulButton, &QPushButton::clicked, this, &DemoWindow::addSuccessful);
        connect(ui->abortedButton, &QPushButton::clicked, this, &DemoWindow::addAborted);
    }

public slots:
    void addIndefinite()
    {
        DemoItem * item = new DemoItem("Indefinite process");
        ui->itemListLayout->insertWidget(0, item);
    }

    void addSuccessful()
    {
        DemoItem * item = new DemoItem("Working");
        ui->itemListLayout->insertWidget(0, item);
        item->progressCircle->setMaximum(100);

        QTimer::singleShot(500, item, [=](){
            item->progressCircle->setValue(10);
        });

        QTimer::singleShot(1000, item, [=](){
            item->progressCircle->setValue(30);
        });

        QTimer::singleShot(2000, item, [=](){
            item->progressCircle->setValue(60);
        });

        QTimer::singleShot(2500, item, [=](){
            item->progressCircle->setValue(70);
        });

        QTimer::singleShot(3300, item, [=](){
            item->progressCircle->setValue(85);
        });

        QTimer::singleShot(4000, item, [=](){
            item->progressCircle->setValue(100);
            item->finish(true);
        });
    }

    void addAborted()
    {
        DemoItem * item = new DemoItem("Working");
        ui->itemListLayout->insertWidget(0, item);
        item->progressCircle->setMaximum(100);

        QTimer::singleShot(500, item, [=](){
            item->progressCircle->setValue(10);
        });

        QTimer::singleShot(1000, item, [=](){
            item->progressCircle->setValue(30);
        });

        QTimer::singleShot(1500, item, [=](){
            item->progressCircle->setValue(65);
        });

        QTimer::singleShot(2000, item, [=](){
            item->finish(false);
        });
    }

private:
    QScopedPointer<Ui::DemoWindow> ui;
};
