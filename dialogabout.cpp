#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de la classe DialogAbout
 */
DialogAbout::~DialogAbout()
{
    delete ui;
}

/**
 * @brief Fermeture de la fenêtre "about" lors de l'appui sur le bouton pour quitter
 */
void DialogAbout::on_pushButtonQuitter_clicked()
{
    close();
}
