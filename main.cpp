#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "datamodel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Create and expose the DataModel instance to QML
    DataModel dataModel;

    engine.rootContext()->setContextProperty("dataModel", &dataModel);

    // Ensure application exits if the QML object fails to load
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
        );

    // Load QML from the module (since we are not using a qrc file)
    engine.loadFromModule("RealChartApp", "Main");

    // Optionally start the UDP receiver automatically
    //dataModel.startUdpReceiver();

    return app.exec();
}
