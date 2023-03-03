#include "whatsprog_login.h"
#include "ui_whatsprog_login.h"
#include <iostream>
WhatsProgLogin::WhatsProgLogin(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WhatsProgLogin),
  novoUsuario(false)
{
  ui->setupUi(this);

  ui->lineEditSenhaUsuario->setEchoMode( QLineEdit::Password );
}

WhatsProgLogin::~WhatsProgLogin()
{
  delete ui;
}

void WhatsProgLogin::slotLogin(bool NovoUsuario)
{
  novoUsuario = NovoUsuario;
  if (novoUsuario) setWindowTitle("Usuario - Criar");
  else setWindowTitle("Usuario - Conectar");
  ui->lineEditIpServidor->clear();
  ui->lineEditNomeUsuario->clear();
  ui->lineEditSenhaUsuario->clear();
  show();
}

void WhatsProgLogin::on_buttonBox_accepted()
{
    QString Ip_serv = ui->lineEditIpServidor->text();
    QString usuario = ui->lineEditNomeUsuario->text();
    QString senha = ui->lineEditSenhaUsuario->text();

    emit signConectar(Ip_serv,usuario,senha,novoUsuario);

}
