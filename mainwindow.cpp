#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(notifyObservers()), this, SLOT(update()));

    ui->book_error->setStyleSheet("QLabel { color : red; }");
    ui->reader_error->setStyleSheet("QLabel { color : red; }");
    ui->transaction_error->setStyleSheet("QLabel { color : red; }");
    ui->status->setStyleSheet("QLabel { color : red; }");

    Book book1 = BookBuilder().setBookId(102).setAuthor("Шилдт Г.").setTitle("Самоучитель C++").setYear("2015").setIsAvailable(false).build();
    Book book2 = BookBuilder().setBookId(28).setAuthor("Пушкин А.").setTitle("Медный всадник").setYear("1824").setIsAvailable(true).build();
    Book book3 = BookBuilder().setBookId(14).setAuthor("Пушкин А.").setTitle("Евгений Онегин").setYear("1823").setIsAvailable(true).build();
    Reader reader1 = ReaderBuilder().setReaderId(273849).setName("Иванов Сергей Александрович").setAddress("ул. Тверская, д. 16, кв. 45").setPhone("+7 (495) 123-45-67").build();
    Reader reader2 = ReaderBuilder().setReaderId(2).setName("Кузнецов Владислав Х.").setAddress("ул. Колотушкина, дом Пушкина").setPhone("+7 (921) 565-09-23").build();
    Transaction transaction1 = TransactionBuilder().setReaderId(reader1.get_readerId()).setBookId(book1.get_bookId()).setIssueDate("29.05.2024").setReturnDate("").build();
    books.push_back(book1);
    books.push_back(book2);
    books.push_back(book3);
    readers.push_back(reader1);
    readers.push_back(reader2);
    transactions.push_back(transaction1);

    QRegularExpression FCs("[а-яА-ЯёЁ]+ [а-яА-ЯёЁ]+ [а-яА-ЯёЁ]+");
    QRegularExpression valtext("[а-яА-ЯёЁ\\- ]+");
    QRegularExpression valid("\\d+");
    QRegularExpression valyear("\\d{4}");
    QRegularExpression phonePattern("\\+?\\d \\(\\d{3}\\) \\d{3}-\\d{2}-\\d{2}");
    QRegularExpression valdate("\\d{2}-\\d{2}-\\d{4}");

    QValidator *FCs_validator = new QRegularExpressionValidator(FCs, this);
    QValidator *id_validator = new QRegularExpressionValidator(valid, this);
    QValidator *phone_validator = new QRegularExpressionValidator(phonePattern, this);
    QValidator *year_validator = new QRegularExpressionValidator(valyear,this);
    QValidator *dte_validator = new QRegularExpressionValidator(valdate, this);
    QValidator *text_validator = new QRegularExpressionValidator(valtext,this);

    ui->book_id->setValidator(id_validator);
    ui->book_title->setValidator(text_validator);
    ui->book_year->setValidator(year_validator);
    ui->author_name->setValidator(FCs_validator);

    ui->reader_id->setValidator(id_validator);
    ui->reader_name->setValidator(FCs_validator);
    ui->phone_number->setValidator(phone_validator);

    ui->book_id_2->setValidator(id_validator);
    ui->reader_id_2->setValidator(id_validator);
    ui->issue_date->setValidator(dte_validator);

    ui->deleteBookId->setValidator(id_validator);
    ui->deleteReaderId->setValidator(id_validator);

    connect(ui->showReaders, SIGNAL(clicked()), this, SLOT(displayTransactions()));
    connect(ui->showBooks, SIGNAL(clicked()), this, SLOT(displayBooks()));
    connect(ui->showReaders, SIGNAL(clicked()), this, SLOT(displayReaders()));
    connect(ui->butt_addBook, SIGNAL(clicked()), this, SLOT(addBook()));
    connect(ui->butt_addReader, SIGNAL(clicked()), this, SLOT(addReader()));
    connect(ui->butt_addTransaction, SIGNAL(clicked()), this, SLOT(addTransaction()));
    connect(ui->deleteBook, SIGNAL(clicked()), this, SLOT(deleteBook()));
    connect(ui->deleteReader, SIGNAL(clicked()), this, SLOT(deleteReader()));
    connect(ui->findBook, SIGNAL(clicked()), this, SLOT(findBook()));
    connect(ui->findReader, SIGNAL(clicked()), this, SLOT(findReader()));
    connect(ui->returnBook, SIGNAL(clicked()), this, SLOT(returnBook()));
    connect(ui->findReaderBook, SIGNAL(clicked()), this, SLOT(findReaderBook()));


    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->tableBooks->setItemDelegate(readOnlyDelegate);
    ui->tableReaders->setItemDelegate(readOnlyDelegate);
    ui->tableTransactions->setItemDelegate(readOnlyDelegate);

    displayBooks();
    displayReaders();
    displayTransactions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayBooks()
{

    ui->tableBooks->setRowCount(books.size());
    ui->tableBooks->setColumnCount(5);
    ui->tableBooks->setHorizontalHeaderLabels(QStringList() << "Id книги" << "ФИО автора" << "Название книги" << "Год издания" << "Наличие");
    ui->tableBooks->clearContents();

    int rowCount = 0;

    for(int i = 0; i < books.size(); i++)
    {
        if(books[i].get_isAvailable())
        {
            ui->tableBooks->setItem(rowCount, 0, new QTableWidgetItem(QString::number(books[i].get_bookId())));
            ui->tableBooks->setItem(rowCount, 1, new QTableWidgetItem(books[i].get_author()));
            ui->tableBooks->setItem(rowCount, 2, new QTableWidgetItem(books[i].get_title()));
            ui->tableBooks->setItem(rowCount, 3, new QTableWidgetItem(books[i].get_year()));
            ui->tableBooks->setItem(rowCount, 4, new QTableWidgetItem(books[i].get_Available()));
            rowCount++;
        }
    }
    ui->tableBooks->setRowCount(rowCount);
}


