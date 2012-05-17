#ifndef PIMTHAIWINDOW_H
#define PIMTHAIWINDOW_H

#include <QMainWindow>

#include "ui_PimThaiWindow.h"

#include "JKeyboard.h"

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

    PimThaiWindow(QWidget *parent = 0);
    ~PimThaiWindow();

protected:
    enum {
        MAX_BUFFER = 4
    };

    QSettings settingsDb;
    JKeyboard *keyboard;
    int activeBuffer;
    QString buffers[MAX_BUFFER];
    QPushButton *bufferButtons[MAX_BUFFER];
    bool predictionEnabled;

    void updateBuffer(QPushButton *button);

private slots:
    void clearBuffer();
    void copyToClipboard();
    void bufferButtonClicked();
    void predictToggleClicked(bool enabled);
};

#endif
