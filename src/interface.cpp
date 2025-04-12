// classe pra gerenciar a maioria dos botoes da interface, assim como os sliders

#include "Interface.h"
#include <string.h>
#include "gl_canvas2d.h"

#define posBotoesClick 9/10
#define larguraBotoesClick 46
#define alturaBotoesClick 30
#define distanciaEntreBotoesClick 5

Interface::Interface(int screenWidth, int screenHeight) // carrega todos os botoes e interface
{
    bordaMenuLateralX = screenWidth * 3 / 4;
    grossuraBordasLateraisNasCamadas = 10;
    inicioMenuLateralX = bordaMenuLateralX + grossuraBordasLateraisNasCamadas;
    tamanhoLadoQuadradosFundo = 10;
    borda1X = grossuraBordasLateraisNasCamadas;
    borda1Y = grossuraBordasLateraisNasCamadas;
    borda2X = bordaMenuLateralX;
    borda2Y = screenHeight - grossuraBordasLateraisNasCamadas;

    submenuArquivos.aberto = 0;
    tamanhoBotaoArquivos = 10;
    qntArquivos = 0;
    carregarNomeArquivos();

    botaoAddImagem.borda1X = inicioMenuLateralX + 5;
    botaoAddImagem.borda1Y = screenHeight * 9.5 / 10;
    botaoAddImagem.borda2X = screenWidth - 5;
    botaoAddImagem.borda2Y = botaoAddImagem.borda1Y + 30;
    botaoAddImagem.tem_borda = 1;

    clicar.borda1X = inicioMenuLateralX + 5;
    clicar.borda1Y = screenHeight * posBotoesClick;
    clicar.borda2X = clicar.borda1X + larguraBotoesClick;
    clicar.borda2Y = clicar.borda1Y + alturaBotoesClick;
    clicar.tem_borda = 1;

    pincel.borda1X = clicar.borda2X + distanciaEntreBotoesClick;
    pincel.borda1Y = screenHeight * posBotoesClick;
    pincel.borda2X = pincel.borda1X + larguraBotoesClick;
    pincel.borda2Y = pincel.borda1Y + alturaBotoesClick;
    pincel.tem_borda = 0;

    spray.borda1X = pincel.borda2X + distanciaEntreBotoesClick;
    spray.borda1Y = screenHeight * posBotoesClick;
    spray.borda2X = spray.borda1X + larguraBotoesClick;
    spray.borda2Y = spray.borda1Y + alturaBotoesClick;
    spray.tem_borda = 0;

    marcaTexto.borda1X = spray.borda2X + distanciaEntreBotoesClick;
    marcaTexto.borda1Y = screenHeight * posBotoesClick;
    marcaTexto.borda2X = marcaTexto.borda1X + larguraBotoesClick;
    marcaTexto.borda2Y = marcaTexto.borda1Y + alturaBotoesClick;
    marcaTexto.tem_borda = 0;

    balde.borda1X = marcaTexto.borda2X + distanciaEntreBotoesClick;
    balde.borda1Y = screenHeight * posBotoesClick;
    balde.borda2X = balde.borda1X + larguraBotoesClick;
    balde.borda2Y = balde.borda1Y + alturaBotoesClick;
    balde.tem_borda = 0;

    borracha.borda1X = balde.borda2X + distanciaEntreBotoesClick;
    borracha.borda1Y = screenHeight * posBotoesClick;
    borracha.borda2X = borracha.borda1X + larguraBotoesClick;
    borracha.borda2Y = borracha.borda1Y + alturaBotoesClick;
    borracha.tem_borda = 0;

    sliderR.inicioX = inicioMenuLateralX + 5;
    sliderR.fimX = balde.borda2X - 10;
    sliderR.Y = screenHeight * 8.5 / 10;
    sliderR.valorMinimo = 0;
    sliderR.valorMaximo = 255;
    sliderR.valorAtual = 255;
    sliderR.segurando = 0;

    sliderG.inicioX = inicioMenuLateralX + 5;
    sliderG.fimX = balde.borda2X - 10;
    sliderG.Y = sliderR.Y - 30;
    sliderG.valorMinimo = 0;
    sliderG.valorMaximo = 255;
    sliderG.valorAtual = 0;
    sliderG.segurando = 0;

    sliderB.inicioX = inicioMenuLateralX + 5;
    sliderB.fimX = balde.borda2X - 10;
    sliderB.Y = sliderG.Y - 30;
    sliderB.valorMinimo = 0;
    sliderB.valorMaximo = 255;
    sliderB.valorAtual = 0;
    sliderB.segurando = 0;

    sliderRaio.inicioX = inicioMenuLateralX + 5;
    sliderRaio.fimX = balde.borda2X - 10;
    sliderRaio.Y = sliderB.Y - 30;
    sliderRaio.valorMinimo = 1;
    sliderRaio.valorMaximo = 50;
    sliderRaio.valorAtual = 10;
    sliderRaio.segurando = 0;

    sliderBrilho.inicioX = inicioMenuLateralX + 5;
    sliderBrilho.fimX = balde.borda2X - 60;
    sliderBrilho.Y = sliderRaio.Y - 35;
    sliderBrilho.valorMinimo = -255;
    sliderBrilho.valorMaximo = 255;
    sliderBrilho.valorAtual = 0;
    sliderBrilho.segurando = 0;

    sliderGama.inicioX = inicioMenuLateralX + 5;
    sliderGama.fimX = balde.borda2X - 60;
    sliderGama.Y = sliderBrilho.Y - 35;
    sliderGama.valorMinimo = 20; // esse valor vai ser dividido por 100
    sliderGama.valorMaximo = 500; // esse valor vai ser dividido por 100
    sliderGama.valorAtual = 100; // esse valor vai ser dividido por 100
    sliderGama.segurando = 0;

    addBrilho.borda1X = sliderBrilho.fimX + 15;
    addBrilho.borda1Y = sliderBrilho.Y;
    addBrilho.borda2X = addBrilho.borda1X + larguraBotoesClick;
    addBrilho.borda2Y = sliderBrilho.Y + alturaBotoesClick;
    addBrilho.tem_borda = 1;

    addGama.borda1X = sliderGama.fimX + 15;
    addGama.borda1Y = sliderGama.Y;
    addGama.borda2X = addGama.borda1X + larguraBotoesClick;
    addGama.borda2Y = sliderGama.Y + alturaBotoesClick;
    addGama.tem_borda = 1;

    fliperVertical.borda1X = sliderRaio.fimX + 15;
    fliperVertical.borda1Y = sliderRaio.Y - 35;
    fliperVertical.borda2X = fliperVertical.borda1X + larguraBotoesClick;
    fliperVertical.borda2Y = fliperVertical.borda1Y + alturaBotoesClick;
    fliperVertical.tem_borda = 1;

    fliperHorizontal.borda1X = sliderRaio.fimX + 15;
    fliperHorizontal.borda1Y = fliperVertical.borda1Y - 35;
    fliperHorizontal.borda2X = fliperHorizontal.borda1X + larguraBotoesClick;
    fliperHorizontal.borda2Y = fliperHorizontal.borda1Y + alturaBotoesClick;
    fliperHorizontal.tem_borda = 1;

    tonsCinza.borda1X = sliderRaio.fimX + 15;
    tonsCinza.borda1Y = fliperHorizontal.borda1Y - 35;
    tonsCinza.borda2X = screenWidth - 5;
    tonsCinza.borda2Y = tonsCinza.borda1Y + alturaBotoesClick;
    tonsCinza.tem_borda = 1;

    save.borda1X = sliderRaio.fimX + 15;
    save.borda1Y = tonsCinza.borda1Y - 18;
    save.borda2X = screenWidth - 5;
    save.borda2Y = save.borda1Y + 13;
    save.tem_borda = 1;

    load.borda1X = sliderRaio.fimX + 15;
    load.borda1Y = save.borda1Y - 18;
    load.borda2X = screenWidth - 5;
    load.borda2Y = load.borda1Y + 13;
    load.tem_borda = 1;

    sliderContraste.inicioX = inicioMenuLateralX + 5;
    sliderContraste.fimX = balde.borda2X - 60;
    sliderContraste.Y = sliderGama.Y - 35;
    sliderContraste.valorMinimo = 0; // esse valor vai ser dividido por 100
    sliderContraste.valorMaximo = 200; // esse valor vai ser dividido por 100
    sliderContraste.valorAtual = 100; // esse valor vai ser dividido por 100
    sliderContraste.segurando = 0;

    addContraste.borda1X = sliderContraste.fimX + 15;
    addContraste.borda1Y = sliderContraste.Y;
    addContraste.borda2X = addContraste.borda1X + larguraBotoesClick;
    addContraste.borda2Y = sliderContraste.Y + alturaBotoesClick;
    addContraste.tem_borda = 1;

    sliderBlur.inicioX = inicioMenuLateralX + 5;
    sliderBlur.fimX = balde.borda2X - 60;
    sliderBlur.Y = sliderContraste.Y - 35;
    sliderBlur.valorMinimo = 1;
    sliderBlur.valorMaximo = 15;
    sliderBlur.valorAtual = 3;
    sliderBlur.segurando = 0;

    addBlur.borda1X = sliderBlur.fimX + 15;
    addBlur.borda1Y = sliderBlur.Y;
    addBlur.borda2X = addBlur.borda1X + larguraBotoesClick;
    addBlur.borda2Y = sliderBlur.Y + alturaBotoesClick;
    addBlur.tem_borda = 1;

    botaoSelecionado = 0;
    raioCor = 10;
    RGBA[0] = 255;
    RGBA[1] = 0;
    RGBA[2] = 0;
    RGBA[3] = 1;
}

