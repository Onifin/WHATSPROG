#include <QWindow>
#include <QMessageBox>
#include <iostream>
#include "whatsprog_main.h"
#include "ui_whatsprog_main.h"
#include <C:\Users\igojo\Documents\Codes PA\MySocket\Mysocket.h>
#include "whatsprog_dados_cliente.h"
#include "whatsprog_thread.h"


using namespace std;

/// Precisa criar ou declarar como "extern"
/// a variavel global que contem todas as msgs de todas as conversas
WhatsProgDadosCliente DC;


/// Precisa criar ou declarar como "extern"
/// o socket do cliente, a ser utilizado por todas as threads
tcp_mysocket sock;


/// Construtor da janela principal da interface
WhatsProgMain::WhatsProgMain(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::WhatsProgMain),
  pixEnviada(),
  pixRecebida(),
  pixEntregue(),
  pixOther(),
  msgStatus(nullptr),
  loginDialog(nullptr),
  novaConversa(nullptr),
  thread(nullptr)

{
  ui->setupUi(this);

  // Cria caixas de dialogos de login e de nova conversa
  loginDialog = new WhatsProgLogin(this);
  novaConversa = new WhatsProgNovaConversa(this);

  // A lista da esquerda (conversas)
  ui->tableConversas->setColumnCount(2);
  ui->tableConversas->setShowGrid(false);
  ui->tableConversas->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableConversas->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableConversas->setTabKeyNavigation(false);
  ui->tableConversas->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
  ui->tableConversas->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
  ui->tableConversas->horizontalHeader()->setSectionsClickable(false);
  // O cabecalho
  ui->tableConversas->setStyleSheet("QHeaderView::section { text-align:center }"
                                    "QHeaderView::section { font: bold }"
                                    "QHeaderView::section { background-color:lightgray }");
  ui->tableConversas->setHorizontalHeaderLabels(QStringList() << "Num" <<  "Usuario");

  // A lista da direita (mensagens)
  ui->tableMensagens->setColumnCount(3);
  ui->tableMensagens->setShowGrid(true);
  ui->tableMensagens->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableMensagens->setSelectionMode(QAbstractItemView::NoSelection);
  ui->tableMensagens->setTabKeyNavigation(false);
  ui->tableMensagens->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
  ui->tableMensagens->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
  ui->tableMensagens->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->tableMensagens->horizontalHeader()->setSectionsClickable(false);
  // O cabecalho
  ui->tableMensagens->setStyleSheet("QHeaderView::section { text-align:center }"
                                    "QHeaderView::section { font: bold }"
                                    "QHeaderView::section { background-color:lightgray }");
  ui->tableMensagens->setHorizontalHeaderLabels(QStringList() << "Id" << "Mensagem" <<  "St");

  // Os icones do status das mensagens
  QString dir = ".\\";
  QString pixfile;

  pixfile = dir+"status0.png";
  if (!pixEnviada.load(pixfile,"PNG"))
  {
      cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
  }
  pixfile = dir+"status1.png";
  if (!pixRecebida.load(pixfile,"PNG"))
  {
      cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
  }
  pixfile = dir+"status2.png";
  if (!pixEntregue.load(pixfile,"PNG"))
  {
      cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
  }
  pixfile = dir+"status_other.png";
  if (!pixOther.load(pixfile,"PNG"))
  {
      cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
  }

  // O icone da aplicacao
  QPixmap pixIcon;
  pixfile = dir+"whatsprog_icon.png";
  if (!pixIcon.load(pixfile,"PNG"))
  {
    cerr << "Erro na leitura do pixmap " << pixfile.toStdString() << endl;
  }
  else
  {
    setWindowIcon(QIcon(pixIcon));
  }

  // A conexao dos sinais e slots
  // Os sinais


  // Os sinais da WhatsProgMain
  connect(this, &WhatsProgMain::signLogin,
          loginDialog, &WhatsProgLogin::slotLogin);
  connect(this, &WhatsProgMain::signShowNovaConversa,
          novaConversa, &WhatsProgNovaConversa::show);
  connect(this, &WhatsProgMain::signIniciaThread,
          thread,&WhatsProg_Thread::slotIniciaThread);


  // Os sinais da WhatsProgLogin
  connect(loginDialog, &WhatsProgLogin::signConectar,
          this, &WhatsProgMain::slotConectar);

  // Os sinais da WhatsProgNovaConversa
  connect(novaConversa, &WhatsProgNovaConversa::signAtualizaConversas,
          this, &WhatsProgMain::slotExibirConversas);
  connect(novaConversa, &WhatsProgNovaConversa::signAtualizaMensagens,
          this, &WhatsProgMain::slotExibirMensagens);

  // Precisa conectar
  // os sinais da classe que contem a thread do cliente

  connect(thread,&WhatsProg_Thread::signErroSalva,
          this,&WhatsProgMain::slotExibirErroMensagem);
  connect(thread,&WhatsProg_Thread::signReexibeErro,
          this,&WhatsProgMain::slotExibirErroMensagem);
  connect(thread,&WhatsProg_Thread::signExibeNovaMensagem,
          this,&WhatsProgMain::slotExibirMensagens);
  connect(thread,&WhatsProg_Thread::signExibeNovaConversa,
          this,&WhatsProgMain::slotExibirConversas);
  //connect(thread,&WhatsProg_Thread::signEncerrar,
       //   this,&WhatsProgMain::slot);


  // A barra de status
  msgStatus = new QLabel("?");
  statusBar()->addWidget(msgStatus);

  // Coloca a interface em modo desconectado
  on_actionDesconectar_triggered();
}

