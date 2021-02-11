#include <QString>
#include <QMessageBox>

void showErrorMessageBox(const QString &message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString("Предупреждение"));
    msgBox.setText(message);
    msgBox.exec();
}