void Interface::render(int screenWidth, int screenHeight){ // funcao 'main' da interface, renderiza tudo
    renderFundo();
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(bordaMenuLateralX, 0, bordaMenuLateralX + grossuraBordasLateraisNasCamadas, screenHeight);
    CV::rectFill(0, 0, bordaMenuLateralX, grossuraBordasLateraisNasCamadas);
    CV::rectFill(0, 0, grossuraBordasLateraisNasCamadas, screenHeight);
    CV::rectFill(0, screenHeight - grossuraBordasLateraisNasCamadas, bordaMenuLateralX, screenHeight);
    CV::color(0.5, 0.5, 0.5);
    CV::rectFill(inicioMenuLateralX, 0, screenWidth, screenHeight);
    renderBotao(botaoAddImagem, "Adicionar uma imagem/camada", false);
    renderBotao(clicar, "Clck", false);
    renderBotao(pincel, "Pncl", false);
    renderBotao(spray, "Spry", false);
    renderBotao(marcaTexto, "mcTx", false);
    renderBotao(balde, "Blde", false);
    renderBotao(borracha, "Lmpa", false);
    renderBotao(fliperVertical, "FlpV", false);
    renderBotao(fliperHorizontal, "FlpH", false);
    renderBotao(tonsCinza, "Gray", false);
    renderBotao(addBrilho, nullptr, true); 
    renderBotao(addGama, nullptr, true);  
    renderBotao(addContraste, nullptr, true); 
    renderBotao(addBlur, nullptr, true);
    renderBotao(save, "Save", false);
    renderBotao(load, "Load", false);

    renderSlider(sliderR, "R: ");
    renderSlider(sliderG, "G: ");
    renderSlider(sliderB, "B: ");
    renderSlider(sliderRaio, "Raio: ");
    renderSlider(sliderBrilho, "Brilho: ");
    renderSlider(sliderGama, "Gama: ", true, true);
    renderSlider(sliderContraste, "Contraste: ", true, true);
    renderSlider(sliderBlur, "Desfoque: ");

    renderPreviewCor(screenWidth);

    if(submenuArquivos.aberto){
        renderSubmenuArquivos();
    }
}