void MainWindow::displayReaders()
{
    ui->tableReaders->setRowCount(readers.size());
    ui->tableReaders->setColumnCount(4);
    ui->tableReaders->setHorizontalHeaderLabels(QStringList() << "Id чит. бил." << "ФИО читателя" << "Адрес" << "Телефон");
    ui->tableReaders->clearContents();

    for(int i=0;i<readers.size();i++){
        ui->tableReaders->setItem(i,0, new QTableWidgetItem(QString::number(readers[i].get_readerId())));
        ui->tableReaders->setItem(i,1, new QTableWidgetItem(readers[i].get_name()));
        ui->tableReaders->setItem(i,2, new QTableWidgetItem(readers[i].get_address()));
        ui->tableReaders->setItem(i,3, new QTableWidgetItem(readers[i].get_phone()));
    }
}

void MainWindow::displayTransactions()
{
    ui->tableTransactions->setRowCount(transactions.size());
    ui->tableTransactions->setColumnCount(4);
    ui->tableTransactions->setHorizontalHeaderLabels(QStringList() << "Id чит. бил." << "Id книги" << "Дата выдачи" << "Дата возрата");
    ui->tableTransactions->clearContents();

    for(int i=0;i<transactions.size();i++){
        ui->tableTransactions->setItem(i,0, new QTableWidgetItem(QString::number(transactions[i].get_readerId())));
        ui->tableTransactions->setItem(i,1, new QTableWidgetItem(QString::number(transactions[i].get_bookId())));
        ui->tableTransactions->setItem(i,2, new QTableWidgetItem(transactions[i].get_issueDate()));
        ui->tableTransactions->setItem(i,3, new QTableWidgetItem(transactions[i].get_returnDate()));
    }
}

void MainWindow::addBook()
{
    if(ui->book_id->text() == "")
    {
        ui->book_error->setText("Введите id книги");
        return;
    }
    if(ui->book_title->text() == "" || ui->book_title->text()[0].isLower())
    {
        ui->book_error->setText("Введите название книги");
        return;
    }
    if(ui->book_year->text() == "" || ui->book_year->text().toInt() > 2024 || ui->book_year->text().toInt() < 105)
    {
        ui->book_error->setText("Введите год");
        return;
    }
    if(ui->author_name->text() == "" || ui->author_name->text()[0].isLower())
    {
        ui->book_error->setText("Введите имя автора");
        return;
    }
    int bookId = ui->book_id->text().toInt();
    for(int i = 0; i < books.size(); i++)
    {
        if(books[i].get_bookId() == bookId)
        {
            ui->book_error->setText("Уже существует книга с таким id");
            return;
        }
    }
    ui->book_error->clear();
    Book book = BookBuilder().setBookId(ui->book_id->text().toInt()).setAuthor(ui->author_name->text()).setTitle(ui->book_title->text()).setYear(ui->book_year->text()).setIsAvailable(true).build();;
    books.push_back(book);
    ui->book_id->clear();
    ui->book_title->clear();
    ui->book_year->clear();
    ui->author_name->clear();
    emit notifyObservers();
}

