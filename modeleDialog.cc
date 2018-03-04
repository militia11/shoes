#include "modeleDialog.h"
#include "ui_modeleDialog.h"

void modeleDialog::resetRodzaje() {
    filtrRodzaje.r1 = QString("");
    filtrRodzaje.r2 = QString("");
    filtrRodzaje.r3 = QString("");
    filtrRodzaje.r4 = QString("");
    filtrRodzaje.r5 = QString("");
    filtrRodzaje.r6 = QString("");
    filtrRodzaje.mont = QString("");
    filtrRodzaje.typ = QString("");
}

modeleDialog::modeleDialog(ZdjecieDialog *zdj,
                           owyModelDialog *nowyModDialog,
                           BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modeleDialog), dbManager(db), nowyModDialog(nowyModDialog),
    dialogZdj(zdj),
    proxy(nullptr) {
    ui->setupUi(this);
    label1 = new clickableLabel(this);
    ui->horizontalLay1->addWidget(label1);
    label2 = new clickableLabel(this);
    ui->horizontalLay1_2->addWidget(label2);
    label3 = new clickableLabel(this);
    ui->horizontalLay1_3->addWidget(label3);
    label4 = new clickableLabel(this);
    ui->horizontalLay1_4->addWidget(label4);
    label1->setScaledContents(true);
    label2->setScaledContents(true);
    label3->setScaledContents(true);
    label4->setScaledContents(true);
    connect(label1, &clickableLabel::clicked, this, &modeleDialog::zdj1);
    connect(label2, &clickableLabel::clicked, this, &modeleDialog::zdj2);
    connect(label3, &clickableLabel::clicked, this, &modeleDialog::zdj3);
    connect(label4, &clickableLabel::clicked, this, &modeleDialog::zdj4);
    proxy = new QSortFilterProxyModel(this);
    ui->checkBox1->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox1->setFocusPolicy(Qt::NoFocus);
    ui->checkBox2->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox2->setFocusPolicy(Qt::NoFocus);
    ui->checkBox3->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox3->setFocusPolicy(Qt::NoFocus);
    ui->checkBox4->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBox4->setFocusPolicy(Qt::NoFocus);
    ui->comboBoxtyp->setFixedWidth(124);
    ui->comboBoxmont->setFixedWidth(124);
    ui->comboBoxb1->setFixedWidth(124);
    ui->comboBoxb2->setFixedWidth(124);
    ui->comboBoxb3->setFixedWidth(124);
    ui->comboBoxb4->setFixedWidth(124);
    ui->comboBoxb5->setFixedWidth(124);
    ui->comboBoxb6->setFixedWidth(124);
    ui->lineEditkol->setFixedWidth(124);
    ui->lineEditma->setFixedWidth(124);
    ui->lineEditoc->setFixedWidth(124);
    ui->lineEditspna->setFixedWidth(124);
    ui->lineEditwkl->setFixedWidth(124);
    ui->lineEditwz->setFixedWidth(124);
    resetRodzaje();
}

modeleDialog::~modeleDialog() {
    delete ui;
    delete proxy;
}

int modeleDialog::selectExec() {
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoModel(const QModelIndex)));
    createCombos();
    ui->checkBox1->hide();
    ui->checkBox2->hide();
    ui->checkBox3->hide();
    ui->checkBox4->hide();
    return QDialog::exec();
}

void modeleDialog::ustawIFiltruj() {
    QString f = QString("nr_wzoru LIKE '%1%' AND nazwa LIKE '%2%' AND rodzaj LIKE '%3%' AND kolor LIKE '%4%'"
        "AND spnaz LIKE '%5%' AND wkrodzaj LIKE '%6%' AND typ LIKE '%7%' AND rodzaj_montazu LIKE '%8%'").arg(
                    ui->lineEditwz->text(), ui->lineEditma->text(), ui->lineEditoc->text(), ui->lineEditkol->text(),
                    ui->lineEditspna->text(), ui->lineEditwkl->text(), filtrRodzaje.typ, filtrRodzaje.mont);
    f += QString(" AND rodzaj_buta LIKE '%1%' AND rodzaj_buta_2 LIKE '%2%' AND rodzaj_buta_3 LIKE '%3%' AND rodzaj_buta_4 LIKE '%4%' AND rodzaj_buta_5 LIKE '%5%' AND rodzaj_buta_6 LIKE '%6%'").
         arg(filtrRodzaje.r1,  filtrRodzaje.r2, filtrRodzaje.r3, filtrRodzaje.r4,  filtrRodzaje.r5, filtrRodzaje.r6);
    dbManager->getModele()->setFilter(f);
}

