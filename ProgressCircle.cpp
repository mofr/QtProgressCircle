/////////////////////////////////////////////////////////////////////////////
// Date of creation: 04.07.2013
// Creator: Alexander Egorov aka mofr
// Authors: mofr
/////////////////////////////////////////////////////////////////////////////

#include "ProgressCircle.h"
#include <QPainter>
#include <QPixmapCache>

ProgressCircle::ProgressCircle(QWidget *parent) :
    QWidget(parent),
    mValue(0),
    mMaximum(0),
    mInnerRadius(0.6),
    mOuterRadius(1.0),
    mColor(110,190,235),
    mVisibleValue(0),
    mValueAnimation(this, "visibleValue"),
    mInfiniteAnimation(this, "infiniteAnimationValue"),
    mInfiniteAnimationValue(0.0)
{
    mInfiniteAnimation.setLoopCount(-1);//infinite
    mInfiniteAnimation.setDuration(1000);
    mInfiniteAnimation.setStartValue(0.0);
    mInfiniteAnimation.setEndValue(1.0);
    mInfiniteAnimation.start();
}

int ProgressCircle::value() const
{
    return mValue;
}

int ProgressCircle::maximum() const
{
    return mMaximum;
}

qreal ProgressCircle::innerRadius() const
{
    return mInnerRadius;
}

qreal ProgressCircle::outerRadius() const
{
    return mOuterRadius;
}

QColor ProgressCircle::color() const
{
    return mColor;
}

void ProgressCircle::setValue(int value)
{
    if(value < 0) value = 0;

    if(mValue != value)
    {
        mValueAnimation.stop();
        mValueAnimation.setEndValue(value);
        mValueAnimation.setDuration(250);
        mValueAnimation.start();

        mValue = value;
        emit valueChanged(value);
    }
}

void ProgressCircle::setMaximum(int maximum)
{
    if(maximum < 0) maximum = 0;

    if(mMaximum != maximum)
    {
        mMaximum = maximum;
        update();
        emit maximumChanged(maximum);

        if(mMaximum == 0)
        {
            mInfiniteAnimation.start();
        }
        else
        {
            mInfiniteAnimation.stop();
        }
    }
}

void ProgressCircle::setInnerRadius(qreal innerRadius)
{
    if(innerRadius > 1.0) innerRadius = 1.0;
    if(innerRadius < 0.0) innerRadius = 0.0;

    if(mInnerRadius != innerRadius)
    {
        mInnerRadius = innerRadius;
        update();
    }
}

void ProgressCircle::setOuterRadius(qreal outerRadius)
{
    if(outerRadius > 1.0) outerRadius = 1.0;
    if(outerRadius < 0.0) outerRadius = 0.0;

    if(mOuterRadius != outerRadius)
    {
        mOuterRadius = outerRadius;
        update();
    }
}

void ProgressCircle::setColor(QColor color)
{
    if(color != mColor)
    {
        mColor = color;
        update();
    }
}

QRectF squared(QRectF rect)
{
    if(rect.width() > rect.height())
    {
        qreal diff = rect.width() - rect.height();
        return rect.adjusted(diff/2, 0, -diff/2, 0);
    }
    else
    {
        qreal diff = rect.height() - rect.width();
        return rect.adjusted(0, diff/2, 0, -diff/2);
    }
}

void ProgressCircle::paintEvent(QPaintEvent *)
{
    QPixmap pixmap;
    if (!QPixmapCache::find(key(), pixmap))
    {
        pixmap = generatePixmap();
        QPixmapCache::insert(key(), pixmap);
    }

    // Draw pixmap at center of item
    QPainter painter(this);
    painter.drawPixmap( 0.5 * ( width() - pixmap.width() ), 0.5 * ( height() - pixmap.height() ), pixmap );
}

void ProgressCircle::setInfiniteAnimationValue(qreal value)
{
    mInfiniteAnimationValue = value;
    update();
}

void ProgressCircle::setVisibleValue(int value)
{
    if(mVisibleValue != value)
    {
        mVisibleValue = value;
        update();
    }
}

QString ProgressCircle::key() const
{
    return QString("%1,%2,%3,%4,%5,%6,%7,%8")
            .arg(mInfiniteAnimationValue)
            .arg(mVisibleValue)
            .arg(mMaximum)
            .arg(mInnerRadius)
            .arg(mOuterRadius)
            .arg(width())
            .arg(height())
            .arg(mColor.rgb())
            ;
}

QPixmap ProgressCircle::generatePixmap() const
{
    QPixmap pixmap(squared(rect()).size().toSize());
    pixmap.fill(QColor(0,0,0,0));
    QPainter painter(&pixmap);

    painter.setRenderHint(QPainter::Antialiasing, true);

    QRectF rect = pixmap.rect().adjusted(1,1,-1,-1);
    qreal margin = rect.width()*(1.0 - mOuterRadius)/2.0;
    rect.adjust(margin,margin,-margin,-margin);
    qreal innerRadius = mInnerRadius*rect.width()/2.0;

    //background grey circle
    painter.setBrush(QColor(225,225,225));
    painter.setPen(QColor(225,225,225));
    painter.drawPie(rect, 0, 360*16);

    painter.setBrush(mColor);
    painter.setPen(mColor);

    if(mMaximum == 0)
    {
        //draw as infinite process
        int startAngle = -mInfiniteAnimationValue * 360 * 16;
        int spanAngle = 0.15 * 360 * 16;
        painter.drawPie(rect, startAngle, spanAngle);
    }
    else
    {
        int value = qMin(mVisibleValue, mMaximum);
        int startAngle = 90 * 16;
        int spanAngle = -qreal(value) * 360 * 16 / mMaximum;

        painter.drawPie(rect, startAngle, spanAngle);
    }

    //inner circle and frame
    painter.setBrush(QColor(255,255,255));
    painter.setPen(QColor(0,0,0, 60));
    painter.drawEllipse(rect.center(), innerRadius, innerRadius);

    //outer frame
    painter.drawArc(rect, 0, 360*16);

    return pixmap;
}

qreal ProgressCircle::infiniteAnimationValue() const
{
    return mInfiniteAnimationValue;
}

int ProgressCircle::visibleValue() const
{
    return mVisibleValue;
}