int Interface::getBordaMenuLateralX(){
    return bordaMenuLateralX;
}

int Interface::getGrossuraBordasLaterais(){
    return grossuraBordasLateraisNasCamadas;
}

void Interface::renderFundo(){ // renderiza aqueles quadriculados cinzas
    int i, j;
    int linha = 0, coluna;
    for(i = borda1Y; i < borda2Y; i += tamanhoLadoQuadradosFundo){
        coluna = 0;
        for(j = borda1X; j < borda2X; j += tamanhoLadoQuadradosFundo){
            if((linha + coluna)%2==0){
                CV::color(0.8, 0.8, 0.8);
            }
            else{
                CV::color(0.4, 0.4, 0.4);
            }
            CV::rectFill(j, i, j + tamanhoLadoQuadradosFundo, i + tamanhoLadoQuadradosFundo);
            coluna++;
        }
        linha++;
    }
}

void Interface::renderBotao(BOTAO botao, const char* texto, bool isImage){ // funcao generica pra renderizar um botao
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(botao.borda1X, botao.borda1Y, botao.borda2X, botao.borda2Y);

    if(botao.tem_borda){
        CV::color(0.9, 0.9, 0.9);
        CV::rect(botao.borda1X, botao.borda1Y, botao.borda2X, botao.borda2Y);
    }
    
    if (!isImage) {
        CV::color(0.9, 0.9, 0.9);
        CV::text(botao.borda1X + 5, (botao.borda1Y + botao.borda2Y) / 2 - 2, texto);
    } 
    else {
        CV::color(0.9, 0.9, 0.9);
        CV::rectFill(botao.borda1X + 5, (botao.borda1Y + botao.borda2Y) / 2 - 2, 
                    botao.borda2X - 5, (botao.borda1Y + botao.borda2Y) / 2 + 2);
        CV::rectFill((botao.borda1X + botao.borda2X) / 2 - 2, botao.borda1Y + 5, 
                    (botao.borda1X + botao.borda2X) / 2 + 2, botao.borda2Y - 5);
        
    }
}

