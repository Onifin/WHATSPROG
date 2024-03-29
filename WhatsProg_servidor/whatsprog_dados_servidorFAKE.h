#ifndef WHATSPROG_DADOS_SERVIDOR_H
#define WHATSPROG_DADOS_SERVIDOR_H

#include <string>
#include <list>
#include <vector>
#include "../MySocket/mysocket.h"
#include "whatsprog_dados.h"

/// Os usuarios cadastrados no servidor
class Usuario
{
private:
  // Identificacao do usuario
  std::string login;
  std::string senha;

  // Socket de comunicacao (idle se nao conectado)
  tcp_mysocket s;

  // Ultima id de mensagem recebida
  int32_t last_id;

public:
  // Construtor default
  Usuario();

  // Funcao de consulta ao valor para login
  const std::string& getLogin() const;

  // Funcao de fixacao de valor para login e senha
  // Retorna true em caso de sucesso, false se erro
  bool setUsuario(const std::string& L, const std::string& S);

  // Valida uma senha, comparando com a senha armazenada
  bool validarSenha(const std::string& S) const;

  // Funcao de acesso ao socket do usuario
  const tcp_mysocket& getSocket() const;

  // Alteracao do socket de um usuario
  void swapSocket(tcp_mysocket& S);

  // Consulta do estado do socket
  bool connected() const;
  bool closed() const;

  // Funcoes de envio de dados via socket
  mysocket_status read_int(int32_t& num, long milisec=-1) const;
  mysocket_status write_int(int32_t num) const;
  mysocket_status read_string(std::string& msg, long milisec=-1) const;
  mysocket_status write_string(const std::string& msg) const;

  // Fechamento do socket
  void close();

  // Consulta da ultima ID do usuario
  int32_t getLastId() const;

  // Alteracao da ultima ID do usuario
  bool setLastId(int32_t ID);

  // Reinicializa a ID do usuario
  void resetId();

  // Teste de igualdade com uma std::string (testa se a std::string eh igual ao login)
  bool operator==(const std::string& L) const;
};

class WhatsProgDadosServidor
{
private:
  // O socket de conexoes
  tcp_mysocket_server c;

  /* **************************************************************************************
  ATENCAO: a parte a seguir da implementacao do servidor FAKE ***NAO*** pode ser adaptada
  para o servidor real.
  ************************************************************************************** */
  // O usuario
  // No programa real, seriam varios usuarios
  std::vector<Usuario> user;

  // Mensagens pendentes
  // Este servidor fake nao tem um buffer de verdade
  // Apenas guarda, para simulacao, a ultima msg recebida
  // (do usuario para userfake1 e para userfake2)
  std::vector<Mensagem> bufferDeMensagens;

  ///ITERADORES DE MENSAGEM E USUARIO
  std::vector<Mensagem>::iterator iMsg;
  std::vector<Usuario>::iterator iDest;


  // e a ultima msg enviada (gerada aleatoriamente)
  // (de userfake1 e userfake2 para usuario)


  // Envia uma mensagem "i" que esteja no buffer com status MSG_RECEBIDA
  // e cujo destinatario seja o usuario conectado (caso de uso S.3)
  // Apos o envio, altera o status da msg enviada para MSG_ENTREGUE
  // Em seguida, simula o envio da confirmacao de entrega e remove do buffer
  // No servidor real deveria ser:
  // void WhatsProgDadosServidor::enviarMensagem(iterMensagem iMsg, iterUsuario iDest)
  //RECEBIA UM int i;
  void enviarMensagem(std::vector<Mensagem>::iterator iMsg, std::vector<Usuario>::iterator iDest);

  // Envia uma confirmacao de entrega da mensagem "i"
  // que esteja no buffer com status MSG_ENTREGUE
  // e cujo remetente seja o usuario conectado (caso de uso S.4)
  // Apos o envio da confirmacao, remove a msg do buffer
  // No servidor real deveria ser:
  // void WhatsProgDadosServidor::enviarConfirmacao(iterMensagem iMsg, iterUsuario iRemet)
  void enviarConfirmacao(std::vector<Mensagem>::iterator iMsg, std::vector<Usuario>::iterator iDest);
  /* Fim da parte que ***NAO*** pode ser adaptada para o servidor real ***************** */

public:
  /// Funcoes de acesso aas funcionalidades basicas dos sockets
  mysocket_status listen(const char *port, int nconex=1);

  /// Fecha os sockets de conexao e de todos os usuarios conectados
  void closeSockets();

  /// Thread que efetivamente desempenha as tarefas do servidor
  int main_thread();
};

#endif //WHATSPROG_DADOS_SERVIDOR_H
