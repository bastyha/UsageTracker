#include "window.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QVBoxLayout>
#include <QLabel>
#include <sqlite3.h>

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

    sqlite3_open("db.sql", &db);

    sqlite3_exec(
        db,
        "CREATE TABLE person (id INT PRIMARY KEY, name TEXT, age INT);"
        "INSERT INTO person VALUES(1, 'Jánűs', 23);"
        "INSERT INTO person VALUES(2, 'Margit', 36);",
        nullptr,
        nullptr,
        nullptr
        );

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(
        db,
        "SELECT * FROM person;",
        -1,
        &stmt,
        nullptr
        );

    while (1)
    {
        int res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
                qDebug() <<
                    sqlite3_column_int(stmt, 0) << " "<<
                    QString::fromUtf8(sqlite3_column_text(stmt, 1))<< " "<<
                    sqlite3_column_int(stmt, 2);
        }
        else if (res == SQLITE_DONE)
        {
            qDebug() << "Done";
            break;
        }
        else
        {
            qDebug() << res;
            break;
        }
    }


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Number of records"));
    setLayout(mainLayout);

    trayIcon->show();
    setWindowTitle("Computer usage tracker");
    resize(400, 300);
}
Window::~Window(){
    sqlite3_close(db);
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
