#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h> 
#include <stdlib.h>

using namespace std;

string matrizElementos[6][6] = {""};
string matrizExibida[6][6] = {""};
bool jogadorComTesouro = false;
bool jogadorVenceu = false;
bool jogadorVivo = false;
int flechas = 2;
int posicaoX;
int posicaoY;

void inserirElemento(string elemento, string informacao);
void inserirInformacao(string informacao, int x, int y);
void verificarAtaquePosicaoY(int posicaoAtaque);
void verificarAtaquePosicaoX(int posicaoAtaque);
void atualizarCoordenadaX(int posicao);
void atualizarCoordenadaY(int posicao);
void retirarMonstroWumpus();
void retirarTesouro();
void imprimirMundoWumpus();
void criarMundoWumpus();
void iniciarJogo();
void imprimirStatus();
void fimDeJogo();
void escolherAcao();
bool movimentarJogador(string movimento);
bool atacarMonstro(string ataque);
int getPosicao(int min, int max);
string verificarCaverna();
string verificarTesouro();

int main() {
	
	
	iniciarJogo();
	
	while (jogadorVivo) {	
	
		imprimirMundoWumpus();
		imprimirStatus();
		
		if (jogadorVivo) {
                
                        escolherAcao();
		}
		
		if (jogadorComTesouro && matrizElementos[posicaoX][posicaoY] == "Entrada") {
		
		        jogadorVenceu = true;
		        fimDeJogo();
		        break;
		}
	}
        
	return 0;
}

void iniciarJogo() {
	string iniciaJogo;

	cout << endl;
	cout << endl;
	cout << endl;

	cout << "                    **   **   **   **   **    **   ****      ******                    "<< endl;
	cout << "                    *** ***   **   **   ***   **   **   **   **  **                    "<< endl;
	cout << "                    ** * **   **   **   ** *  **   **   **   **  **                    "<< endl;
	cout << "                    **   **   **   **   **  * **   **   **   **  **                    "<< endl;
	cout << "                    **   **     ***     **   ***   ****      ******                    "<< endl;

	cout << endl;
	cout << endl;

	cout <<"                  **   **   **   **   **   **   *****    **    **    ****                      "<< endl;
	cout <<"                  **   **   **   **   *** ***   **  **   **    **   *                          "<< endl;
	cout <<"                  ** * **   **   **   ** * **   ** **    **    **   *****                      "<< endl;
	cout <<"                  *** ***   **   **   **   **   **       **    **        *                     "<< endl;
	cout <<"                  **   **     ***     **   **   **         ***      *****                      "<< endl;

	cout << endl;
	cout << endl;
	cout << endl;

	cout <<"    O mundo do Wumpus é caracterizado por um labirinto habitado por um terrível monstro, "<< endl;
	cout <<"    Wumpus e seu valioso tesouro. O objetivo do jogo é encontrar o tesouro e sair do la- "<< endl;
	cout <<"    birinto sem ser capturado pelo monstro ou morto por  suas armadilhas. Para encontrar "<< endl;
	cout <<"    o tesouro, o jogador deve caminhar entre as cavernas do labirinto guiado por suas p- "<< endl;
	cout <<"    ercepções: a brisa indica que próximo existem abismos espalhados nas cavernas próxi- "<< endl;
	cout <<"    mas; o mau cheiro indica que o terrível Wumpus está próximo;e o brilho indica que e-"<<endl;
	cout <<"    stá próximo da caverna com o ouro. O jogador dispõe de apenas duas flechas que pode- "<< endl;
	cout <<"    rão ser disparadas para matar o Wumpus. Após encontrar o tesouro o jogador sairá ve"<<endl;
	cout <<"    ncedor se conseguir retornar para a porta de entrada do labirinto. " << endl;

	cout << endl;
	cout << endl;

	cout << "Deseja começar o jogo? (S - Sim; N - Nao): ";
	cin >> iniciaJogo;	

	if (iniciaJogo == "S") {
		jogadorVivo = true;
		criarMundoWumpus();
	
	}
}

