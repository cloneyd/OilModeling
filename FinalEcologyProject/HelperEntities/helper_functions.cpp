#include <QString>
#include <QMessageBox>

void showErrorMessageBox(const QString &message) // cannot use QStringView because QMessageBox::setText takes const QString
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString("Предупреждение"));
    msgBox.setText(message);
    msgBox.exec();
}
