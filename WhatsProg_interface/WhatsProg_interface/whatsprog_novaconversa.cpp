#include <string>
#include <QMessageBox>
#include "whatsprog_novaconversa.h"
#include "ui_whatsprog_novaconversa.h"
#include "whatsprog_dados_cliente.h"

WhatsProgNovaConversa::WhatsProgNovaConversa(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WhatsProgNovaConversa)
{
  ui->setupUi(this);
}

WhatsProgNovaConversa::~WhatsProgNovaConversa()
{
  delete ui;
}

void WhatsProgNovaConversa::on_buttonBox_accepted()

{
        QString user = ui->lineEditConversa->text();

       if (testarNomeUsuario(user.toStdString()))
       {
           emit signAtualizaConversas();
           return;
       }

       QMessageBox msgBox;
       msgBox.setWindowTitle("Erro na conversa");
       msgBox.setText("Nao foi possivel iniciar uma conversa com ("+user+")");
       msgBox.exec();
       return;

}
