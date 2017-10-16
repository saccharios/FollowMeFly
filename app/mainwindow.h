#pragma once

#include <QMainWindow>
#include <QTimer>
#include "communication/CrazyRadio.h"
#include "communication/CrazyFlie.h"
#include "cameraviewpainter.h"
#include "trackingcolor.h"
#include "imageprocess/camera.h"
#include "imageprocess/extractcolor.h"
#include "control/commander.h"
#include <QTableView>
#include "actual_values_model.h"
#include "parameter_model.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_disconnectRadio_clicked();
    void on_connectRadio_clicked();
    void on_radioSettings_Options_currentIndexChanged(int index);
    void on_exitApp_clicked();
    void display_sensor_values();
    void display_connection_timeout_box();
    void display_not_connecting_box();
    void on_actionExit_triggered();
    void on_verticalSlider_hue_valueChanged(int value);
    void on_pushButton_CameraOnlyMode_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_hoverMode_clicked();

    void RePaintCameraViewPainter() {_cameraViewPainter.repaint();}
    void UpdateCamera();
    void UpdateCrazyFlie();


    void on_pushButton_SafeLandingMode_clicked();


    void on_pushButton_ActualValues_clicked();

    void on_pushButton_ParameterTable_clicked();

    void on_pushButton_TestAddElement_clicked();

    void on_pushButton_TestRemoveElement_clicked();

private:
    // GUI Windows and Widgets
    Ui::MainWindow* ui;
    QTableView* _actualValuesTable;
    QTableView* _parameterTable;

    std::vector<TOCElement> _dataForActualValuesModel;
    ActualValuesModel _actualValuesModel;
    ParameterModel _parameterModel;

    // Timer
    QTimer _timer_t0;
    QTimer _timer_t1;
    QTimer _timer_t2;

    // Function related
    CrazyRadio _crazyRadio;
    Crazyflie _crazyFlie;
    CameraViewPainter _cameraViewPainter;
    TrackingColor _trackingColor;
    Camera _camera;
    ExtractColor _extractColor;
    Commander _commander;


    void DisplayConnectionStatus();
};