void MainWindow::addReader()
{
    if(ui->reader_id->text() == "")
    {
        ui->reader_error->setText("Введите id читателя");
        return;
    }
    if(ui->reader_name->text() == "" || ui->reader_name->text()[0].isLower())
    {
        ui->reader_error->setText("Введите имя читателя");
        return;
    }
    if(ui->reader_address->text() == "" || ui->reader_address->text().length() < 3)
    {
        ui->reader_error->setText("Введите адресс");
        return;
    }
    if(ui->phone_number->text() == "" || ui->phone_number->text().length() < 17)
    {
        ui->reader_error->setText("Введите номер телефона X/+X (XXX) XXX-XX-XX");
        return;
    }
    int readerId = ui->reader_id->text().toInt();
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].get_readerId() == readerId)
        {
            ui->reader_error->setText("Уже существует читатель с таким id");
            return;
        }
    }
    ui->reader_error->clear();
    Reader reader = ReaderBuilder().setReaderId(ui->reader_id->text().toInt()).setName(ui->reader_name->text()).setAddress(ui->reader_address->text()).setPhone(ui->phone_number->text()).build();;
    readers.push_back(reader);
    ui->reader_id->clear();
    ui->reader_name->clear();
    ui->reader_address->clear();
    ui->phone_number->clear();
    emit notifyObservers();
}

void MainWindow::addTransaction()
{
    if(ui->reader_id_2->text() == "")
    {
        ui->transaction_error->setText("Введите id читателя");
        return;
    }
    if(ui->book_id_2->text() == "")
    {
        ui->transaction_error->setText("Введите id книги");
        return;
    }
    if(ui->issue_date->text() == "" || ui->issue_date->text().length() < 9)
    {
        ui->transaction_error->setText("Введите дату выдачи книги");
        return;
    }

    int readerId = ui->reader_id_2->text().toInt();
    int amount_of_books = 0;
    int bookId = ui->book_id_2->text().toInt();
    bool check = false;
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].get_readerId() == readerId)
        {
            check = true;
        }
    }
    if(!check)
    {
        ui->transaction_error->setText("Нет такого читателя");
        return;
    }
    check = false;
    for(int i = 0; i <transactions.size(); i++)
    {
        if(transactions[i].get_readerId() == readerId || transactions[i].get_returnDate() == "")
        {
            amount_of_books +=1;
        }
    }
    if(amount_of_books == 3)
    {
        ui->transaction_error->setText("Куда тебе столько?");
        return;
    }
    for(int i = 0; i < books.size(); i++)
    {
        if(books[i].get_bookId() == bookId)
        {
            if (books[i].get_isAvailable())
            {
                check = true;
                books[i].set_isAvailable(false);
                ui->transaction_error->setText("Книга выдана");
            }
            else
            {
                ui->transaction_error->setText("Книга уже выдана");
                return;
            }
            break;
        }
    }
    if(!check)
    {
        ui->transaction_error->setText("Нет такой книги");
        return;
    }
    // for(int i = 0; i < transactions.size(); i++)
    // {
    //     if(transactions[i].get_bookId() == bookId)
    //     {
    //         ui->transaction_error->setText("Уже выдана");
    //         return;
    //     }
    // }
    ui->transaction_error->clear();
    Transaction transaction = TransactionBuilder().setReaderId(ui->reader_id_2->text().toInt()).setBookId(ui->book_id_2->text().toInt()).setIssueDate(ui->issue_date->text()).setReturnDate("").build();;
    transactions.push_back(transaction);
    ui->reader_id_2->clear();
    ui->book_id_2->clear();
    ui->issue_date->clear();
    emit notifyObservers();
}

