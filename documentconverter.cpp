#include "documentconverter.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QProcess>
#include <QPrinter>
#include <QTextCursor>

DocumentConverter::DocumentConverter() {
    setWindowTitle("Document Converter");

    inputComboBox.addItem("Select Input Format");
    inputComboBox.addItem("Word");
    inputComboBox.addItem("PDF");
    inputComboBox.addItem("Text");

    outputComboBox.addItem("Select Output Format");
    outputComboBox.addItem("Word");
    outputComboBox.addItem("PDF");
    outputComboBox.addItem("Text");

    statusLabel.setText("<b>Conversion status will be displayed here</b>");
    convertButton.setText("Convert");

    layout.addWidget(&inputComboBox);
    layout.addWidget(&outputComboBox);
    layout.addWidget(&statusLabel);
    layout.addWidget(&convertButton);

    setLayout(&layout);

    connect(&convertButton, &QPushButton::clicked, this, &DocumentConverter::startConversion);
}

void DocumentConverter::startConversion() {
    QString inputFormat = inputComboBox.currentText();
    QString outputFormat = outputComboBox.currentText();

    if (inputFormat == "Select Input Format" || outputFormat == "Select Output Format") {
        statusLabel.setText("<font color='red'><b>Please select valid input and output formats.</b></font>");
        return;
    }

    if (inputFormat == "Text" && outputFormat == "PDF") {
        performTextToPdfConversion();
    } else if (inputFormat == "Text" && outputFormat == "Word") {
        performTextToWordConversion();
    } else if (inputFormat == "Word" && outputFormat == "Text") {
        performWordToTextConversion();
    } else if (inputFormat == "Word" && outputFormat == "PDF") {
        performWordToPdfConversion();
    } else if (inputFormat == "PDF" && outputFormat == "Text") {
        performPdfToTextConversion();
    } else if (inputFormat == "PDF" && outputFormat == "Word") {
        statusLabel.setText("<font color='orange'><b>This functionality is yet to be launched.</b></font>");
    } else if(inputFormat == outputFormat){
        statusLabel.setText("<font color='red'><b>You are converting file to the same format.</b></font>");
    } else {
        statusLabel.setText("<font color='red'><b>Conversion not supported for the selected formats.</b></font>");
    }
}

void DocumentConverter::performTextToPdfConversion() {
    QString inputFilePath = QFileDialog::getOpenFileName(this, "Select Input Text File", "", "Text Files (*.txt)");
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save As", "", "PDF Files (*.pdf)");

    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        statusLabel.setText("Conversion canceled or invalid file paths.");
        return;
    }

    // Define the command for LibreOffice conversion (Text to PDF)
    QString conversionCommand = "C:\\Program Files\\LibreOffice\\program\\soffice.exe"; // Path to soffice.exe
    QStringList conversionArguments;
    conversionArguments << "--headless" << "--convert-to" << "pdf" << inputFilePath << "--outdir" << outputFilePath;

    QProcess conversionProcess;
    conversionProcess.start(conversionCommand, conversionArguments);

    if (conversionProcess.waitForFinished() && conversionProcess.exitCode() == 0) {
        statusLabel.setText("<font color='green'><b>Conversion from Text to PDF completed successfully.</b></font>");
    } else {
        statusLabel.setText("Error: Conversion from Text to PDF failed.");
    }
}

