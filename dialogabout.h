#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>


namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructeur de la classe DialogAbout
     * @param QWidget* parent
     */
    explicit DialogAbout(QWidget *parent = 0);
    /**
     * @brief Destructeur de la classe DialogAbout
     */
    ~DialogAbout();
    
private slots:
    /**
     * @brief Fonction qui est appelé lorsque l'on appui sur le bouton quitter
     */
    void on_pushButtonQuitter_clicked();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