void criarMundoWumpus() {

	inserirElemento("Entrada", "");
	inserirElemento("Monstro Wumpus", "Cheiro do Wumpus");
	inserirElemento("Abismo", "Brisa");
	inserirElemento("Abismo", "Brisa");
	inserirElemento("Abismo", "Brisa");
	inserirElemento("Abismo", "Brisa");
	inserirElemento("Tesouro", "Brilho do Tesouro");
}

void imprimirMundoWumpus() {

	system("clear");

	for (int i = 0; i < 6; i++) {

		for (int j = 0; j < 6; j++) {
			
			if (matrizExibida[i][j] == "") {

				cout << " - ";
			}
			else {
			
				cout << " " << matrizExibida[i][j] << " ";
			}
		}
		
		cout << endl;
	}
}

void imprimirStatus() {
        
        string caverna = verificarCaverna();
        string tesouro = verificarTesouro();
        
        cout << endl;
        cout << "STATUS: " << endl;
        cout << "       " << caverna << endl;
        cout << "       " << tesouro << endl;
        
        if (!jogadorVivo) {
        
                cout << endl;
                cout << "       GAME OVER" << endl;
        }
}
void escolherAcao() {

        string acao = "";
        string acaoInvalida = "       Ação Inválida! :(";

	cout << endl;

        cout << "AÇÃO:" << endl;
	cout << "       Escolher ação (A - atacar, M - mover): ";
	cin >> acao;

	if (acao == "A") {
	
	        if (flechas > 0) {
	
	                string ataque = "";
	                
	                cout << "       Atacar em qual direção (C - cima, B - baixo, E - esquerda, D - direita)? ";
	
	                cin >> ataque;
	                
	                if (!atacarMonstro(ataque)) {

                                cout << endl;
	                        cout << "Erro:" << endl;
			        cout << endl << acaoInvalida << endl;
			        system("sleep 4");				
		        }
	        }
	        
	        else {
	        
	                cout << endl;
	                cout << "Erro:" << endl;
	                cout << "       Você não tem flechas para poder atacar." << endl;
	                system("sleep 4");
	        }
	}

	else if (acao == "M") {
		
		string movimento = "";
		
		cout << endl;
		cout << "       Mover em qual direção (C - cima, B - baixo, E - esquerda, D - direita)? ";
		
		cin >> movimento;

		if(!movimentarJogador(movimento)){
		
	                cout << endl;
	                cout << "Erro:" << endl;
			cout << endl << acaoInvalida << endl;
			system("sleep 4");				
		}
	} 

	else {

                cout << endl;
		cout << "Erro:" << endl;
		cout << acaoInvalida << endl;
		system("sleep 4");
	}
}

bool atacarMonstro(string ataque) {

        bool ataqueValido = true;	
	
	if (ataque == "E") {

		int posicaoAtaque = posicaoY - 1;

		if (posicaoAtaque < 0) {

			ataqueValido = false;
		} 

		else {
			
			cout << endl;
			cout << "ATAQUE:" << endl;
			verificarAtaquePosicaoY(posicaoAtaque);
			cout << "Voce agora tem " << flechas << " flechas." << endl;
			system("sleep 3");
		}
	}

	else if (ataque == "D") {

		int posicaoAtaque = posicaoY + 1;

		if (posicaoAtaque > 5) {

			ataqueValido = false;
		}

		else {
			
			cout << endl;
			cout << "ATAQUE:" << endl;
			verificarAtaquePosicaoY(posicaoAtaque);			
			cout << "Voce agora tem " << flechas << " flechas." << endl;
			system("sleep 3");
		}
	}

	else if (ataque == "C") {

		int posicaoAtaque = posicaoX - 1;

		if (posicaoAtaque < 0) {

			ataqueValido = false;
		} 

		else {
			
			cout << endl;
			cout << "ATAQUE:" << endl;
			verificarAtaquePosicaoX(posicaoAtaque);			
			cout << "Voce agora tem " << flechas << " flechas." << endl;
			system("sleep 3");
			
		}
	}

	else if (ataque == "B") {

		int posicaoAtaque = posicaoX + 1;

		if (posicaoAtaque > 5) {

			ataqueValido = false;
		}
		
		else {
			
			cout << endl;
			cout << "ATAQUE:" << endl;
			verificarAtaquePosicaoX(posicaoAtaque);			
			cout << "Voce agora tem " << flechas << " flechas." << endl;			
			system("sleep 3");
		}
	}

	else {

		ataqueValido = false;
	}

	return ataqueValido;
}

