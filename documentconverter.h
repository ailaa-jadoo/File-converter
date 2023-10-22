#ifndef DOCUMENTCONVERTER_H
#define DOCUMENTCONVERTER_H


#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QVBoxLayout>


class DocumentConverter : public QWidget {
    Q_OBJECT

public:
    DocumentConverter();

private slots:
    void startConversion();
    void performTextToPdfConversion();
    void performTextToWordConversion();
    void performWordToTextConversion();
    void performWordToPdfConversion();
    void performPdfToTextConversion();
//    void performPdfToWordConversion();

private:
    QComboBox inputComboBox;
    QComboBox outputComboBox;
    QLabel statusLabel;
    QPushButton convertButton;
    QVBoxLayout layout;

    QString inputFilePath;
    QString outputFilePath;

};

#endif // DOCUMENTCONVERTER_H
