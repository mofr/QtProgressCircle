#pragma once

#include "ProgressCircle.h"
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

class DemoItem : public QWidget
{
public:
    explicit DemoItem(QString text, QWidget * parent = 0) :
        QWidget(parent)
    {
        setStyleSheet(".QWidget{border-bottom: 1px solid lightgrey;}");
        QHBoxLayout * layout = new QHBoxLayout(this);
        layout->setSpacing(12);
        progressCircle = new ProgressCircle();
        progressCircle->setFixedSize(30, 30);
        layout->addWidget(progressCircle);
        label = new QLabel(text);
        layout->addWidget(label, 1);
        QPushButton * closeButton = new QPushButton(tr("Delete"));
        connect(closeButton, &QPushButton::clicked, this, &QObject::deleteLater);
        layout->addWidget(closeButton);

        QPropertyAnimation * progressCircleAnimation = new QPropertyAnimation(progressCircle, "outerRadius", progressCircle);
        progressCircleAnimation->setDuration(750);
        progressCircleAnimation->setEasingCurve(QEasingCurve::OutQuad);
        progressCircleAnimation->setStartValue(0.0);
        progressCircleAnimation->setEndValue(1.0);
        progressCircleAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void finish(bool success)
    {
        QPropertyAnimation * animation = new QPropertyAnimation(progressCircle, "outerRadius", progressCircle);
        animation->setDuration(1500);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->setEndValue(0.5);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        animation = new QPropertyAnimation(progressCircle, "innerRadius", progressCircle);
        animation->setDuration(750);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->setEndValue(0.0);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        QColor color = success ? QColor(155,219,58) : QColor(255,100,100);

        animation = new QPropertyAnimation(progressCircle, "color", progressCircle);
        animation->setDuration(750);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->setEndValue(color);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        label->setText(success ? "Successfully finished" : "Aborted");
    }

    ProgressCircle * progressCircle;

private:
    QLabel * label;
};