void Interface::renderSlider(Slider slider, const char* texto, bool mostrarValor, bool porcentagem){ // funcao generica pra renderizar um slider
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(slider.inicioX, slider.Y, slider.fimX + 10, slider.Y + 10);
    CV::color(0.9, 0.9, 0.9);
    
    float ratio = (float)(slider.valorAtual - slider.valorMinimo) / (slider.valorMaximo - slider.valorMinimo);
    int cursorPos = slider.inicioX + (slider.fimX - slider.inicioX) * ratio;
    
    CV::rectFill(cursorPos, slider.Y, cursorPos + 10, slider.Y + 10);
    
    if (texto != nullptr) {
        CV::color(0.9, 0.9, 0.9);
        CV::text(slider.inicioX, slider.Y + 15, texto);
        
        if (mostrarValor) {
            if (porcentagem) {
                char buffer[20];
                sprintf(buffer, "%.1f", slider.valorAtual / 100.0);
                CV::text(slider.fimX - 30, slider.Y + 15, buffer);
            } else {
                CV::text(slider.fimX - 30, slider.Y + 15, std::to_string(slider.valorAtual).c_str());
            }
        }
    }
}

bool Interface::verificaClickBotao(BOTAO botao, int mouseX, int mouseY){ // funcao generica pra verifica click no botao
    if(mouseX > botao.borda1X && mouseX < botao.borda2X && mouseY > botao.borda1Y && mouseY < botao.borda2Y){
        return 1;
    }
    return 0;
}

// esses gets precisaram ser feitos pois cada botao é privado

BOTAO Interface::getBotaoAddImagem(){
    return botaoAddImagem;
}

BOTAO Interface::getBotaoClicar(){
    return clicar;
}

BOTAO Interface::getBotaoPincel(){
    return pincel;
}

BOTAO Interface::getBotaoSpray(){
    return spray;
}

BOTAO Interface::getBotaoMarcaTexto(){
    return marcaTexto;
}

