#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <sqlite3.h>

class Window : public QDialog
{
public:
    Window();
    ~Window();

    void setVisible(bool visible) override;

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();

private:
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    sqlite3* db;
};

#endif // WINDOW_H
