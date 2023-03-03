#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "whatsprog_dados_servidorFAKE.h"

using namespace std;

/// O flag que indica que o software deve encerrar todas as threads
extern bool fim;

/// Funcao auxiliar que imprime um comando tratado pelo servidor
void imprimeComando(bool recebido, const string& user, ComandoWhatsProg cmd,
                    int id, const string& user2)
{
    cout << "CMD ";
    if (recebido) cout << "REC DE ";
    else cout << "ENV P/ ";
    cout << user << ": " << nome_cmd(cmd);
    if (id > 0) cout << ',' << id;
    if (user2.size() > 0) cout << ',' << user2;
    cout << endl;
}

/// Funcao auxiliar que imprime um comando enviado pelo servidor
void imprimeComandoEnviado(const string& user, ComandoWhatsProg cmd,
                           int id=-1, const string& user2="")
{
    imprimeComando(false, user, cmd, id, user2);
}

/// Funcao auxiliar que imprime um comando recebido pelo servidor
void imprimeComandoRecebido(const string& user, ComandoWhatsProg cmd,
                            int id=-1, const string& user2="")
{
    imprimeComando(true, user, cmd, id, user2);
}

/// Funcoes auxiliares para impressao
ostream& operator<<(ostream& O, const Mensagem& M)
{
    O << M.getId() << ';' << nome_status(M.getStatus()) << ';'
      << M.getRemetente() << ';' << M.getDestinatario() << ';'
      << M.getTexto();
    return O;
}

ostream& operator<<(ostream& O, const Usuario& U)
{
    O << U.getLogin() << ';' << U.getLastId();
    return O;
}

/// CLASSE USUARIO

/// Construtor default
Usuario::Usuario(): login(""), senha(""), s(), last_id(0) {}

/// Funcao de consulta ao valor para login
const string& Usuario::getLogin() const
{
    return login;
}

/// Fixa login e senha do usuario
/// Retorna true se OK; false em caso de erro
bool Usuario::setUsuario(const string& L, const string& S)
{
    if (!testarNomeUsuario(L) || !testarSenha(S))
    {
        return false;
    }
    login = L;
    senha = S;
    return true;
}

/// Valida uma senha, comparando com a senha armazenada
bool Usuario::validarSenha(const string& S) const
{
    return (S == senha);
}

/// Funcao de acesso ao socket do usuario
const tcp_mysocket& Usuario::getSocket() const
{
    return s;
}

/// Alteracao do socket de um usuario
void Usuario::swapSocket(tcp_mysocket& S)
{
    s.swap(S);
}

/// Consulta do estado do socket
bool Usuario::connected() const
{
    return s.connected();
}

bool Usuario::closed() const
{
    return s.closed();
}

/// Funcoes de envio de dados via socket
mysocket_status Usuario::read_int(int32_t& num, long milisec) const
{
    return s.read_int(num,milisec);
}

mysocket_status Usuario::write_int(int32_t num) const
{
    return s.write_int(num);
}

mysocket_status Usuario::read_string(string& msg, long milisec) const
{
    return s.read_string(msg,milisec);
}

mysocket_status Usuario::write_string(const string& msg) const
{
    return s.write_string(msg);
}

/// Fechamento do socket
void Usuario::close()
{
    s.close();
}

/// Consulta da ultima ID do usuario
int32_t Usuario::getLastId() const
{
    return last_id;
}

/// Alteracao da ultima ID do usuario
bool Usuario::setLastId(int32_t ID)
{
    if (ID<=0 || ID<=last_id)
    {
        return false;
    }
    last_id = ID;
    return true;
}

/// Reinicializa a ID do usuario
void Usuario::resetId()
{
    last_id=0;
}

/// Teste de igualdade com uma string (testa se a string eh igual ao login)
bool Usuario::operator==(const string& L) const
{
    return login==L;
}

/// CLASSE WHATSPROGDADOSSERVIDOR

/// Funcoes de acesso aas funcionalidades basicas dos sockets
mysocket_status WhatsProgDadosServidor::listen(const char *port, int nconex)
{
    return c.listen(port,nconex);
}

