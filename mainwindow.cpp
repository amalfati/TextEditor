                    #include "mainwindow.h"
                    #include "ui_mainwindow.h"
                    #include<QFile>
                    #include<QMessageBox>
                    #include<QFileDialog>
                    #include<QTextStream>
                    #include<QFontDialog>
                    
                    
                    MainWindow::MainWindow(QWidget *parent)
                        : QMainWindow(parent)
                        , ui(new Ui::MainWindow)
                    {
                        ui->setupUi(this);
                        setCentralWidget(ui->textEdit);
                    
                    
                            connect(ui->actionNewfile, &QAction::triggered, this, &MainWindow::newDocument);
                            connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
                            connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
                            connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveAs);
                            connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);
                            connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::copy);
                            connect(ui->actionCut, &QAction::triggered, this, &MainWindow::cut);
                            connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::paste);
                            connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undo);
                            connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redo);
                            connect(ui->actionSelectfont, &QAction::triggered, this, &MainWindow::selectFont);
                            connect(ui->actionabout, &QAction::triggered, this, &MainWindow::about);
                            connect(ui->actionclear, &QAction::triggered, this, &MainWindow::clear);
                    
                    }
                    void MainWindow::newDocument()
                    {
                        currentFile.clear();
                        ui->textEdit->setText(QString());
                    }
                    void MainWindow::open()
                    {
                        QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
                        QFile file(fileName);
                        currentFile = fileName;
                        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
                            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
                            return;
                        }
                        setWindowTitle(fileName);
                        QTextStream in(&file);
                        QString text = in.readAll();
                        ui->textEdit->setText(text);
                        file.close();
                    }
                    void MainWindow::save()
                    {
                        QString fileName;
                        // If we don't have a filename from before, get one.
                        if (currentFile.isEmpty()) {
                            fileName = QFileDialog::getSaveFileName(this, "Save");
                            currentFile = fileName;
                        } else {
                            fileName = currentFile;
                        }
                        QFile file(fileName);
                        if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
                            QMessageBox::warning(this, "Attention", "this file Cannot be save : " + file.errorString());
                            return;
                        }
                        setWindowTitle(fileName);
                        QTextStream out(&file);
                        QString text = ui->textEdit->toPlainText();
                        out << text;
                        file.close();
                    }
                    void MainWindow::saveAs()
                    {
                        QString fileName = QFileDialog::getSaveFileName(this, "Save as");
                        QFile file(fileName);
                    
                        if (!file.open(QFile::WriteOnly | QFile::Text)) {
                            QMessageBox::warning(this, "Attention", "this file Cannot be save : " + file.errorString());
                            return;
                        }
                        currentFile = fileName;
                        setWindowTitle(fileName);
                        QTextStream out(&file);
                        QString text = ui->textEdit->toPlainText();
                        out << text;
                        file.close();
                    }
                    
                    void MainWindow::exit()
                    {
                        QCoreApplication::quit();
                    }
                    void MainWindow::copy()
                    {
                    
                        ui->textEdit->copy();
                    
                    }
                    
                    void MainWindow::cut()
                    {
                    
                        ui->textEdit->cut();
                    
                    }
                    void MainWindow::paste()
                    {
                    
                        ui->textEdit->paste();
                    
                    }
                    
                    void MainWindow::undo()
                    {
                         ui->textEdit->undo();
                    }
                    
                    void MainWindow::redo()
                    {
                        ui->textEdit->redo();
                    }
                    void MainWindow::selectFont()
                    {
                        bool fontSelected;
                        QFont font = QFontDialog::getFont(&fontSelected, this);
                        if (fontSelected)
                            ui->textEdit->setFont(font);
                    }
                    
                    
                    
                    void MainWindow:: about()
                    {
                       QMessageBox::about(this, tr("About TextEditor"),
                                    tr("The <b>TextEditor</b> The application is a small text editor which allows you to create a text file,"
                                       " save it, print it and other things ….."
                                       ));
                    
                    }
                    
                    void MainWindow::clear(){
                    
                            ui->textEdit->clear();
                    }
                    
                    MainWindow::~MainWindow()
                    {
                        delete ui;
                    }
                    
