/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         02/2025
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.1
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "gl_canvas2d.h"

#include "Bmp.h"
#include "GerenciadorCamadas.h"
#include "Interface.h"
#include <string>

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1280, screenHeight = 720;


Bmp *img1;
Interface *interface;
gerenciadorCamadas *gCamadas;
int opcao  = 50;//variavel global para selecao do que sera exibido na canvas.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
int cont = 0;

void carregarImagemNaCamada(char *nome_arquivo){
    img1 = new Bmp(nome_arquivo);
    img1->convertBGRtoRGB();
    gCamadas->carregaCamada(img1->getImage(), img1->getWidth(), img1->getHeight());
    gCamadas->addBotaoCamada(gCamadas->getQntCamadas() - 1, screenWidth, screenHeight, interface->getBordaMenuLateralX());
}

void render()
{
    int pos;
    interface->render(screenWidth, screenHeight);

    gCamadas->render();
    Sleep(10); //nao eh controle de FPS. Somente um limitador de FPS.
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   printf("\nTecla: %d" , key);
   if( key < 200 )
   {
      opcao = key;
   }

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    if(button == 0 && state == 1){
        if(interface->getAbertoSubmenuArquivos()){
            if(interface->verificaClickSubmenu(interface->getSubmenuArquivos(), mouseX, mouseY) == 0){
                interface->setAbertoSubmenuArquivos(0, 0, 0);
            }
            else{
                char nome_arquivo[512]; // Buffer grande o suficiente
                std::string nomeArquivoRetornado = (interface->verificaArquivoParaAbrir(mouseX, mouseY).c_str());
                sprintf(nome_arquivo, ".\\Trab1GabrielBaggio\\images\\%s", nomeArquivoRetornado.c_str());
                carregarImagemNaCamada(nome_arquivo);
                interface->setAbertoSubmenuArquivos(0, 0, 0);

            }
        }
        else if(interface->verificaClickBotao(interface->getBotaoAddImagem(), mouseX, mouseY)){
            interface->setAbertoSubmenuArquivos(1, mouseX, mouseY);
        }
        gCamadas->setPintando(0);
    }
    else if(button == 0 && state == 0){
        if(gCamadas->verificaMouseCamada(mouseX, mouseY)){
            gCamadas->setPintando(1);
        }
    }

    if(gCamadas->getPintando() && gCamadas->verificaMouseCamada(mouseX, mouseY)){
        printf("Estou pintando!");
    }
    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

}

int main(void)
{
    interface = new Interface(screenWidth, screenHeight);
    gCamadas = new gerenciadorCamadas(interface->getGrossuraBordasLaterais(), interface->getBordaMenuLateralX(), screenHeight);


    CV::init(&screenWidth, &screenHeight, "Gabriel Baggio Image Manipulation Program (GBIMP)");
    CV::run();
}