/// Fecha os sockets de conexao e de todos os usuarios conectados
void WhatsProgDadosServidor::closeSockets()
{
    c.close();
    /// ARRUMAR //ADAPTADO PARA O SERVIDOR REAL COM MUITOS USUARIOS ARRUMAR
    for(iDest = user.begin(); iDest != user.end(); iDest++)
    {
        if ((*iDest).connected()) (*iDest).close();
    }
}

/* **************************************************************************************
ATENCAO: a parte a seguir da implementacao do servidor FAKE ***NAO*** pode ser adaptada
para o servidor real, a nao ser que seja feita uma analise cuidadosa.
************************************************************************************** */
/// Envia uma mensagem "i" que esteja no buffer com status MSG_RECEBIDA
/// e cujo destinatario seja o usuario conectado (caso de uso S.3)
/// Apos o envio, altera o status da msg enviada para MSG_ENTREGUE
/// Em seguida, simula o envio da confirmacao de entrega e remove do buffer
/// No servidor real deveria ser:
/// void WhatsProgDadosServidor::enviarRecebidas(iterMensagem iMsg, iterUsuario iDest)
void WhatsProgDadosServidor::enviarMensagem(std::vector<Mensagem>::iterator iMsg, std::vector<Usuario>::iterator iDest)
{
    try
    {
        // Testa os parametros
        ///TESTE PARA FAZER DEPOIS
        if (iMsg==bufferDeMensagens.end() || iDest == user.end() || !iDest->connected()) throw 1;
        if (iMsg->getStatus() !=  MsgStatus::MSG_RECEBIDA ||
            iMsg->getDestinatario() != iDest->getLogin()) throw 1;

        // Envia a mensagem pelo socket
        if (iDest->write_int(CMD_NOVA_MSG) != mysocket_status::SOCK_OK) throw 2;
        if (iDest->write_int(iMsg->getId()) != mysocket_status::SOCK_OK) throw 3;
        if (iDest->write_string(iMsg->getRemetente()) != mysocket_status::SOCK_OK) throw 4;
        if (iDest->write_string(iMsg->getTexto()) != mysocket_status::SOCK_OK) throw 5;

        // Mensagem enviada
        imprimeComandoEnviado(iDest->getLogin(), CMD_NOVA_MSG,
                              iMsg->getId(), iMsg->getRemetente());

        iMsg->setStatus(MsgStatus::MSG_ENTREGUE);


        // Procura o usuario remetente

        // O OPERADOR == USADO NO FIND ESTÁ SOBRECARREGADO PARA USUARIO, ENTÃO TESTA APENAS O LOGIN
        std::vector<Usuario>::iterator remetente = find(user.begin(), user.end(), iMsg->getRemetente());
        /* No servidor FAKE soh compara com os 2 nomes simulados */
        ///FAZER TESTE SE A PESSOA EXISTE throw 6
        if(remetente==user.end()) throw 6;
        // Remetente existe. Testa se estah conectado
        if (remetente->connected())
        {
            enviarConfirmacao(iMsg, remetente);
        }

    }
    catch (int erro)
    {
        if (erro>=2 && erro<=5)
        {
            // Desconecta o destinatario se houve erro no envio pelo socket
            iDest->close();
        }
        cerr << "Erro " << erro << " no envio da mensagem para destinatario "
             << iDest->getLogin() << endl;
    }
}

