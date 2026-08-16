#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QSystemTrayIcon>

class Window : public QDialog
{
public:
    Window();

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
};

#endif // WINDOW_H
