#pragma once
#include <QObject>
#include <QColor>
#include "opencv2/opencv.hpp"
#include "ball_kalman_filter.h"
#include "math/types.h"
#include "time_levels.h"
#include "camera.h"
class ExtractColor :  public QObject
{
    Q_OBJECT

public:
    ExtractColor(QColor const & color) :
        _colorToFilter(color),
        _kalmanFilter(1.0, 0.1, 0.0),
        _detectorParams()
    {

        // Change thresholds
        _detectorParams.minThreshold = 10;
        _detectorParams.maxThreshold = 255;
        // Filter by Area.
        _detectorParams.filterByArea = true;
        _detectorParams.minArea = 1;
        _detectorParams.maxArea = 100000;

        // Filter by Circularity
        _detectorParams.filterByCircularity = false;
        _detectorParams.minCircularity = 0.1;

        // Filter by Convexity
        _detectorParams.filterByConvexity = false;
        _detectorParams.minConvexity = 0.87;

        // Filter by Inertia
        _detectorParams.filterByInertia = false;
        _detectorParams.minInertiaRatio = 0.01;

       _blobDetector = cv::SimpleBlobDetector::create(_detectorParams);
    }

public slots:
    void ProcessImage(cv::Mat const & img);
    void Initialize(cv::Mat const & img);

signals:
    void NewDistance(Distance const &);

private:
    QColor const & _colorToFilter;
    BallKalmanFilter _kalmanFilter;

    cv::SimpleBlobDetector _detectorParams;
    cv::SimpleBlobDetector _blobDetector;


    void ConvertToHSV(cv::Mat const & img, cv::Mat & imgHSV, cv::Scalar & colorLower, cv::Scalar colorUpper);
    std::vector<cv::KeyPoint> ExtractKeyPoints(cv::Mat const & img, cv::Mat & imgWithKeypoints);
    void FilterImage(cv::Mat & imgThresholded);
    Distance CalculateDistance(cv::Point2f point,
                               double size,
                               cv::Size cameraSize,
                               double blobSizeToLength,
                               double focalLength,
                               double sizeBall,
                               double fieldOfView);
};