/* **************************************************************************************
ATENCAO: a parte a seguir da implementacao do servidor FAKE ***NAO*** pode ser adaptada
para o servidor real, a nao ser que seja feita uma analise cuidadosa.
************************************************************************************** */
/// Envia uma confirmacao de entrega de mensagem "i"
/// que esteja no buffer com status MSG_ENTREGUE
/// e cujo remetente seja o usuario conectado (caso de uso S.4)
/// Apos o envio da confirmacao, remove a msg do buffer
/// No servidor real deveria ser:
/// void WhatsProgDadosServidor::enviarConfirmacao(iterMensagem iMsg, iterUsuario iRemet)
void WhatsProgDadosServidor::enviarConfirmacao(std::vector<Mensagem>::iterator iMsg, std::vector<Usuario>::iterator iRemet)
{
    try
    {
        // Testa os parametros
        if (iMsg==bufferDeMensagens.end() || iRemet == user.end() || !iRemet->connected()) throw 1;
        if (iMsg->getStatus() !=  MsgStatus::MSG_ENTREGUE ||
                iMsg->getRemetente() != iRemet->getLogin()) throw 1;

        // Envia a confirmacao pelo socket
        if (iRemet->write_int(CMD_MSG_ENTREGUE) != mysocket_status::SOCK_OK) throw 2;
        if (iRemet->write_int(iMsg->getId()) != mysocket_status::SOCK_OK) throw 3;

        // Confirmacao enviada
        imprimeComandoEnviado(iRemet->getLogin(), CMD_MSG_ENTREGUE,
                              iMsg->getId(), "");

        std::vector<Mensagem>::iterator aux;

        for(aux = bufferDeMensagens.begin(); aux != bufferDeMensagens.end(); aux++)
        {
            if(iMsg->getId() == aux->getId()) bufferDeMensagens.erase(aux);
        }
    }
    catch (int erro)
    {
        if (erro>=2 && erro<=3)
        {
            // Desconecta o remetente se houve erro no envio pelo socket
            iDest->close();
        }
        cerr << "Erro " << erro << " no envio de confirmacao de entrega para remetente "
             << iDest->getLogin() << endl;
    }
}

