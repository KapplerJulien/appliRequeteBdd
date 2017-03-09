#ifndef DIALOGCONNECTION_H
#define DIALOGCONNECTION_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class DialogConnection;
}

class DialogConnection : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructeur de la classe DialogConnection
     * @param QWidget* parent
     */
    explicit DialogConnection(QWidget *parent = 0);
    /**
     * @brief Destructeur de la classe DialogConnection
     */
    ~DialogConnection();
    
private slots:
    /**
     * @brief Fonction appelé lorsque l'on clique sur le bouton connexion
     */
    void on_pushButtonConnexion_clicked();

    /**
     * @brief Fonction appelé lorsque l'on clique sur le bouton quitter
     */
    void on_pushButtonQuitter_clicked();

private:
    Ui::DialogConnection *ui;
};

#endif // DIALOGCONNECTION_H
