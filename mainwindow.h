#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputMethodEvent>
#include <QCompleter>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QStringListModel>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QValidator>
#include <QMessageBox>
#include <QPlainTextEdit>
#include "QProgressIndicator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QVector<QString> m_cityStr;
    QVector<QVector<QString>> m_areaStr;

    QCompleter* m_pCpCityEdit;
    QCompleter* m_pCpAreaEdit;
    QCompleter* m_pCpEmail;

    QStringList m_mailList;

    QRegExpValidator* m_mailValid;
    QRegExpValidator* m_cellPhoneValid;
    QRegExpValidator* m_homePhoneValid;

    QUrl m_url;
    QNetworkAccessManager m_qnam;
    QNetworkReply *m_reply;
    //QFile logFile;
    QString log_str;
    QProgressIndicator* m_pi;
    int m_nSubmit;

    void setAreaListFromCityIdx(int cityIdx);
    void loadCityAndArea();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void on_listWidget_City_itemClicked();
    void on_listWidget_Area_itemClicked();

    void on_lineEdit_City_textChanged(const QString &);
    void on_lineEdit_Area_textChanged(const QString &);
    void on_lineEdit_CellPhone_textChanged(const QString &text);
    void on_lineEdit_HomePhone_textChanged(const QString &text);
    void on_lineEdit_Email_textChanged(const QString &text);

    void on_lineEdit_City_returnPressed();
    void on_lineEdit_Area_returnPressed();
    void on_lineEdit_Name_returnPressed();
    void on_lineEdit_CellPhone_returnPressed();
    void on_lineEdit_HomePhone_returnPressed();

    void on_lineEdit_Email_returnPressed();


    void on_pushButton_Submit_clicked();
    void on_pushButton_Reset_clicked();

    void on_radioButton_toggled(bool checked);

    void httpFinished();
    void httpReadyRead();

    void clearAllExceptCityArea();
    void about();
    void readMe();

    void setLabelNumText(int num);
};

#endif // MAINWINDOW_H
