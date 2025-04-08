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
        else if(gCamadas->verificaBotaoHide(mouseX, mouseY)){

        }
        else if(gCamadas->verificaBotaoAtiva(mouseX, mouseY)){

        }
        else if(interface->verificaClickBotao(interface->getBotaoClicar(), mouseX, mouseY)){
            interface->alteraBotaoSelecionado(0);
        }
        else if(interface->verificaClickBotao(interface->getBotaoPincel(), mouseX, mouseY)){
            interface->alteraBotaoSelecionado(1);
        }
        else if(interface->verificaClickBotao(interface->getBotaoSpray(), mouseX, mouseY)){
            interface->alteraBotaoSelecionado(2);
        }
        else if(interface->verificaClickBotao(interface->getBotaoMarcaTexto(), mouseX, mouseY)){
            interface->alteraBotaoSelecionado(3);
        }
        else if(interface->verificaClickBotao(interface->getBotaoBalde(), mouseX, mouseY)){
            interface->alteraBotaoSelecionado(4);
        }
        else if(interface->verificaClickBotao(interface->getBotaoBorracha(), mouseX, mouseY)){
            interface->alteraBotaoSelecionado(5);
        }
        gCamadas->setPintando(0);
        interface->setSegurandoR(0);
        interface->setSegurandoG(0);
        interface->setSegurandoB(0);
        interface->setSegurandoRaio(0);
    }
    else if(button == 0 && state == 0){
        if(gCamadas->verificaMouseCamada(mouseX, mouseY)){
            gCamadas->setPintando(1);
        }
        else if(interface->verificaSegurandoSlider(interface->getSliderR(), mouseX, mouseY)){
            interface->setSegurandoR(1);
        }
        else if(interface->verificaSegurandoSlider(interface->getSliderG(), mouseX, mouseY)){
            interface->setSegurandoG(1);
        }
        else if(interface->verificaSegurandoSlider(interface->getSliderB(), mouseX, mouseY)){
            interface->setSegurandoB(1);
        }
        else if(interface->verificaSegurandoSlider(interface->getSliderRaio(), mouseX, mouseY)){
            interface->setSegurandoRaio(1);
        }
    }

    if(gCamadas->getPintando() && gCamadas->verificaMouseCamada(mouseX, mouseY) && gCamadas->getQntCamadas() > 0){
        if(interface->getBotaoSelecionado() == 1){
            gCamadas->pintarCamada(mouseX, mouseY, interface->getRGBA(), 1, interface->getRaioCor());
        }
        else if(interface->getBotaoSelecionado() == 2){
            gCamadas->pintarCamada(mouseX, mouseY, interface->getRGBA(), 2, interface->getRaioCor());
        }
        else if(interface->getBotaoSelecionado() == 3){
            gCamadas->pintarCamada(mouseX, mouseY, interface->getRGBA(), 3, interface->getRaioCor());
        }
        else if(interface->getBotaoSelecionado() == 4){
            gCamadas->pintarCamada(mouseX, mouseY, interface->getRGBA(), 4, interface->getRaioCor());
        }
        else if(interface->getBotaoSelecionado() == 5){
            gCamadas->pintarCamada(mouseX, mouseY, interface->getRGBA(), 5, interface->getRaioCor());
        }
    }

    if(interface->getSegurandoR()){
        interface->mudaValorSliderR(mouseX);
    }
    else if(interface->getSegurandoG()){
        interface->mudaValorSliderG(mouseX);
    }
    else if(interface->getSegurandoB()){
        interface->mudaValorSliderB(mouseX);
    }
    else if(interface->getSegurandoRaio()){
        interface->mudaValorSliderRaio(mouseX);
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