void MainWindow::deleteBook()
{
    if(ui->deleteBookId->text() == "")
    {
        ui->status->setText("Введите id книги для удаления");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }
    int bookId = ui->deleteBookId->text().toInt();
    for(int i = 0 ; i < books.size(); i++)
    {
        if(books[i].get_bookId() == bookId)
        {
            books.removeAt(i);
            ui->status->setText("Удалено успешно: книга");
            ui->status->setStyleSheet("QLabel { color : green; }");
        }
    }
    for(int i = 0; i < transactions.size(); i++)
    {
        if(transactions[i].get_bookId() == bookId)
        {
            transactions.removeAt(i);
            ui->status->setText(ui->status->text() + " + транзакция");
        }
    }
    ui->deleteBookId->clear();
    emit notifyObservers();
}

void MainWindow::deleteReader()
{
    if(ui->deleteReaderId->text().isEmpty())
    {
        ui->status->setText("Вы не ввели ID читателя");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }

    int readerId = ui->deleteReaderId->text().toInt();
    bool readerFound = false;
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].get_readerId() == readerId)
        {
            readerFound = true;
            readers.removeAt(i);
            ui->status->setText("Читатель удалён успешно");
            ui->status->setStyleSheet("QLabel { color : green; }");

            for(int j = 0; j < transactions.size();)
            {
                if(transactions[j].get_readerId() == readerId)
                {
                    for(int k = 0; k < books.size(); k++)
                    {
                        if(books[k].get_bookId() == transactions[j].get_bookId())
                        {
                            books[k].set_isAvailable(true);
                            break;
                        }
                    }
                    transactions.removeAt(j);
                    ui->status->setText(ui->status->text() + " и транзакции");
                }
                else
                {
                    ++j;
                }
            }
            break;
        }
    }

    if(!readerFound)
    {
        ui->status->setText("Читатель не найден");
        ui->status->setStyleSheet("QLabel { color : red; }");
    }
    ui->deleteReaderId->clear();
    emit notifyObservers();
}

void MainWindow::findBook()
{
    if(ui->deleteBookId->text().isEmpty())
    {
        ui->status->setText("Введите ID книги для поиска");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }

    int bookId = ui->deleteBookId->text().toInt();
    bool bookFound = false;

    ui->tableBooks->clearContents();

    for(int i = 0; i < books.size(); ++i)
    {
        if(books[i].get_bookId() == bookId)
        {
            ui->tableBooks->setRowCount(1);
            ui->tableBooks->setColumnCount(5);
            ui->tableBooks->setHorizontalHeaderLabels(QStringList() << "Id книги" << "ФИО автора" << "Название книги" << "Год издания" << "Наличие");

            ui->tableBooks->setItem(0, 0, new QTableWidgetItem(QString::number(books[i].get_bookId())));
            ui->tableBooks->setItem(0, 1, new QTableWidgetItem(books[i].get_author()));
            ui->tableBooks->setItem(0, 2, new QTableWidgetItem(books[i].get_title()));
            ui->tableBooks->setItem(0, 3, new QTableWidgetItem(books[i].get_year()));
            ui->tableBooks->setItem(0, 4, new QTableWidgetItem(books[i].get_Available()));

            bookFound = true;
            break;
        }
    }

    if(!bookFound)
    {
        ui->status->setText("Книга с указанным ID не найдена");
        ui->status->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        ui->status->clear();
    }
    ui->deleteBookId->clear();

}

void MainWindow::findReader()
{
    if(ui->deleteReaderId->text().isEmpty())
    {
        ui->status->setText("Введите ID читателя для поиска");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }
    int readerId = ui->deleteReaderId->text().toInt();
    bool readerFound = false;

    ui->tableReaders->clearContents();

    for(int i = 0; i < readers.size(); ++i)
    {
        if(readers[i].get_readerId() == readerId)
        {
            ui->tableReaders->setRowCount(1);
            ui->tableReaders->setColumnCount(4);
            ui->tableReaders->setHorizontalHeaderLabels(QStringList() << "Id чит. бил." << "ФИО читателя" << "Адрес" << "Телефон");

            ui->tableReaders->setItem(0, 0, new QTableWidgetItem(QString::number(readers[i].get_readerId())));
            ui->tableReaders->setItem(0, 1, new QTableWidgetItem(readers[i].get_name()));
            ui->tableReaders->setItem(0, 2, new QTableWidgetItem(readers[i].get_address()));
            ui->tableReaders->setItem(0, 3, new QTableWidgetItem(readers[i].get_phone()));

            readerFound = true;
            break;
        }
    }

    if(!readerFound)
    {
        ui->status->setText("Читатель с указанным ID не найден");
        ui->status->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        ui->status->clear();
    }
    ui->deleteReaderId->clear();

}

