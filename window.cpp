#include "window.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QVBoxLayout>
#include <QLabel>

Window::Window() {
    minimizeAction = new QAction("Mi&nimize", this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction("Ma&ximize", this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction("&Restore", this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction("&Quit", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    connect(
        trayIcon,
        &QSystemTrayIcon::messageClicked,
        this,
        &Window::messageClicked
    );
    connect(
        trayIcon,
        &QSystemTrayIcon::activated,
        this,
        &Window::iconActivated
    );
    trayIcon->setIcon(
        QIcon::fromTheme(QIcon::ThemeIcon::Computer)
    );

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Lol"));
       setLayout(mainLayout);

    trayIcon->show();
    setWindowTitle("Wind");
    resize(400, 300);
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:

        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        break;
    }
}

void Window::showMessage() {
    trayIcon->showMessage(
        "Title",
        "Body",
        QSystemTrayIcon::MessageIcon(),
        4000
    );
}

void Window::messageClicked() {
    QMessageBox::information(
        nullptr,
        "Systray",
        "Sorry, I already gave what help I could.\n"
        "Maybe you should try asking a human?"
    );
}

void Window::setVisible(bool visible) {
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void Window::closeEvent(QCloseEvent* event) {
    if  (!event->spontaneous() || !isVisible())
        return;
    if (!trayIcon->isVisible()) {
        QMessageBox::information(
            this,
            "Systray",
            "Gonna run in backG"
            );
        hide();
        event->ignore();
    }
}