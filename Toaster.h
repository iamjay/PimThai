#ifndef TOASTER_H
#define TOASTER_H

#include <QTimer>
#include <QWidget>

class QLabel;

class Toaster : public QWidget
{
    Q_OBJECT
public:
    Toaster(QWidget *parent = 0);
    void showToast(QPoint &p, const QString &text);

protected:
    QLabel *label;

private slots:
    void toastTimeout();
};

#endif