WhatsProgMain::~WhatsProgMain()
{
  delete ui;
}

/// Redesenha a janela de conversas
void WhatsProgMain::slotExibirConversas()
{
  // Redesenha toda a tabela de conversas
  // O redesenho eh diferente caso o cliente esteja conectado ou nao.
  //
  // Testa se o socket estah conectado e
  // os dados de conexao estao corretamente definidos
  //
  // Falta fazer
}

/// Redesenha a janela de mensagens
void WhatsProgMain::slotExibirMensagens()
{
  // Redesenha toda a tabela de mensagens
  // O redesenho eh diferente caso o (cliente esteja conectado e
  // uma conversa esteja selecionada) ou nao.
  //
  // Testa se o socket estah conectado,
  // os dados de conexao estao corretamente definidos e
  // uma conversa estah selecionada
  //
  // Falta fazer
}

/// Redesenha a barra de status
void WhatsProgMain::atualizaEstadoConexao()
{
  // Atualiza a msg na barra de status
  // A atualizacao o eh diferente caso o cliente esteja conectado ou nao.
  //
  // Testa se o socket estah conectado e
  // os dados de conexao estao corretamente definidos
  //
  // Falta fazer
}

/// Conecta-se ao servidor
void WhatsProgMain::slotConectar(const QString &IP, const QString &login,
                                 const QString &senha, bool novoUsuario )
{

// Testa todos os parametros
   if(IP == "" || !testarNomeUsuario(login.toStdString()) || !testarSenha(senha.toStdString()))
   {
       QMessageBox msgBox;
       msgBox.setWindowTitle("Erro na conexao");
       msgBox.setText("Valor invalido de servidor ("+IP+") e/ou login ("+login+")");
       msgBox.exec();
       return;
   }

 // Depois faz a conexao com servidor

   if (!sock.accepting())
  /* {
       sock.close();
       QMessageBox msgBox;
       msgBox.setWindowTitle("Erro na conexao");
       msgBox.setText("Nao eh foi possivel conectar o servidor pois o socket não está aberto");
       msgBox.exec();
       return;
   }*/

   if((sock.connect(IP.toStdString(),PORTA_WHATSPROG)!= mysocket_status::SOCK_OK ))
   {
       sock.close();
       QMessageBox msgBox;
       msgBox.setWindowTitle("Erro na conexao");
       msgBox.setText("Nao eh foi possivel conectar o servidor ("+IP+") na porta ("+PORTA_WHATSPROG+")");
       msgBox.exec();
       return;
   }
    if (novoUsuario)
    {
        emit signIniciaThread();
    }
}

/// Exibe um pop-up com mensagem de erro
void WhatsProgMain::slotExibirErroMensagem(string S)
{
  QMessageBox::warning(this, "WhatsProg - Erro", QString::fromStdString(S));
}

void WhatsProgMain::on_actionNovo_usuario_triggered()
{
  // Exibe a janela de login para novo usuario (true)
  emit signLogin(true);
}

void WhatsProgMain::on_actionUsuario_existente_triggered()
{
  // Exibe a janela de login para usuario existente (false)
  emit signLogin(false);
}

/// Coloca a interface em modo desconectado
/// Desconecta o socket, limpa o servidor e usuario atuais,
/// limpa todas as conversas, redesenha todas as janelas
void WhatsProgMain::on_actionDesconectar_triggered()
{
  // Falta fazer

  // Redesenha todas as janelas

   ui->tableConversas->setEnabled(true);
   ui->tableMensagens->setEnabled(true);
   ui->statusBar->setEnabled(true);

  slotExibirConversas();
  slotExibirMensagens();
  atualizaEstadoConexao();
}

void WhatsProgMain::on_actionSair_triggered()
{
  QCoreApplication::quit();
}

void WhatsProgMain::on_actionNova_conversa_triggered()
{
  emit signShowNovaConversa();
}

void WhatsProgMain::on_actionRemover_conversa_triggered()
{

  // Sinaliza que houve alteracao na janela de Conversas
  slotExibirConversas();
  // Sinaliza que houve alteracao na janela de Mensagens
  slotExibirMensagens();
}

void WhatsProgMain::on_actionApagar_mensagens_triggered()
{
  // Falta fazer

  // Sinaliza que houve alteracao no numero de msgs de uma conversa
  slotExibirConversas();
  // Sinaliza que houve alteracao na janela de Mensagens
  slotExibirMensagens();
}

void WhatsProgMain::on_tableConversas_activated(const QModelIndex &index)
{
  on_tableConversas_clicked(index);
}

void WhatsProgMain::on_tableConversas_clicked(const QModelIndex &index)
{

  // Sinaliza que houve alteracao na conversa selecionada
  slotExibirConversas();
  // Sinaliza que houve alteracao na janela de Mensagens
  slotExibirMensagens();
}

void WhatsProgMain::on_lineEditMensagem_returnPressed()
{
  // Falta fazer

  // Sinaliza que houve alteracao no numero de msgs de uma conversa
  slotExibirConversas();
  // Sinaliza que houve alteracao na janela de Mensagens
  slotExibirMensagens();
}