int modeleDialog::exec() {
    createCombos();
    ui->checkBox1->show();
    ui->checkBox2->show();
    ui->checkBox3->show();
    ui->checkBox4->show();
    return QDialog::exec();
}

void modeleDialog::wybranoModel(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableView->selectionModel()->currentIndex());
    dbManager->ustawAktualnyModelId(idx);
    accept();
}

void modeleDialog::zdj1() {
    if (!image1.isNull()) {
        label1->setPixmap(QPixmap::fromImage(image1));
        showPhoto(image1);
    }
}

void modeleDialog::zdj2() {
    if (!image2.isNull()) {
        label2->setPixmap(QPixmap::fromImage(image2));
        showPhoto(image2);
    }

}

void modeleDialog::zdj3() {
    if (!image3.isNull()) {
        label3->setPixmap(QPixmap::fromImage(image3));
        showPhoto(image3);
    }
}

void modeleDialog::zdj4() {
    if (!image4.isNull()) {
        label4->setPixmap(QPixmap::fromImage(image4));
        showPhoto(image4);
    }
}

void modeleDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setModele();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getModele());
    ui->tableView->setModel(proxy);
    ui->tableView->setSortingEnabled(true);
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Stretch);
    }
    QHeaderView *hv = ui->tableView->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setSectionHidden(0, true);
    hv->setSectionHidden(17, true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ustawIFiltruj();
}

void modeleDialog::hideEvent(QHideEvent *e) {
    wyczyscPola();
    disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
               SLOT(wybranoModel(const QModelIndex)));
}

int modeleDialog::getId() {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableView->selectionModel()->currentIndex());
    return  dbManager->getModele()->data(
                dbManager->getModele()->index(idx.row(),
                        0)).toInt();
}

void modeleDialog::ustawCombo(QString tabela, QComboBox *com) {
    com->clear();
    QString q = QString("select *from %1").arg(tabela);
    QSqlQuery query(q);
    QAbstractItemModel *vModel = dbManager->getModelForQuery(&query);
    com->addItem(QString(""), QVariant(0));
    if (vModel) {
        for (int i = 0; i < vModel->rowCount(); ++i) {
            QString vEventName = vModel->data(vModel->index(i, 1)).toString();
            QVariant vEventMnemonic = vModel->data(vModel->index(i, 1));
            com->addItem(
                vEventName,
                vEventMnemonic);
        }
        delete vModel;
    }
}

void modeleDialog::createCombos() {
    ustawCombo("rodzaj_montazu", ui->comboBoxmont);
    ustawCombo("typ", ui->comboBoxtyp);
    ustawCombo("rodzaj_buta", ui->comboBoxb1);
    ustawCombo("rodzaj_buta_2", ui->comboBoxb2);
    ustawCombo("rodzaj_buta_3", ui->comboBoxb3);
    ustawCombo("rodzaj_buta_4", ui->comboBoxb4);
    ustawCombo("rodzaj_buta_5", ui->comboBoxb5);
    ustawCombo("rodzaj_buta_6", ui->comboBoxb6);
}

void modeleDialog::on_pushButton_2_clicked() {
    nowyModDialog->setFixedSize(nowyModDialog->size());
    nowyModDialog->exec();
}

void modeleDialog::showPhoto(QImage im) {
    dialogZdj->setLabel(im);
    dialogZdj->exec();
}