bool movimentarJogador(string movimento) {

	bool movimentoValido = true;	
	
	if (movimento == "E") {

		int novaPosicaoY = posicaoY - 1;

		if (novaPosicaoY < 0) {

			movimentoValido = false;
		} 

		else {
			
			atualizarCoordenadaY(novaPosicaoY);			
			
		}
	}

	else if (movimento == "D") {

		int novaPosicaoY = posicaoY + 1;

		if (novaPosicaoY > 5) {

			movimentoValido = false;
		}

		else {
			
			atualizarCoordenadaY(novaPosicaoY);			
			
		}
	}

	else if (movimento == "C") {

		int novaPosicaoX = posicaoX - 1;

		if (novaPosicaoX < 0) {

			movimentoValido = false;
		} 

		else {
			
			atualizarCoordenadaX(novaPosicaoX);			
			
		}
	}

	else if (movimento == "B") {

		int novaPosicaoX = posicaoX + 1;

		if (novaPosicaoX > 5) {

			movimentoValido = false;
		} 

		else {
			
			atualizarCoordenadaX(novaPosicaoX);	
			
		}
	}

	else {

		movimentoValido = false;
	}

	return movimentoValido;
}

void retirarMonstroWumpus() {

        for (int i = 0; i < 6; i++) {
        
                for (int j = 0; j < 6; j++) {
                
                        if (matrizElementos[i][j] == "Monstro Wumpus" || matrizElementos[i][j] == "Cheiro do Wumpus") {
                        
                                matrizElementos[i][j] = "";
                        }
                }
        }
}

void retirarTesouro() {

	matrizElementos[posicaoX][posicaoY] = "";
	
	if (posicaoX-1 >= 0 && matrizElementos[posicaoX-1][posicaoY] == "Brilho do Tesouro") {
		
		matrizElementos[posicaoX-1][posicaoY] = "";
	}
	if (posicaoX+1 <= 5 && matrizElementos[posicaoX+1][posicaoY] == "Brilho do Tesouro") {
		
		matrizElementos[posicaoX+1][posicaoY] = "";
	}
	if (posicaoY-1 >= 0 && matrizElementos[posicaoX][posicaoY-1] == "Brilho do Tesouro") {
		
		matrizElementos[posicaoX][posicaoY-1] = "";
	}
	if (posicaoY+1 <= 5 && matrizElementos[posicaoX][posicaoY+1] == "Brilho do Tesouro") {
		
		matrizElementos[posicaoX][posicaoY+1] = "";
	}
}

void verificarAtaquePosicaoY(int posicaoAtaque) {

        flechas--;

        if (matrizElementos[posicaoX][posicaoAtaque] == "Monstro Wumpus") {
        
                retirarMonstroWumpus();

                cout << "       Você acertou o monstro Wumpus!" << endl;
                system("sleep 4");                
		cout << endl;
        }
        
        else {
        
                cout << "       Você errou!" << endl;
                system("sleep 4");
		cout << endl;
        }
}

void verificarAtaquePosicaoX(int posicaoAtaque) {

        flechas--;

        if (matrizElementos[posicaoAtaque][posicaoY] == "Monstro Wumpus") {
        
                retirarMonstroWumpus();

                cout << "       Você acertou o monstro Wumpus!" << endl;
                system("sleep 4");                
		cout << endl;
        }
        
        else {
        
                cout << "       Você errou!" << endl;
                system("sleep 4");
		cout << endl;
        }
}


