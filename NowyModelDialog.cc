#include "NowyModelDialog.h"
#include "ui_NowyModelDialog.h"
#include "ManagerZdjec.h"
#include <QInputDialog>
NowyModelDialog::NowyModelDialog(wkladkaDialog *w, ocieplenieDialog *oc, wzoryDialog *wz, skoryDialog *s,
				 koloryDialog *k,
				 spodyDialog *sp,
				 matryceDialog *matryce,
				 BazaDanychManager *dbManager,
				 QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NowyModelDialog),  s(s),  matryce(matryce) ,
	dbManager(dbManager), w(w),
	k(k), sp(sp), oc(oc), wz(wz)
{
	ui->setupUi(this);
	editExecc = false;
}

NowyModelDialog::~NowyModelDialog() {
	delete ui;
}

void NowyModelDialog::createCombos() {
	ustawCombo("rodzaj_montazu", ui->comboBoxmont);
	ustawCombo("typ", ui->comboBoxtyp);
	ustawCombo("rodzaj_buta", ui->comboBoxb1);
	ustawCombo("rodzaj_buta_2", ui->comboBoxb2);
	ustawCombo("rodzaj_buta_3", ui->comboBoxb3);
	ustawCombo("rodzaj_buta_4", ui->comboBoxb4);
	ustawCombo("rodzaj_buta_5", ui->comboBoxb5);
	ustawCombo("rodzaj_buta_6", ui->comboBoxb6);
}

int NowyModelDialog::editExec(int id) {
	dbManager->setIdModelu(id);
	editExecc = true;
	QVector<QString> list = dbManager->zwrocListeModel(id);
	ui->labelKolor->setText(list[2]);
	ui->labelMatryca->setText(list[4]);
	ui->labelSpod->setText(list[1]);
	ui->labelOciep->setText(list[3]);
	ui->labelSko->setText(list[6]);
	ui->labelWzor->setText(list[0]);
	ui->labelWkladka->setText(list[5]);

	ui->plainTextEdit1->setPlainText(dbManager->poberzOpis1(id));
	ui->plainTextEdit2->setPlainText(dbManager->poberzOpis2(id));

	createCombos();
	QVector<QString> vec = dbManager->poberzRodzaje(id);
	ui->comboBoxtyp->setCurrentIndex(ui->comboBoxtyp->findData(vec[0]));
	ui->comboBoxmont->setCurrentIndex(ui->comboBoxmont->findData(vec[1]));
	ui->comboBoxb1->setCurrentIndex(ui->comboBoxb1->findData(vec[2]));
	ui->comboBoxb2->setCurrentIndex(ui->comboBoxb2->findData(vec[3]));
	ui->comboBoxb3->setCurrentIndex(ui->comboBoxb3->findData(vec[4]));
	ui->comboBoxb4->setCurrentIndex(ui->comboBoxb4->findData(vec[5]));
	ui->comboBoxb5->setCurrentIndex(ui->comboBoxb5->findData(vec[6]));
	ui->comboBoxb6->setCurrentIndex(ui->comboBoxb6->findData(vec[7]));

	ui->labelPodglad1->clear();
	ui->labelPodglad2->clear();
	ui->labelPodglad3->clear();
	ui->labelPodglad4->clear();
	for (int i = 0; i < 4; i++) {
		images.append(QImage());
	}

	images[0] = dbManager->getImage(id, 1, QString("modele"));
	images[1] = dbManager->getImage(id, 2, QString("modele"));
	images[2] = dbManager->getImage(id, 3, QString("modele"));
	images[3] = dbManager->getImage(id, 4, QString("modele"));

	ui->labelPodglad1->setPixmap(QPixmap::fromImage(images[0]));
	ui->labelPodglad2->setPixmap(QPixmap::fromImage(images[1]));
	ui->labelPodglad3->setPixmap(QPixmap::fromImage(images[2]));
	ui->labelPodglad4->setPixmap(QPixmap::fromImage(images[3]));
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

	return QDialog::exec();
}

int NowyModelDialog::exec() {
	editExecc = false;
	for (int i = 0; i < 4; i++) {
		images.append(QImage());
	}
	createCombos();
	return QDialog::exec();
}

void NowyModelDialog::on_pushButton_9_clicked() {
	if (matryce->selectExec() == QDialog::Accepted) {
		ui->labelMatryca->setText(matryce->getAktualnaMatrycaNazwa());
	}
}

void NowyModelDialog::on_pushButton_14_clicked() {
	images[0] = ManagerZdjec::getImage(this);
	if (!images[0].isNull()) {
		ui->labelPodglad1->setPixmap(QPixmap::fromImage(images[0]));
	}
}

void NowyModelDialog::on_pushButton_15_clicked() {
	images[1] = ManagerZdjec::getImage(this);
	if (!images[1].isNull()) {
		ui->labelPodglad2->setPixmap(QPixmap::fromImage(images[1]));
	}
}

void NowyModelDialog::on_pushButton_16_clicked() {
	images[2] = ManagerZdjec::getImage(this);
	if (!images[2].isNull()) {
		ui->labelPodglad3->setPixmap(QPixmap::fromImage(images[2]));
	}
}

