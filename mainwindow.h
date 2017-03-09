#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructeur de la classe MainWindow
     * @param QWidget* parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief Destructeur de la classe MainWindow
     */
    ~MainWindow();
    
private slots:
    /**
     * @brief Fonction appelé lorsqu'on choisit une base de données
     * @param QString nomBase : nom de la base de données choisis
     */
    void on_comboBoxBdd_activated(const QString &nomBase);

    /**
     * @brief Fonction appelé lorsqu'on clique sur un item de la liste des tables
     * @param QListWidgetItem* item : l'item de la liste choisis
     */
    void on_listWidgetTables_itemClicked(QListWidgetItem *item);

    /**
     * @brief Fonction appelé à chaque fois que le texte change dans le textEdit
     */
    void on_textEditRequete_textChanged();

    /**
     * @brief Fonction appelé à chaque fois qu'on appui sur le bouton d'infos, le "?"
     */
    void on_pushButtonInfos_clicked();

    /**
     * @brief Fonction appelé lorsque l'on clique sur un item de la liste d'historique
     * @param QListWidgetItem* item : L'item de la liste chosis
     */
    void on_listWidgetHistorique_itemClicked(QListWidgetItem *item);

    /**
     * @brief Fonction appelé à chaque fois qu'on appui sur le bouton pour sauvegarder l'historique
     */
    void on_pushButtonSauvegarde_clicked();

    /**
     * @brief Fonction appelé à chaque fois qu'on appui sur le bouton pour historiser l'historique
     */
    void on_pushButtonHistorise_clicked();

    /**
     * @brief Fonction appelé à chaque fois qu'on appui sur le bouton pour charger un fichier texte contenant des requêtes historique
     */
    void on_pushButtonLoad_clicked();

    /**
     * @brief Fonction appelé à chaque fois qu'on appui sur le bouton pour exporter le résultat de la requête au format csv
     */
    void on_pushButtonExporter_clicked();

    /**
     * @brief Fonction appelé lorsque l'on appui sur le menu "fichier" puis "quitter"
     */
    void on_actionQuit_activated();

    /**
     * @brief Fonction appelé lorsque l'on appui sur le menu "fichier" et "charger fichier"
     */
    void on_actionLoad_file_activated();

    /**
     * @brief Fonction appelé lorsque l'on appui sur le menu "?" et "about"
     */
    void on_actionAbout_activated();

private:
    Ui::MainWindow *ui;
    /**
     * @brief L'erreur sql récupéré, tant que le résultat est faux, en QString
     */
    QString erreurSql;
    /**
     * @brief Vecteur contenant les requêtes de l'historique
     */
    QVector<QString> vecteurHistorique;
};

#endif // MAINWINDOW_H
