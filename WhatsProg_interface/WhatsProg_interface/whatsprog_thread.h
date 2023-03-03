#ifndef WHATSPROG_THREAD_H
#define WHATSPROG_THREAD_H

#include <qobject.h>
#include <thread>
#include "whatsprog_dados_cliente.h"
#include "mysocket.h"


extern WhatsProgDadosCliente DC;
extern tcp_mysocket sock;


class WhatsProg_Thread :  public QObject
{
  Q_OBJECT


public slots:

    /// Iniciar a thread
    void slotIniciaThread(void);

    /// Terminar a thread
    void slotEncerraThread(void);

signals:

    ///Após criar nova conversa,reexibe interface
    void signExibeNovaMensagem();

    ///Após receber nova mensagem, reexibe interface
    void signExibeNovaConversa();

    ///Após receber confirmação de mensagem recebida ou entregue da conversa que está aberta e
    /// sendo visualizada,
    void signReexibeMensRecebida();

    ///reexibe interface e exibe mensagem de erro, reexibe interface e exibe mensagem de erro
    void signReexibeErro(const std::string S);

    ///Após erro no salvamento periódico dos dados, exibe mensagem de erro
    void signErroSalva(const std::string S);

    ///Quando a thread for encerrada, mudar interface para modo cliente desconectado
    void signEncerrar(void);

private:

    std::thread thr;
    void main_thread();
    friend void main_thread(WhatsProg_Thread* E);

public:
    explicit  WhatsProg_Thread(QObject *parent = nullptr);

};

#endif // WHATSPROG_THREAD_H
