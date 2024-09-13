#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "readonlydelegate.h"
#include "Book.h"
#include "Reader.h"
#include "Transaction.h"
#include "bookbuilder.h"
#include "readerbuilder.h"
#include "transactionbuilder.h"
#include <QDate>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<Book>books;
    QList<Reader>readers;
    QList<Transaction>transactions;
public slots:
    void update();
private slots:
    void displayBooks();
    void displayReaders();
    void displayTransactions();
    void addBook();
    void addReader();
    void addTransaction();
    void deleteBook();
    void deleteReader();
    void findBook();
    void findReader();
    void returnBook();
    void findReaderBook();
signals:
    void notifyObservers();
};
#endif // MAINWINDOW_H
