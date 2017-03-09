#include "dialogconnection.h"
#include "ui_dialogconnection.h"
#include "mainwindow.h"


DialogConnection::DialogConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnection)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de la classe DialogConnection
 */
DialogConnection::~DialogConnection()
{
    delete ui;
}

/**
 * @brief Connexion au reste de l'application si le login et mot de passe sont corrects
 */
void DialogConnection::on_pushButtonConnexion_clicked()
{
    extern QSqlDatabase connection;
    QString login = ui->lineEditPseudo->text();
    QString motDePasse = ui->lineEditMdp->text();
    QString hostName = ui->lineEditHostName->text();
    connection = QSqlDatabase::addDatabase("QMYSQL");
    // connection.setDatabaseName("gestionContact");
    connection.setHostName(hostName);
    connection.setUserName(login);
    connection.setPassword(motDePasse);
    // "gestionContact adminDBGContact"
    if(connection.open()){
        accept();
    } else {
        qDebug() << "L'ouverture de la session à échoué";
    }
}

/**
 * @brief Fermeture de l'application si on appui sur le bouton quitter
 */
void DialogConnection::on_pushButtonQuitter_clicked()
{
    close();
}