BOTAO Interface::getBotaoBalde(){
    return balde;
}

BOTAO Interface::getBotaoBorracha(){
    return borracha;
}

BOTAO Interface::getBotaoVertical(){
    return fliperVertical;
}

BOTAO Interface::getBotaoHorizontal(){
    return fliperHorizontal;
}

BOTAO Interface::getBotaoCinza(){
    return tonsCinza;
}

BOTAO Interface::getBotaoAddBrilho(){
    return addBrilho;
}

BOTAO Interface::getBotaoAddGama(){
    return addGama;
}

BOTAO Interface::getBotaoAddContraste(){
    return addContraste;
}

BOTAO Interface::getBotaoAddBlur(){
    return addBlur;
}

BOTAO Interface::getBotaoSave(){
    return save;
}

BOTAO Interface::getBotaoLoad(){
    return load;
}

void Interface::alteraBotaoSelecionado(int botaoSelecionado){ // esse aqui altera qual botao está selecionado (pincel, spray, etc), e muda a borda dele
    this->botaoSelecionado = botaoSelecionado;
    clicar.tem_borda = 0;
    pincel.tem_borda = 0;
    spray.tem_borda = 0;
    marcaTexto.tem_borda = 0;
    balde.tem_borda = 0;
    borracha.tem_borda = 0;

    switch(botaoSelecionado){
        case 0:
            clicar.tem_borda = 1;
            break;
        case 1:
            pincel.tem_borda = 1;
            break;
        case 2:
            spray.tem_borda = 1;
            break;
        case 3:
            marcaTexto.tem_borda = 1;
            break;
        case 4:
            balde.tem_borda = 1;
            break;
        case 5:
            borracha.tem_borda = 1;
            break;
    }
}

void Interface::carregarNomeArquivos(){ // carrega os arquivos da pasta image
    struct dirent *entry;
    DIR *dp = opendir(".\\Trab1GabrielBaggio\\images");

    if (dp == nullptr)
        printf("Erro ao abrir diretorio das imagens, ajeitar nos diretorios do windows pra ficar certo");
    int cont = 0;
    while ((entry = readdir(dp))){
        if(cont > 1){
            BotaoArquivo novoBotao;
            novoBotao.deltaY = tamanhoBotaoArquivos * qntArquivos;
            novoBotao.nome = entry->d_name;
            botaoArquivos.push_back(novoBotao);
            qntArquivos++;
        }
        cont++;
    }

    closedir(dp);
}

void Interface::renderSubmenuArquivos(){ // renderiza aquele submenu de arquivos
    int i = 0;
    CV::color(0.2, 0.2, 0.2);
    CV::rectFill(submenuArquivos.borda1X, submenuArquivos.borda1Y, submenuArquivos.borda2X, submenuArquivos.borda2Y);
    CV::color(1, 1, 1);
    for(BotaoArquivo botaoArquivo : botaoArquivos){
        CV::text(submenuArquivos.borda1X, submenuArquivos.borda1Y + botaoArquivo.deltaY, botaoArquivo.nome.c_str());
        i++;
    }
}

void Interface::setAbertoSubmenuArquivos(bool aberto, int mouseX, int mouseY){ // abre ou fecha o submenu de arquivos
    submenuArquivos.aberto = aberto;
    submenuArquivos.borda1X = mouseX;
    submenuArquivos.borda1Y = mouseY - qntArquivos * 10;
    submenuArquivos.borda2X = mouseX + 150;
    submenuArquivos.borda2Y = mouseY;
}

bool Interface::getAbertoSubmenuArquivos(){
    return submenuArquivos.aberto;
}

Submenu Interface::getSubmenuArquivos(){
    return submenuArquivos;
}

bool Interface::verificaClickSubmenu(Submenu submenu, int mouseX, int mouseY){ // verifica se clicou dentro ou fora do submenu de arquivos
    if(mouseX > submenu.borda1X && mouseX < submenu.borda2X && mouseY > submenu.borda1Y && mouseY < submenu.borda2Y){
        return 1;
    }
    return 0;
}

