#ifndef PSWINDOW_H
#define PSWINDOW_H

#include <QMainWindow>

namespace Ui {
class PSWindow;
}

class PSWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PSWindow(QWidget *parent = 0);
    ~PSWindow();
    
private:
    Ui::PSWindow *ui;
};

#endif // PSWINDOW_H