/* **************************************************************************************
ATENCAO: a parte a seguir da implementacao do servidor FAKE pode ser parcialmente adaptada
para o servidor real, mas requer uma analise muito cuidadosa.
************************************************************************************** */
/// Funcao que efetivamente desempenha as tarefas do servidor
int WhatsProgDadosServidor::main_thread()
{
    // A fila para select (esperar dados em varios sockets)
    mysocket_queue f;

    // O status de retorno das funcoes do socket
    mysocket_status iResult;

    // O comando recebido/enviado
    int32_t cmd;

    // Eventuais parametros de comandos lidos do socket
    int32_t id;
    string destinatario;
    string texto;

    // Mensagem recebida/enviada
    Mensagem M;

    while (!fim)
    {
        try // Erros graves: catch encerra o servidor
        {
            // Se socket de conexoes nao estah aceitando conexoes, encerra o servidor
            if (!c.accepting()) throw 1; // Erro grave: encerra o servidor

            // Inclui na fila de sockets para o select todos os sockets que eu
            // quero monitorar para ver se houve chegada de dados
            f.clear();
            f.include(c);

            // Soh tem um usuario neste servidor fake...
            // No servidor real, teria que percorrer a lista de usuarios e incluir
            // todos os que estiverem conectados
            for(iDest = user.begin(); iDest != user.end(); iDest++)
            {
                if(iDest->connected()) f.include(iDest->getSocket());
            }

            // Espera que chegue algum dado em qualquer dos sockets da fila
            iResult = f.wait_read(TIMEOUT_WHATSPROG*1000);

            switch (iResult) // resultado do wait_read
            {
            case mysocket_status::SOCK_ERROR: // resultado do wait_read
            default:
                // Erro no select, encerra o servidor
                throw 2; // Erro grave: encerra o servidor
                break;
            case mysocket_status::SOCK_TIMEOUT:
            case mysocket_status::SOCK_OK: // resultado do wait_read
                // Houve atividade em algum socket da fila
                // Testa em qual socket houve atividade.

                try // Erros nos clientes: catch fecha a conexao com esse cliente
                {
                    // Primeiro, testa os sockets dos clientes
                    // Soh tem um usuario neste servidor fake...
                    // No servidor real, teria que percorrer a lista de usuarios e testar
                    // cada um dos sockets de usuario

                    for(iDest = user.begin(); iDest != user.end(); iDest++)
                    {

                        if(!fim && iDest->connected() && f.had_activity(iDest->getSocket()))
                        {
                            // Leh o comando recebido do cliente

                            iResult = iDest->read_int(cmd);
                            // Pode ser mysocket_status::SOCK_OK, mysocket_status::SOCK_TIMEOUT,
                            // mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
                            // Nao deve ser mysocket_status::SOCK_TIMEOUT porque a funcao read_int
                            // nao foi chamada com tempo maximo
                            if (iResult != mysocket_status::SOCK_OK) throw 1;

                            // Executa o comando lido
                            switch(cmd)
                            {
                            case CMD_NEW_USER:
                            case CMD_LOGIN_USER:
                            case CMD_LOGIN_OK:
                            case CMD_LOGIN_INVALIDO:
                            case CMD_MSG_INVALIDA:
                            case CMD_MSG_RECEBIDA:
                            case CMD_MSG_ENTREGUE:
                            default:
                                // Comando invalido
                                throw 2;
                                break;
                            case CMD_NOVA_MSG:
                            {
                                // Receber a msg
                                iResult = iDest->read_int(id, TIMEOUT_WHATSPROG*1000);
                                if (iResult != mysocket_status::SOCK_OK) throw 3;
                                iResult = iDest->read_string(destinatario, TIMEOUT_WHATSPROG*1000);
                                if (iResult != mysocket_status::SOCK_OK) throw 4;
                                iResult = iDest->read_string(texto, TIMEOUT_WHATSPROG*1000);
                                if (iResult != mysocket_status::SOCK_OK) throw 5;

                                // Pedido de nova mensagem
                                imprimeComandoRecebido(iDest->getLogin(), CMD_NOVA_MSG, id, destinatario);

                                // Preenche o status e remetente da mensagem recebida
                                if (!M.setStatus(MsgStatus::MSG_RECEBIDA) ||
                                        !M.setRemetente(iDest->getLogin())) throw 6;

                                // Testa se a id da msg estah correta
                                if (!M.setId(id) || id <= iDest->getLastId()) throw 7;

                                // Testa se o texto da msg estah correto
                                if (!M.setTexto(texto)) throw 8;

                                // Procura se o destinatario eh um usuario cadastrado
                                // Neste servidor fake, nao hah lista de usuarios cadastrados
                                // Os unicos outros usuarios cadastrados sao "userfake1" e "userfake2"

                                std::vector<Usuario>::iterator destinatarioTeste = find(user.begin(), user.end(), destinatario);
                                // Testa se o destinatario eh valido e eh um usuario cadastrado

                                if (!M.setDestinatario(destinatario) || destinatarioTeste==user.end()) throw 9;

                                // Mensagem valida
                                // Insere a mensagem no buffer
                                // Este servidor fake nao tem um buffer de verdade
                                // Apenas guarda, para simulacao, a ultima msg recebida
                                // (do usuario para userfake1 e para userfake2)
                                // No servidor real, a mensagem teria que ser inserida (push_back)
                                // na lista de mensagens
                                bufferDeMensagens.push_back(M);

                                // Atualiza a ultima ID recebida
                                iDest->setLastId(id);

                                // Envia a confirmacao de recebimento
                                if (iDest->write_int(CMD_MSG_RECEBIDA) != mysocket_status::SOCK_OK) throw 10;
                                if (iDest->write_int(id) != mysocket_status::SOCK_OK) throw 11;

                                // Confirmacao de recebimento enviada
                                imprimeComandoEnviado(iDest->getLogin(), CMD_MSG_RECEBIDA, id);

                                // Testa se o destinatario estah conectado
                                if(!iDest->connected())
                                {
                                    iMsg = bufferDeMensagens.end();
                                    iMsg--;
                                    enviarMensagem(iMsg, iDest);

                                    iMsg->setStatus(MsgStatus::MSG_ENTREGUE);
                                }

                                /* Fim da parte que ***NAO*** pode ser adaptada para o servidor real ***************** */
                                break; // Fim do case CMD_NOVA_MSG
                            }
                            case CMD_LOGOUT_USER:
                                imprimeComandoRecebido(iDest->getLogin(), CMD_LOGOUT_USER);
                                iDest->close();
                                break; // Fim do case CMD_LOGOUT_USER
                            } // Fim do switch(cmd)
                        } // Fim do if (had_activity) no socket do cliente
                    } // FIM FOR QUE PERCORRE A LISTA DE USUÁRIOS
                } // Fim do try para erros nos clientes
                catch (int erro) // Erros na leitura do socket de algum cliente
                {
                    if (erro>=6 && erro<=9)
                    {
                        // Comunicacao OK, mensagem invalida
                        // Envia comando informando msg mal formatada
                        iDest->write_int(CMD_MSG_INVALIDA);
                        iDest->write_int(id);

                        // Comando de mensagem invalida enviado
                        imprimeComandoEnviado(iDest->getLogin(), CMD_MSG_INVALIDA, id, destinatario);
                    }
                    else // erro 1-6 e 10-11
                    {
                        // Erro na comunicacao
                        // Fecha o socket
                        iDest->close();

                        // Informa o erro imprevisto
                        cerr << "Erro " << erro << " na leitura de nova mensagem do cliente "
                             << iDest->getLogin() << endl;
                    }
                }

                // Depois de testar os sockets dos clientes,
                // testa se houve atividade no socket de conexao
                if (f.had_activity(c))
                {
                    tcp_mysocket t;
                    string login, senha;

                    // Aceita provisoriamente a nova conexao
                    if (c.accept(t) != mysocket_status::SOCK_OK) throw 3; // Erro grave: encerra o servidor

                    try // Erros na conexao de cliente: fecha socket temporario ou desconecta novo cliente
                    {
                        // Leh o comando
                        iResult = t.read_int(cmd, TIMEOUT_LOGIN_WHATSPROG*1000);
                        if (iResult != mysocket_status::SOCK_OK) throw 1;

                        // Testa o comando
                        if (cmd!=CMD_LOGIN_USER && cmd!=CMD_NEW_USER) throw 2;

                        // Leh o parametro com o login do usuario que deseja se conectar
                        iResult = t.read_string(login, TIMEOUT_LOGIN_WHATSPROG*1000);
                        if (iResult != mysocket_status::SOCK_OK) throw 3;

                        // Leh o parametro com a senha do usuario que deseja se conectar
                        iResult = t.read_string(senha, TIMEOUT_LOGIN_WHATSPROG*1000);
                        if (iResult != mysocket_status::SOCK_OK) throw 4;

                        // Nova tentativa de conexao recebida
                        imprimeComandoRecebido(login, (ComandoWhatsProg)cmd);

                        // Testa o login e senha
                        if (!testarNomeUsuario(login) || !testarSenha(senha)) throw 5;

                        // Verifica se jah existe um usuario cadastrado com esse login
                        // No servidor real, deveria ser feita uma busca na lista de usuarios
                        // Aqui, basta comparar com os nomes "userfake1" ou "userfake2"
                        // nos testes a seguir sobre se o usuario eh adequado ou nao

                        // Testa se o usuario eh adequado
                        /* **************************************************************************************
                        ATENCAO: a parte a seguir da implementacao do servidor FAKE pode ser parcialmente adaptada
                        para o servidor real, mas requer uma analise cuidadosa.
                        ************************************************************************************** */
                        if (cmd == CMD_NEW_USER)
                        {

                            for(iDest = user.begin(); iDest != user.end(); iDest++)
                            {
                                if (login == iDest->getLogin()) throw 6; // Erro se jah existir
                            }
                            // Este servidor fake soh pode ter um usuario cadastrado
                            // Soh vai aceitar o novo usuario se ninguem estiver conectado
                            // Nao eh um erro no servidor real: pode se conectar um novo se
                            // jah houver um ou varios conectados

                            // Insere novo usuario

                            Usuario aux;
                            if(aux.setUsuario(login,senha))
                            {
                                aux.swapSocket(t);
                                user.push_back(aux);
                            }


                        }
                        else  // else cmd == CMD_NEW_USER; implica cmd eh CMD_LOGIN_USER
                        {
                            iDest = find(user.begin(), user.end(), login);

                            if (iDest == user.end()) throw 8; // Erro se nao existir


                            // Testa se a senha confere
                            if (!iDest->validarSenha(senha)) throw 9; // Senha nao confere
                            // Testa se o cliente jah estah conectado

                            if (iDest->connected()) throw 10; // Usuario jah conectado

                            // Associa o socket que se conectou a um usuario cadastrado
                            iDest->swapSocket(t);

                        } // fim cmd eh CMD_LOGIN_USER
                        /* Fim da parte que pode ser PARCIALMENTE adaptada para o servidor real ************** */
                        iDest = find(user.begin(), user.end(), login);
                        // Envia a confirmacao de conexao para o novo cliente

                        if(iDest->write_int(CMD_LOGIN_OK) != mysocket_status::SOCK_OK) throw 11;

                        imprimeComandoEnviado(iDest->getLogin(), CMD_LOGIN_OK);


                        // Se for um cliente antigo, envia para o cliente que se reconectou:
                        // a) as mensagens enviadas para ele que estao no buffer
                        // b) as confirmacoes de visualizacao para ele que estao no buffer
                        if (cmd==CMD_LOGIN_USER)
                        {
                            /* **************************************************************************************
                            ATENCAO: a parte a seguir da implementacao do servidor FAKE ***NAO*** pode ser adaptada
                            para o servidor real, a nao ser que seja feita uma analise muito cuidadosa.
                            ************************************************************************************** */
                            // mensagens enviadas para ele que estao no buffer
                            //
                            // No servidor real, deveria ser feita uma busca para localizar todas as
                            // mensagens enviadas para ele que estao no buffer como recebidas
                            // No servidor FAKE, basta verificar as eventuais 2 msgs que estao em paraUsuario[i]

                            for(iMsg = bufferDeMensagens.begin(); iMsg != bufferDeMensagens.end(); iMsg++)
                            {
                                if(iMsg->getDestinatario() == iDest->getLogin() && iMsg->getStatus() ==  MsgStatus::MSG_RECEBIDA)
                                {
                                    enviarMensagem(iMsg, iDest);
                                }
                            }


                            // as confirmacoes de entrega para ele que estao no buffer
                            //
                            // No servidor real, deveria ser feita uma busca para localizar todas as
                            // mensagens enviadas por ele que estao no buffer como entregues
                            // No servidor FAKE, basta verificar as eventuais 2 msgs que estao em doUsuario[i]
                            for(iMsg = bufferDeMensagens.begin(); iMsg != bufferDeMensagens.end(); iMsg++)
                            {
                                if(iMsg->getRemetente() == iDest->getLogin() && iMsg->getStatus() ==  MsgStatus::MSG_ENTREGUE)
                                {
                                    enviarConfirmacao(iMsg, iDest);
                                }
                            }


                        } // fim do if (cmd==CMD_LOGIN_USER)
                    } // Fim do try para erros na comunicacao com novo cliente
                    catch (int erro) // Erros na conexao do novo cliente
                    {

                        if (erro>=5 && erro<=10)
                        {
                            // Comunicacao com socket temporario OK, login invalido
                            // Envia comando informando login invalido
                            t.write_int(CMD_LOGIN_INVALIDO);

                            // Comando login invalido enviado
                            imprimeComandoEnviado(login, CMD_LOGIN_INVALIDO);

                            // Fecha o socket temporario
                            t.close();
                        }
                        else // erro 1-4 ou 11
                        {
                            // Erro na comunicacao
                            // Fecha o socket
                            if (erro==11)
                            {

                                // Erro na comunicacao com socket do novo cliente
                                iDest->close();
                            }
                            else  // erro 1-4
                            {
                                // Erro na comunicacao com socket temporario
                                t.close();
                            }
                            // Informa erro nao previsto
                            cerr << "Erro " << erro << " na conexao de novo cliente" << endl;
                        }
                    } // fim catch
                } // fim if (had_activity) no socket de conexoes
                break; // fim do case mysocket_status::SOCK_OK - resultado do wait_read
            } // fim do switch (iResult) - resultado do wait_read

        } // Fim do try para erros criticos no servidor
        catch (int erro) // Erros criticos no servidor
        {
            cerr << "Erro " << erro << " no servidor. Encerrando\n";
            fim = true;
        }

    } // Fim do while (!fim), laco principal da thread

    cout << "\nServidor encerrado.\n";

    return 0;
}
