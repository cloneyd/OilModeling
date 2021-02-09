#include <QString>
#include <QMessageBox>

void showErrorMessageBox(const QString &message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}