std::string Interface::verificaArquivoParaAbrir(int mouseX, int mouseY){ // busca no click qual arquivo vai carregar na nova camada
    for(BotaoArquivo botaoArquivo : botaoArquivos){
        if(mouseX > submenuArquivos.borda1X - 2 && mouseX < submenuArquivos.borda2X + 2 && mouseY > submenuArquivos.borda1Y + botaoArquivo.deltaY - 2 && mouseY < submenuArquivos.borda1Y + botaoArquivo.deltaY + tamanhoBotaoArquivos + 2){
            return botaoArquivo.nome;
        }
    }
    return botaoArquivos[0].nome;
}

int Interface::getBotaoSelecionado(){
    return botaoSelecionado;
}

void Interface::setBotaoSelecionado(int botaoSelecionado){
    this->botaoSelecionado = botaoSelecionado;
}

unsigned char *Interface::getRGBA(){
    return RGBA;
}

int Interface::getRaioCor(){
    return raioCor;
}

bool Interface::verificaSegurandoSlider(Slider slider, int mouseX, int mouseY){
    if(mouseX > slider.inicioX && mouseX < slider.fimX + 10 && mouseY > slider.Y && mouseY < slider.Y + 10){
        return 1;
    }
    return 0;
}

// foi preciso fazer todos esses gets por causa que é privado

Slider Interface::getSliderR(){
    return sliderR;
}
Slider Interface::getSliderG(){
    return sliderG;
}
Slider Interface::getSliderB(){
    return sliderB;
}
Slider Interface::getSliderRaio(){
    return sliderRaio;
}

Slider Interface::getSliderBrilho(){
    return sliderBrilho;
}

Slider Interface::getSliderGama(){
    return sliderGama;
}

Slider Interface::getSliderContraste(){
    return sliderContraste;
}

Slider Interface::getSliderBlur(){
    return sliderBlur;
}

// não, não tem como fazer uma função generica pra settar o segurando de um slider, pois não tem como pegar o endereço dele por ser privado

void Interface::setSegurandoR(bool segurando){
    sliderR.segurando = segurando;
}
void Interface::setSegurandoG(bool segurando){
    sliderG.segurando = segurando;
}
void Interface::setSegurandoB(bool segurando){
    sliderB.segurando = segurando;
}
void Interface::setSegurandoRaio(bool segurando){
    sliderRaio.segurando = segurando;
}

void Interface::setSegurandoBrilho(bool segurando){
    sliderBrilho.segurando = segurando;
}

void Interface::setSegurandoGama(bool segurando){
    sliderGama.segurando = segurando;
}

void Interface::setSegurandoContraste(bool segurando){
    sliderContraste.segurando = segurando;
}

void Interface::setSegurandoBlur(bool segurando){
    sliderBlur.segurando = segurando;
}

// precisa ter todos esses aqui msm pra mudar pq ele nao consegue acessar fora

void Interface::mudaValorSliderR(int mouseX){
    int valor = (sliderR.valorMaximo - sliderR.valorMinimo) * (mouseX - sliderR.inicioX) / (sliderR.fimX - sliderR.inicioX) + sliderR.valorMinimo;
    if(valor > sliderR.valorMaximo){
        valor = sliderR.valorMaximo;
    }
    if(valor < sliderR.valorMinimo){
        valor = sliderR.valorMinimo;
    }
    sliderR.valorAtual = valor;
    RGBA[0] = valor;
}

void Interface::mudaValorSliderG(int mouseX){
    int valor = (sliderG.valorMaximo - sliderG.valorMinimo) * (mouseX - sliderG.inicioX) / (sliderG.fimX - sliderG.inicioX) + sliderG.valorMinimo;
    if(valor > sliderG.valorMaximo){
        valor = sliderG.valorMaximo;
    }
    if(valor < sliderG.valorMinimo){
        valor = sliderG.valorMinimo;
    }
    sliderG.valorAtual = valor;
    RGBA[1] = valor;
}

