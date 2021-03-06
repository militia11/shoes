#include "klienciDialog.h"
#include "ui_klienciDialog.h"
#include <QStyle>
#include <QDesktopWidget>


klienciDialog::klienciDialog(nowyKlientDialog *nowyKliDialog,
                             BazaDanychManager *db, QWidget *parent) :
    QDialog(parent), ui(new Ui::klienciDialog), dbManager(db),
    nowyKliDialog(nowyKliDialog), proxy(nullptr) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
    myDelegate = new Delegate(dbManager, this);
    ui->tableViewKlienci->setItemDelegate(myDelegate);
    connect(myDelegate, SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), this, SLOT(abra(QWidget*,QAbstractItemDelegate::EndEditHint)));
    ui->tableViewKlienci->verticalHeader()->setDefaultSectionSize(ui->tableViewKlienci->verticalHeader()->minimumSectionSize());
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

klienciDialog::~klienciDialog() {
    delete ui;
    delete proxy;
}

int klienciDialog::selectExec() {
    dbManager->setHandlowce();
    ui->tableViewKlienci->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableViewKlienci, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoKli(const QModelIndex)));
    return QDialog::exec();
}

int klienciDialog::exec() {
    ui->tableViewKlienci->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

void klienciDialog::abra(QWidget *,QAbstractItemDelegate::EndEditHint) {
    dbManager->getModelKlienci()->select();
    ui->tableViewKlienci->update();
}

void klienciDialog::wybranoKli(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableViewKlienci->selectionModel()->currentIndex());
    dbManager->ustawIdAktualnegoKlienta(idx);
    aktualnyKlientNazwa = dbManager->pobierzNazweAktualnegoKlienta();
    accept();
}

void klienciDialog::aktualizujHeader() {
    QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->lineEditMi->setFixedWidth(118);
    ui->lineEditNr->setFixedWidth(118);
    ui->lineEditNazwaSkrot->setFixedWidth(118);
    ui->lineEditSkrot->setFixedWidth(118);
    ui->lineEditWoj->setFixedWidth(118);
    ui->comboBox->setFixedWidth(118);
    ui->lineEditKr->setFixedWidth(118);
    ui->tableViewKlienci->sortByColumn(0, Qt::AscendingOrder);
    ui->tableViewKlienci->horizontalHeader()->setMinimumSectionSize(13);
    ui->tableViewKlienci->setColumnHidden(16, true);
}

void klienciDialog::aktualizujTabele() {
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getModelKlienci());
    ui->tableViewKlienci->setModel(proxy);
    ui->tableViewKlienci->setSortingEnabled(true);
    for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
        ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Stretch);
    }
    aktualizujHeader();
    combo();
}

void klienciDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setKlienci();
    dbManager->setKliR();
    aktualizujTabele();
    ui->lineEditNazwaSkrot->clear();
    ui->lineEditSkrot->clear();
    ui->lineEditMi->clear();
    ui->lineEditNr->clear();
    ui->pushSzukaj->setFocus();
    ustawIFiltruj();
}

void klienciDialog::hideEvent(QHideEvent *e) {
    disconnect(ui->tableViewKlienci, SIGNAL(doubleClicked(const QModelIndex)), this,
               SLOT(wybranoKli(const QModelIndex)));
}

QString klienciDialog::getAktualnyKlientNazwa() const {
    return aktualnyKlientNazwa;
}

void klienciDialog::ustawIFiltruj() {
    dbManager->filterKlientow.miasto = ui->lineEditMi->text();
    dbManager->filterKlientow.nazwa = ui->lineEditSkrot->text();
    dbManager->filterKlientow.skrot = ui->lineEditNazwaSkrot->text();
    dbManager->filterKlientow.nr = ui->lineEditNr->text();
    dbManager->filterKlientow.han = ui->comboBox->currentText();
    dbManager->setKlienciFilter();
}

void klienciDialog::on_pushButton_2_clicked() {
    if ( nowyKliDialog->exec() == QDialog::Accepted ) {
        Klient klient(nowyKliDialog->getNazwa(), nowyKliDialog->getSkrot(),
                      nowyKliDialog->getUlica(),
                      nowyKliDialog->getNumerDomu(),
                      nowyKliDialog->getMiasto(), nowyKliDialog->getKodPocztowy(),
                      nowyKliDialog->getTel1(),
                      nowyKliDialog->getTel2(),
                      nowyKliDialog->getFax(), nowyKliDialog->getMail(),
                      nowyKliDialog->getUwagi(),
                      nowyKliDialog->getNumerTelefonu(),
                      nowyKliDialog->getWoj(),
                      nowyKliDialog->getKraj());
        dbManager->zachowajKlienta(klient);
        aktualizujHeader();
        combo();
    }
}

void klienciDialog::on_pushSzukaj_clicked() {
    ustawIFiltruj();
}

void klienciDialog::on_pushButton_clicked() {
    ui->lineEditNr->clear();
    ui->lineEditNazwaSkrot->setText("");
    ui->lineEditSkrot->setText("");
    ui->lineEditMi->setText("");
    ui->lineEditWoj->setText("");
    ui->lineEditKr->setText("");


    ui->comboBox->setCurrentText("");
    ui->comboBox->setCurrentIndex(0);
//todo
    ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
    ui->tableViewKlienci->sortByColumn(0, Qt::AscendingOrder);
    ustawIFiltruj();
}

void klienciDialog::combo() {
    ui->comboBox->clear();
    QString q = QString("select skrot, id from handlowce");
    QSqlQuery query(q);
    QAbstractItemModel *vModel = dbManager->getModelForQuery(&query);
    ui->comboBox->addItem(QString(""), QVariant(0));
    if (vModel) {
        for (int i = 0; i < vModel->rowCount(); ++i) {
            QString vEventName = vModel->data(vModel->index(i, 0)).toString();
            QVariant vEventMnemonic = vModel->data(vModel->index(i, 1));
            ui->comboBox->addItem(
                vEventName,
                vEventMnemonic);
        }
        delete vModel;
    }
}

void klienciDialog::on_comboBox_activated(const QString &arg1) {
    dbManager->filterKlientow.han = ui->comboBox->currentText();
    ustawIFiltruj();
}