void NowyModelDialog::on_pushButton_17_clicked() {
	images[3] = ManagerZdjec::getImage(this);
	if (!images[3].isNull()) {
		ui->labelPodglad4->setPixmap(QPixmap::fromImage(images[3]));
	}
}

void NowyModelDialog::on_pushButton_12_clicked() {
	if (k->selectExec() == QDialog::Accepted) {
		ui->labelKolor->setText(QString::number(k->getAktualnyKolor()));
	}
}

void NowyModelDialog::on_pushButton_21_clicked() {
	if (s->selectExec() == QDialog::Accepted) {
		dbManager->setSkory();
		ui->labelSko->setText(s->getAktualnaSkoraNazwa());
	}
}

void NowyModelDialog::on_pushButton_25_clicked() {
	if (sp->selectExec() == QDialog::Accepted) {
		dbManager->setSpody();
		ui->labelSpod->setText(sp->getAktualnySpodNazwa());
	}
}

void NowyModelDialog::ustawCombo(QString tabela, QComboBox *com) {
	com->clear();
	QString q = QString("select *from %1").arg(tabela);
	QSqlQuery query (q);
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

void NowyModelDialog::hideEvent(QHideEvent *e) {
	wyczyscPola();
}

void NowyModelDialog::wyczyscPola() {
	ui->labelKolor->clear();
	ui->labelSpod->clear();
	ui->labelMatryca->clear();
	ui->labelOciep->clear();
	ui->labelSko->clear();
	ui->labelWkladka->clear();
	ui->labelWzor->clear();
	ui->labelPodglad1->clear();
	ui->labelPodglad2->clear();
	ui->labelPodglad3->clear();
	ui->labelPodglad4->clear();
	ui->plainTextEdit1->clear();
	ui->plainTextEdit2->clear();
	ui->labelPodglad1->clear();
	ui->labelPodglad2->clear();
	ui->labelPodglad3->clear();
	ui->labelPodglad4->clear();
	images.clear();
}

void NowyModelDialog::on_pushButton_10_clicked() {
	if (wz->selectExec() == QDialog::Accepted) {
		dbManager->setWzory();
		ui->labelWzor->setText(QString::number(wz->getAktualnyWzorNr()));
	}
}

void NowyModelDialog::on_pushButton_11_clicked() {
	if (oc->selectExec() == QDialog::Accepted) {
		dbManager->setOciep();
		ui->labelOciep->setText(oc->getAktualnyKolor());
	}
}

int NowyModelDialog::zwrocWybZdjecie() {
	int wysZdj = -1;
	if (ui->checkBox1->checkState() == Qt::Checked) {
		wysZdj = 1;
	}
	else if (ui->checkBox2->checkState() == Qt::Checked) {
		wysZdj = 2;
	}
	else if (ui->checkBox3->checkState() == Qt::Checked) {
		wysZdj = 3;
	}
	else if (ui->checkBox4->checkState() == Qt::Checked) {
		wysZdj = 4;
	}

	return  wysZdj;
}

void NowyModelDialog::on_buttonBox_accepted() {
	int wysZdj = zwrocWybZdjecie();
	if (!editExecc) {
		if (ui->labelKolor->text().isEmpty() || ui->labelMatryca->text().isEmpty() ||
				ui->labelOciep->text().isEmpty() || ui->labelSko->text().isEmpty() ||
				ui->labelSpod->text().isEmpty() || ui->labelWkladka->text().isEmpty() ||
				ui->labelWzor->text().isEmpty()) {
			QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
						  " <FONT COLOR='#000080'>Nie można zaakceptować bez wyboru podstawowych pól. "
						  "<br>Proszę uzupełnić dane.</FONT>",
						  QMessageBox::Ok);
		} else {
			dbManager->zachowajModel(images, ui->comboBoxmont->currentText(), ui->comboBoxtyp->currentText(),
						 ui->comboBoxb1->currentText(),
						 ui->comboBoxb2->currentText(), ui->comboBoxb3->currentText(),
						 ui->comboBoxb4->currentText(), ui->comboBoxb5->currentText(), ui->comboBoxb6->currentText(),
						 ui->plainTextEdit1->toPlainText(), ui->plainTextEdit2->toPlainText(), wysZdj);

			wyczyscPola();
			accept();
		}
	} else {
		dbManager->aktualizujModel(images, ui->comboBoxmont->currentText(), ui->comboBoxtyp->currentText(),
					   ui->comboBoxb1->currentText(),
					   ui->comboBoxb2->currentText(), ui->comboBoxb3->currentText(),
					   ui->comboBoxb4->currentText(), ui->comboBoxb5->currentText(), ui->comboBoxb6->currentText(),
					   ui->plainTextEdit1->toPlainText(), ui->plainTextEdit2->toPlainText(), wysZdj);

		wyczyscPola();
		accept();
	}
}

void NowyModelDialog::on_buttonBox_rejected() {
	wyczyscPola();
	reject();
}

void NowyModelDialog::on_pushButton_19_clicked() {
	if (w->selectExec() == QDialog::Accepted) {
		dbManager->setWkladki();
		ui->labelWkladka->setText(w->getAktualnaWkladkaNazwa());
	}
}