void DocumentConverter::performTextToWordConversion() {
    QString inputFilePath = QFileDialog::getOpenFileName(this, "Select Input Text File", "", "Text Files (*.txt)");
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save As", "", "Word Files (*.docx)");

    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        statusLabel.setText("Conversion canceled or invalid file paths.");
        return;
    }

    QTextDocument doc;
    QTextCursor cursor(&doc);

    // Read the text from the input file and set it in the QTextDocument
    QFile inputFile(inputFilePath);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&inputFile);
        cursor.insertText(in.readAll());
        inputFile.close();
    } else {
        statusLabel.setText("Error: Unable to open input file.");
        return;
    }

    // Define the command for LibreOffice conversion (Text to Word)
    QString conversionCommand = "C:\\Program Files\\LibreOffice\\program\\soffice.exe"; // Path to soffice.exe
    QStringList conversionArguments;
    conversionArguments << "--headless" << "--convert-to" << "docx" << inputFilePath << "--outdir" << outputFilePath;

    QProcess conversionProcess;
    conversionProcess.start(conversionCommand, conversionArguments);

    if (conversionProcess.waitForFinished() && conversionProcess.exitCode() == 0) {
        statusLabel.setText("<font color='green'><b>Conversion from Text to Word completed successfully.</b></font>");
    } else {
        statusLabel.setText("Error: Conversion from Text to Word failed.");
    }
}

void DocumentConverter::performWordToTextConversion() {
    QString inputFilePath = QFileDialog::getOpenFileName(this, "Select Input Word File", "", "Word Files (*.docx)");
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save As", "", "Text Files (*.txt)");

    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        statusLabel.setText("Conversion canceled or invalid file paths.");
        return;
    }

    // Define the command for LibreOffice conversion (Word to Text)
    QString conversionCommand = "C:\\Program Files\\LibreOffice\\program\\soffice.exe"; // Path to soffice.exe
    QStringList conversionArguments;
    conversionArguments << "--headless" << "--convert-to" << "txt:Text (encoded):UTF8" << inputFilePath << "--outdir" << outputFilePath;

    QProcess conversionProcess;
    conversionProcess.start(conversionCommand, conversionArguments);

    if (conversionProcess.waitForFinished() && conversionProcess.exitCode() == 0) {
        statusLabel.setText("<font color='green'><b>Conversion from Word to Text completed successfully.</b></font>");
    } else {
        statusLabel.setText("Error: Conversion from Word to Text failed.");
    }
}

void DocumentConverter::performWordToPdfConversion() {
    QString inputFilePath = QFileDialog::getOpenFileName(this, "Select Input Word File", "", "Word Files (*.docx)");
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save As", "", "PDF Files (*.pdf)");

    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        statusLabel.setText("Conversion canceled or invalid file paths.");
        return;
    }

    // Define the command for LibreOffice conversion
    QString conversionCommand = "C:\\Program Files\\LibreOffice\\program\\soffice.exe"; // Path to soffice.exe
    QStringList conversionArguments;
    conversionArguments << "--headless" << "--convert-to" << "pdf" << inputFilePath << "--outdir" << outputFilePath;

    QProcess conversionProcess;
    conversionProcess.start(conversionCommand, conversionArguments);

    if (conversionProcess.waitForFinished() && conversionProcess.exitCode() == 0) {
        statusLabel.setText("<font color='green'><b>Conversion from Word to PDF completed successfully.</b></font>");
    } else {
        statusLabel.setText("Error: Conversion to PDF failed.");
    }
}

void DocumentConverter::performPdfToTextConversion() {
    QString inputFilePath = QFileDialog::getOpenFileName(this, "Select Input PDF File", "", "PDF Files (*.pdf)");
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save As", "", "Text Files (*.txt)");

    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        statusLabel.setText("Conversion canceled or invalid file paths.");
        return;
    }

    // Path to pdftotext.exe
    QString conversionCommand = "H:\\xpdf-tools-win-4.04\\bin64\\pdftotext.exe";

    // Specify the input PDF file and output text file
    QStringList conversionArguments;
    conversionArguments << inputFilePath << outputFilePath;

    QProcess conversionProcess;
    conversionProcess.start(conversionCommand, conversionArguments);

    if (conversionProcess.waitForFinished() && conversionProcess.exitCode() == 0) {
        statusLabel.setText("<font color='green'><b>Conversion from PDF to Text completed successfully.</b></font>");
    } else {
        statusLabel.setText("Error: Conversion from PDF to Text failed.");
    }
}