void MainWindow::returnBook()
{
    if(ui->deleteBookId->text().isEmpty() || ui->deleteReaderId->text().isEmpty() || ui->returnDate->text().isEmpty())
    {
        ui->status->setText("Заполните все поля");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }

    int bookId = ui->deleteBookId->text().toInt();
    int readerId = ui->deleteReaderId->text().toInt();
    QString returnDate = ui->returnDate->text();

    bool transactionFound = false;
    bool correctReader = false;

    for(int i = 0; i < transactions.size(); ++i)
    {
        if(transactions[i].get_bookId() == bookId)
        {
            if(transactions[i].get_readerId() == readerId)
            {
                correctReader = true;
                transactions[i].set_returnDate(returnDate);
                for(int i = 0; i < books.size(); i++)
                {
                    if(books[i].get_bookId() == bookId)
                    {
                        books[i].set_isAvailable(true);
                    }
                }
                transactionFound = true;
                break;
            }
        }
    }

    ui->deleteBookId->clear();
    ui->deleteReaderId->clear();
    ui->returnDate->clear();

    if(!correctReader)
    {
        ui->status->setText("Эта книга не находится у указанного читателя");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }

    if(!transactionFound)
    {
        ui->status->setText("Транзакция для указанной книги и читателя не найдена");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }

    ui->status->clear();
    emit notifyObservers();
}

void MainWindow::findReaderBook()
{
    if (ui->deleteReaderId->text().isEmpty())
    {
        ui->status->setText("Введите ID читателя");
        ui->status->setStyleSheet("QLabel { color : red; }");
        return;
    }

    int readerId = ui->deleteReaderId->text().toInt();
    qDebug() << "Reader ID: " << readerId;

    bool readerFound = false;

    ui->tableTransactions->clearContents(); // Очистка таблицы
    ui->tableTransactions->setRowCount(0);

    qDebug() << "Transactions size: " << transactions.size();

    for (int i = 0; i < transactions.size(); ++i)
    {
        if (transactions[i].get_readerId() == readerId)
        {
            if (!readerFound)
            {
                ui->tableTransactions->setRowCount(0);
                ui->tableTransactions->setColumnCount(4);
                ui->tableTransactions->setHorizontalHeaderLabels(QStringList() << "Id чит. бил." << "Id книги" << "Дата выдачи" << "Дата возрата");
                readerFound = true;
            }
            int rowCount = ui->tableTransactions->rowCount();
            qDebug() << "Inserting row at position: " << rowCount;

            ui->tableTransactions->insertRow(rowCount);
            ui->tableTransactions->setItem(rowCount, 0, new QTableWidgetItem(QString::number(transactions[i].get_readerId())));
            ui->tableTransactions->setItem(rowCount, 1, new QTableWidgetItem(QString::number(transactions[i].get_bookId())));
            ui->tableTransactions->setItem(rowCount, 2, new QTableWidgetItem(transactions[i].get_issueDate()));
            ui->tableTransactions->setItem(rowCount, 3, new QTableWidgetItem(transactions[i].get_returnDate()));
        }
    }

    if (!readerFound)
    {
        ui->status->setText("Читатель с указанным ID не найден");
        ui->status->setStyleSheet("QLabel { color : red; }");
        qDebug() << "Reader not found.";
    }
    else
    {
        ui->status->clear();
        qDebug() << "Reader found.";
    }

    ui->deleteReaderId->clear();
    ui->deleteBookId->clear();
}


void MainWindow::update() {
    displayBooks();
    displayReaders();
    displayTransactions();
}
