#include <QApplication>
#include <QQmlApplicationEngine>
#include "window.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    /*QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("UsageTracker", "Main");

    Window window;
    window.show();
    return QGuiApplication::exec();
    */
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        auto choice = QMessageBox::critical(nullptr, QObject::tr("Systray"),
                                            QObject::tr("I couldn't detect any system tray on this system."),
                                            QMessageBox::Close | QMessageBox::Ignore);
        if (choice == QMessageBox::Close)
            return 1;
        // Otherwise "lurk": if a system tray is started later, the icon will appear.
    }
    QApplication::setQuitOnLastWindowClosed(false);

    Window window;
    window.show();
    return app.exec();
}
