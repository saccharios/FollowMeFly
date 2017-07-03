#pragma once
#include <QWidget>




class CameraViewPainter : public QWidget
{
//    Q_OBJECT
public:
    CameraViewPainter(float const & roll, float const & yaw, float const & pitch);
    void paintEvent(QPaintEvent* /*event*/) override;
public slots:
private slots:
private:
    static constexpr qreal _x_max = 60; // 2*yaw_max is the total x coord
    static constexpr qreal _y_max = 30; // 2*pitch_max is the total y coord

    float const & _roll;
    float const & _yaw;
    float const & _pitch;

    QPoint World2CameraCoord(QPointF point);
    void PaintHorizontalLine(QPainter & painter, float roll,float pitch);
    void PaintVerticalLine(QPainter & painter, float roll, float yaw);
    void DrawGround(QPainter & painter, float roll, float pitch);

};




