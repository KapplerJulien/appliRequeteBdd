#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include "dialogabout.h"

/**
 * @brief Constructeur de la classe MainWindow
 * @param QWidget* parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // qDebug() << "test1";
    ui->setupUi(this);
    ui->comboBoxBdd->addItem("Choisir");
    QSqlQuery database("show databases;");
    while(database.next()){
        QString nomBdd = database.value(0).toString();
        ui->comboBoxBdd->addItem(nomBdd);
    }
    ui->labelLogo->setPixmap(QPixmap("/home/jkappler/Slam4/appliRequeteBdd/logo.png"));
}

/**
 * @brief Destructeur de la classe MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief A chaque modification de la base de données
 * @param nomBase
 */
void MainWindow::on_comboBoxBdd_activated(const QString &nomBase)
{
    ui->listWidgetTables->clear();
    extern QSqlDatabase connection;
    if(nomBase == "Choisir"){

    } else {

        connection.setDatabaseName(nomBase);
        connection.open();
        QSqlQuery rechercheTables("show tables;");
        while(rechercheTables.next()){
            QString table = rechercheTables.value(0).toString();
            ui->listWidgetTables->addItem(table);
        }
        ui->textEditRequete->setEnabled(true);
    }
}

/**
 * @brief Choisir une table et affichage des champs
 * Lorsque l'on clique, la table que l'on choisis est utilisée pour récupérer les champs de la table choisis. Puis les champs sont mis dans une liste.
 * @param item
 */
void MainWindow::on_listWidgetTables_itemClicked(QListWidgetItem *item)
{
    ui->listWidgetChamps->clear();
    QString tables = item->text();
    QString requete = "show fields from ";
    requete += tables;
    requete += ";";
    // qDebug() << requete;
    QSqlQuery rechercheChamps(requete);
    while(rechercheChamps.next()){
        QString table = rechercheChamps.value(0).toString();
        ui->listWidgetChamps->addItem(table);
    }
}

/**
 * @brief A chaque modification du texte de la requête
 * A chaque modification, la requête est tester dans la base de données, si elle fonctionne on affiche le résultat dans un tableau et le bouton "?" est en vert, sinon on ne fait rien et le bouton "?" est en rouge
 */
void MainWindow::on_textEditRequete_textChanged()
{
    QStringList listeNomColonne;
    QString requete = ui->textEditRequete->toPlainText();
    qDebug() << requete;
    if(!(requete.endsWith(';'))){
        requete += ";";
    }
    qDebug() << requete;
    QSqlQuery rechercheBdd(requete);
    if(rechercheBdd.isActive()){
        ui->pushButtonInfos->setStyleSheet("background-color: green;");
        erreurSql = "";
        QSqlRecord rec = rechercheBdd.record();
        int nbreColonne = rec.count();
        ui->tableWidgetResultat->setColumnCount(nbreColonne);
        int nbreLigne = rechercheBdd.size();
        ui->tableWidgetResultat->setRowCount(nbreLigne);
        for(int colonne = 0; colonne < nbreColonne; colonne++){
            QString nomColonne = rec.fieldName(colonne);
            listeNomColonne.push_back(nomColonne);
        }
        ui->tableWidgetResultat->setHorizontalHeaderLabels(listeNomColonne);
        int row = 0;
        while(rechercheBdd.next()){
            for(int i=0; i<nbreColonne; i++){
                QString infos = rechercheBdd.value(i).toString();
                QTableWidgetItem * infosItem = new QTableWidgetItem(infos);
                ui->tableWidgetResultat->setItem(row, i, infosItem);
                qDebug() << infos;
            }
            row ++;
        }
        ui->pushButtonHistorise->setEnabled(true);
    } else {
        ui->pushButtonInfos->setStyleSheet("background-color: red;");
        erreurSql = rechercheBdd.lastError().text();
        ui->pushButtonHistorise->setEnabled(false);
    }
}

/**
 * @brief Le bouton d'information
 * Affiche l'erreur sql correspondant à la requête écrite, l'erreur sql ne change que si on rappui sur le bouton
 */
void MainWindow::on_pushButtonInfos_clicked()
{
    ui->labelInfos->setText(erreurSql);
}

/**
 * @brief Lancement de requête à partir de l'historique
 * Lorsqu'on appui sur une requête dans l'historique elle est affiché dans le textEdit et elle se lance directement
 * @param item
 */
void MainWindow::on_listWidgetHistorique_itemClicked(QListWidgetItem *item)
{
    ui->textEditRequete->clear();
    QString requete = item->text();
    ui->textEditRequete->setText(requete);
}

/**
 * @brief Sauvegarde de l'historique
 * Sauvegarde dans un fichier (.sql) toutes les requêtes présentent dans l'historique
 */
void MainWindow::on_pushButtonSauvegarde_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save file"), "/home", "*.sql");
    QFile file(fileName+".sql");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for(int resultLigne = 0; resultLigne < ui->listWidgetHistorique->count(); resultLigne++ ){
        QString data = ui->listWidgetHistorique->item(resultLigne)->text();
        qDebug() << data;
        if(!(data.endsWith(';'))){
            out << data ;
        } else {
            out << data ;
            out << "\n";
        }

    }
}

/**
 * @brief Ajout dans l'historique
 * Si la requête est valide, elle peut être ajouté dans la liste d'hisorique lorsqu'on appui sur le bouton pour historiser
 */
void MainWindow::on_pushButtonHistorise_clicked()
{
    QString requete = ui->textEditRequete->toPlainText();

    if(requete.endsWith(';')){
        ui->listWidgetHistorique->addItem(requete);
    } else {
        requete += ";";
        ui->listWidgetHistorique->addItem(requete);
    }
    ui->pushButtonHistorise->setEnabled(false);
}

/**
 * @brief Charger un fichier
 * Permet de charger un fichier (.sql), pour afficher les requêtes de ce fichier dans la liste d'historique
 */
void MainWindow::on_pushButtonLoad_clicked()
{
    QString ligne;
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open file"), "/home", "*.sql");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QString line = file.readLine();
        qDebug() << line;
        if(!(line.endsWith(';'))){
            // qDebug() << "2";
            ligne += line;
        } else {
            // qDebug() << "1";
            ligne += line;
            ui->listWidgetHistorique->addItem(ligne);
            ligne="";
        }
    }
}

/**
 * @brief Exporter le résultat
 * Permet d'exporter le résultat de la requête au fomat csv
 */
void MainWindow::on_pushButtonExporter_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save file"), "/home", "*.csv");
    QFile file(fileName+".csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    int nbreLigne = ui->tableWidgetResultat->rowCount();
    int nbreColonne = ui->tableWidgetResultat->columnCount();
    for(int resultLigne = 0; resultLigne < nbreLigne; resultLigne++ )
    {
        QStringList listeDesValeurs;
        for(int numColonne = 0; numColonne < nbreColonne; numColonne++ )
        {
            QString data = ui->tableWidgetResultat->item(resultLigne, numColonne)->text();
            listeDesValeurs<<data;
         }//fin du for toutes les valeurs de la ligne
        out << listeDesValeurs.join(";") << "\n";

    }
}

/**
 * @brief Fermer l'application
 */
void MainWindow::on_actionQuit_activated()
{
    close();
}

/**
 * @brief Charger un fichier
 */
void MainWindow::on_actionLoad_file_activated()
{
    on_pushButtonLoad_clicked();
}

/**
 * @brief Ouvrir le about de l'application
 */
void MainWindow::on_actionAbout_activated()
{
    DialogAbout dialAbout;
    if(dialAbout.exec()==DialogAbout::Accepted){
    }
}
