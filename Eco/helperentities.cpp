#include <QMessageBox>
#include <QString>

void showErrorMessageBox(const QString &msg)
{
    QMessageBox msg_box;
    msg_box.setText(msg);
    msg_box.exec();
}
