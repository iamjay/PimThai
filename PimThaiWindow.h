#ifndef PIMTHAIWINDOW_H
#define PIMTHAIWINDOW_H

#include <QMainWindow>

#include "ui_PimThaiWindow.h"

#include "JKeyboard.h"
#include "MenuBar.h"
#include "Toaster.h"

class PimThaiWindow : public QMainWindow,
        private Ui::PimThaiWindow
{
    Q_OBJECT

public:
    static const char *activeBufferKey;
    static const char *buffer0Key;
    static const char *buffer1Key;
    static const char *buffer2Key;
    static const char *buffer3Key;
    static const char *predictionEnabledKey;
    static const char *autoCopyEnabledKey;

    PimThaiWindow(QWidget *parent = 0);
    ~PimThaiWindow();

    void resizeEvent(QResizeEvent *);

private:
    enum {
        MAX_BUFFER = 4
    };

    MenuBar *menuBar;
    Toaster *toaster;
    QSettings settingsDb;
    JKeyboard *keyboard;
    int activeBuffer;
    QString buffers[MAX_BUFFER];
    QToolButton *bufferButtons[MAX_BUFFER];
    bool predictionEnabled;
    bool autoCopyEnabled;

    void changeEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void saveSettings();
    void updateBuffer(QToolButton *button);

private slots:
    void aboutClicked();
    void autoCopyClicked(bool enabled);
    void clearBuffer();
    void copyToClipboard();
    void bufferButtonClicked();
    void predictToggleClicked(bool enabled);
};

#endif
