#ifndef FUNCOES_H
#define FUNCOES_H

#include <gtk/gtk.h>

gboolean adicionar_widget(gpointer verificador);

/**
 * @brief Destroi todos os widgets filhos de um container.
 * @param widget Widget filho a ser destruído.
 * @param data Dados adicionais (não utilizado).
 */
void destruir_filhos(GtkWidget *widget, gpointer data);

/**
 * @brief Adiciona um botão na lista de itens, representando um item salvo.
 * @param nome_item Nome do item a ser exibido.
 * @param id Identificador do item.
 */
void atualizar_lista(char *nome_item,int id);

/**
 * @brief Conecta os sinais dos botões aos seus callbacks.
 */
void conectar_botoes();

/**
 * @brief Callback do botão de confirmação. Lê os campos, concatena e criptografa os dados.
 */
void adicionar_na_lista();
int confirmar_entrada();

/**
 * @brief Callback para alternar para a aba de notas.
 */
void acao_nota();
void acao_senha();

/**
 * @brief Callback do botão de cancelar. Limpa os campos de entrada.
 */
void cancelar_entrada();

/**
 * @brief Inicializa os ponteiros dos widgets a partir do arquivo Glade.
 */
void get_object_gtk();

/**
 * @brief Separa o nome do item de uma string formatada.
 * @param dados String formatada com delimitadores "|||".
 * @return Ponteiro para o nome do item.
 */

char *separar( char *dados);
char* senha_janela();
void controle_de_fluxo();
#endif