void Interface::mudaValorSliderB(int mouseX){
    int valor = (sliderB.valorMaximo - sliderB.valorMinimo) * (mouseX - sliderB.inicioX) / (sliderB.fimX - sliderB.inicioX) + sliderB.valorMinimo;
    if(valor > sliderB.valorMaximo){
        valor = sliderB.valorMaximo;
    }
    if(valor < sliderB.valorMinimo){
        valor = sliderB.valorMinimo;
    }
    sliderB.valorAtual = valor;
    RGBA[2] = valor;
}

void Interface::mudaValorSliderRaio(int mouseX){
    int valor = (sliderRaio.valorMaximo - sliderRaio.valorMinimo) * (mouseX - sliderRaio.inicioX) / (sliderRaio.fimX - sliderRaio.inicioX) + sliderRaio.valorMinimo;
    if(valor > sliderRaio.valorMaximo){
        valor = sliderRaio.valorMaximo;
    }
    if(valor < sliderRaio.valorMinimo){
        valor = sliderRaio.valorMinimo;
    }
    sliderRaio.valorAtual = valor;
    raioCor = valor;
}

void Interface::mudaValorSliderBrilho(int mouseX){
    int valor = (sliderBrilho.valorMaximo - sliderBrilho.valorMinimo) * (mouseX - sliderBrilho.inicioX) / (sliderBrilho.fimX - sliderBrilho.inicioX) + sliderBrilho.valorMinimo;
    if(valor > sliderBrilho.valorMaximo){
        valor = sliderBrilho.valorMaximo;
    }
    if(valor < sliderBrilho.valorMinimo){
        valor = sliderBrilho.valorMinimo;
    }
    sliderBrilho.valorAtual = valor;
}

void Interface::mudaValorSliderGama(int mouseX){
    int valor = (sliderGama.valorMaximo - sliderGama.valorMinimo) * (mouseX - sliderGama.inicioX) / (sliderGama.fimX - sliderGama.inicioX) + sliderGama.valorMinimo;
    if(valor > sliderGama.valorMaximo){
        valor = sliderGama.valorMaximo;
    }
    if(valor < sliderGama.valorMinimo){
        valor = sliderGama.valorMinimo;
    }
    sliderGama.valorAtual = valor;
}

void Interface::mudaValorSliderContraste(int mouseX){
    int valor = (sliderContraste.valorMaximo - sliderContraste.valorMinimo) * (mouseX - sliderContraste.inicioX) / (sliderContraste.fimX - sliderContraste.inicioX) + sliderContraste.valorMinimo;
    if(valor > sliderContraste.valorMaximo){
        valor = sliderContraste.valorMaximo;
    }
    if(valor < sliderContraste.valorMinimo){
        valor = sliderContraste.valorMinimo;
    }
    sliderContraste.valorAtual = valor;
}

void Interface::mudaValorSliderBlur(int mouseX){
    int valor = (sliderBlur.valorMaximo - sliderBlur.valorMinimo) * (mouseX - sliderBlur.inicioX) / (sliderBlur.fimX - sliderBlur.inicioX) + sliderBlur.valorMinimo;
    if(valor > sliderBlur.valorMaximo){
        valor = sliderBlur.valorMaximo;
    }
    if(valor < sliderBlur.valorMinimo){
        valor = sliderBlur.valorMinimo;
    }
    sliderBlur.valorAtual = valor;
}

void Interface::renderPreviewCor(int screenWidth){ // renderiza aquela corzinha que vai pintar
    CV::color(0.3, 0.3, 0.3);
    CV::rect(sliderRaio.fimX + 15, sliderRaio.Y, screenWidth - 5, sliderR.Y + 15);
    CV::color((float)RGBA[0] / 255, (float)RGBA[1] / 255, (float)RGBA[2] / 255);
    CV::rectFill(sliderRaio.fimX + 15, sliderRaio.Y, screenWidth - 5, sliderR.Y + 15);
}