void modeleDialog::on_pushButton_3_clicked() {
    int id = getId();
    nowyModDialog->editExec(id);
}

void modeleDialog::wyczyscPola() {
    ui->pushButton_3->setEnabled(false);
    label1->clear();
    label2->clear();
    label3->clear();
    label4->clear();
    image1 = QImage();
    image2 = QImage();
    image3 = QImage();
    image4 = QImage();
    ui->checkBox1->setChecked(true);
}

void modeleDialog::on_tableView_clicked(const QModelIndex &index) {
    if (ui->pushButton_3->isEnabled() == false) {
        ui->pushButton_3->setEnabled(true);
    }
    label1->clear();
    label2->clear();
    label3->clear();
    label4->clear();
    int id = getId();
    image1 = dbManager->getImage(id, 1, QString("modele"));
    image2 = dbManager->getImage(id, 2, QString("modele"));
    image3 = dbManager->getImage(id, 3, QString("modele"));
    image4 = dbManager->getImage(id, 4, QString("modele"));

    label1->setPixmap(QPixmap::fromImage(image1));
    label2->setPixmap(QPixmap::fromImage(image2));
    label3->setPixmap(QPixmap::fromImage(image3));
    label4->setPixmap(QPixmap::fromImage(image4));
    int wysZdj = dbManager->getWysZdj(id);
    switch (wysZdj) {
        case 1:
            ui->checkBox1->setChecked(true);
            break;
        case 2:
            ui->checkBox2->setChecked(true);
            break;
        case 3:
            ui->checkBox3->setChecked(true);
            break;
        case 4:
            ui->checkBox4->setChecked(true);
            break;
    }
}

void modeleDialog::on_pushButtonSzukaj_clicked() {
    ustawIFiltruj();
}

void modeleDialog::on_pushButton_clicked() {
    ui->comboBoxtyp->setCurrentIndex(0);
    ui->comboBoxmont->setCurrentIndex(0);
    ui->comboBoxb1->setCurrentIndex(0);
    ui->comboBoxb2->setCurrentIndex(0);
    ui->comboBoxb3->setCurrentIndex(0);
    ui->comboBoxb4->setCurrentIndex(0);
    ui->comboBoxb5->setCurrentIndex(0);
    ui->comboBoxb6->setCurrentIndex(0);
    ui->lineEditkol->clear();
    ui->lineEditma->clear();
    ui->lineEditoc->clear();
    ui->lineEditspna->clear();
    ui->lineEditwkl->clear();
    ui->lineEditwz->clear();
    resetRodzaje();
    ustawIFiltruj();
}

void modeleDialog::on_comboBoxtyp_activated(int index) {
    filtrRodzaje.typ =  ui->comboBoxtyp->currentText();
    ustawIFiltruj();
}

void modeleDialog::on_comboBoxmont_activated(int index) {
    filtrRodzaje.mont = ui->comboBoxmont->currentText();
    ustawIFiltruj();
}

void modeleDialog::on_comboBoxb1_activated(int index) {
    filtrRodzaje.r1 = ui->comboBoxb1->currentText();
    ustawIFiltruj();
}

void modeleDialog::on_comboBoxb2_activated(int index) {
    filtrRodzaje.r2 = ui->comboBoxb2->currentText();
    ustawIFiltruj();
}

void modeleDialog::on_comboBoxb3_activated(int index) {
    filtrRodzaje.r3 = ui->comboBoxb3->currentText();
    ustawIFiltruj();
}

void modeleDialog::on_comboBoxb4_activated(int index) {
    filtrRodzaje.r4 = ui->comboBoxb4->currentText();
    ustawIFiltruj();

}

void modeleDialog::on_comboBoxb5_activated(int index) {
    filtrRodzaje.r5 = ui->comboBoxb5->currentText();
    ustawIFiltruj();

}

void modeleDialog::on_comboBoxb6_activated(int index) {
    filtrRodzaje.r6 = ui->comboBoxb6->currentText();
    ustawIFiltruj();
}

