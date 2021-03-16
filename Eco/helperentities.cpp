#include <QMessageBox>
#include <QString>

void showErrorMessageBox(const QString &msg, const QString &title = "")
{
    QMessageBox msg_box;
    msg_box.setAutoFillBackground(true);
    msg_box.setWindowTitle(title);
    msg_box.setText(msg);
    msg_box.exec();
}