void inserirElemento(string elemento, string informacao) {

	int x, y;

	while(true) {

		x = getPosicao(0, 5);
		y = getPosicao(0, 5);
		
		if (matrizElementos[x][y] == "") {

			matrizElementos[x][y] = elemento;
			
			if (elemento == "Entrada") {

				matrizExibida[x][y] = "@";
				posicaoX = x;
				posicaoY = y;
			}			

			inserirInformacao(informacao, x, y);
			break;
		}
	}
}

int getPosicao(int min, int max) {

	static int Init = 0;
	int rc;

	if (Init == 0) {

		srand(time(NULL));
		Init = 1;
	}

	rc = (rand() % (max - min + 1) + min);

	return rc;
}

void inserirInformacao(string informacao, int x, int y) {

	if (x-1 >= 0 && matrizElementos[x-1][y] == "") {
		
		matrizElementos[x-1][y] = informacao;
	}
	if (x+1 <= 5 && matrizElementos[x+1][y] == "") {
		
		matrizElementos[x+1][y] = informacao;
	}
	if (y-1 >= 0 && matrizElementos[x][y-1] == "") {
		
		matrizElementos[x][y-1] = informacao;
	}
	if (y+1 <= 5 && matrizElementos[x][y+1] == "") {
		
		matrizElementos[x][y+1] = informacao;
	}
}





void atualizarCoordenadaX(int posicao) {

	matrizExibida[posicaoX][posicaoY] = "";
	posicaoX = posicao;
	matrizExibida[posicaoX][posicaoY] = "@";	
}

void atualizarCoordenadaY(int posicao) {

	matrizExibida[posicaoX][posicaoY] = "";
	posicaoY = posicao;
	matrizExibida[posicaoX][posicaoY] = "@";
}




string verificarCaverna() {

        string caverna = "";
        
        if (matrizElementos[posicaoX][posicaoY] == "") {
        
                caverna = "Você está em uma caverna vazia.";
        }
        
        else if (matrizElementos[posicaoX][posicaoY] == "Entrada" && !jogadorComTesouro) {
        
                caverna = "Você está na entrada do Mundo Wumpus.";
        }
        
        else if (matrizElementos[posicaoX][posicaoY] == "Monstro Wumpus") {
        
                caverna = "O monstro Wumpus te pegou!";
                jogadorVivo = false;
        }
        
        else if (matrizElementos[posicaoX][posicaoY] == "Cheiro do Wumpus") {
        
                caverna = "Você está em uma caverna com cheiro do monstro Wumpus.";
        }
        
        else if (matrizElementos[posicaoX][posicaoY] == "Abismo") {
        
                caverna = "Você caiu em um abismo!";
                jogadorVivo = false;
        }
        
        else if (matrizElementos[posicaoX][posicaoY] == "Brisa") {
        
                caverna = "Você está em uma caverna com brisa.";
        }
        
        else if (matrizElementos[posicaoX][posicaoY] == "Brilho do Tesouro") {
        
                caverna = "Você está em uma caverna onde se ver o brilho do tesouro!";
        }
        
        else if (matrizElementos[posicaoX][posicaoY] == "Tesouro") {
        
                caverna = "Você está na caverna do tesouro!";
		retirarTesouro();
                jogadorComTesouro = true;
        }
        
        return caverna;
}

string verificarTesouro() {

        string tesouro = "";
        
        if (jogadorComTesouro) {
        
                tesouro = "Você está com o tesouro!\n       Volte até a entrada!";
                
        }
        
        return tesouro;
}

void fimDeJogo() {

        system("clear");
        cout << "Parabéns! Você conseguiu pegar o tesouro e sair do Mundo Wumpus!" << endl;
        cout << endl;
}
