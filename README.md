# SistemaSolar
Trabalho Prático da disciplina de Computação Gráfica do curso de Engenharia da Computação no CEFET-MG. 
# Aluna: Mônica Karine Caridade Pereira

# Instruções para compilar: 
- Compilação com make all
- Execução com make run

# Vídeo: https://youtu.be/85qpETZbiRw

# Itens obrigatórios implementados:
1.Mundo:
-> Objeto no centro (Sol) e, ao seu redor, orbitam os planetas que possuem rotação em torno do seu próprio eixo;
-> Os planetas possuem um satélite orbitando ao redor, (com exceção de Vênus e Mercúrio). Os satélites possuem rotação em torno do próprio eixo também. 
-> Todos os objetos citados possuem texturas

2. Câmera:
-> Usou-se a projeção perspectiva gluPerspective
-> Implementou-se a visão de cima e a visão "diagonal" 
-> As setas para cima e para baixo modificam o zoom.
-> É possível movimentar a câmera pelo mouse

3. Gráficos:
-> Implementou-se o modelo de iluminação do OpenGL
-> É possível remover/adicionar luz (Sol) no sistema solar. 

4. Controles:
	Setas: 
		*Direita: Rotaciona eixo X
		*Esquerda: Rotaciona eixo Y
		*Para baixo: Diminui zoom
		*Para cima: Aumenta zoom
	Teclas:
		*ESC: Sair
		*L - Ativa/remove iluminação/Sol
		*1 - Visão superior do sistema
		*C - Centraliza visão no Sol
		*O - Mostra/Esconde órbitas
	Mouse:
		*Botão direito+ movimento do mouse - Afasta/ aproxima câmera
		*Botão Esquerdo+movimento do mouse - Seleciona movimento para cima ou para baixo 

# Itens extras:

-> Carregou-se um objeto no formato .obj (asteróide). Esse objeto foi retirado do site: https://github.com/brownan/asteroids/blob/master/asteroid.obj
-> Tentou-se fazer um cinturão de asteróides a partir do .obj carregado, que separa os planetas grandes dos pequenos. 
-> Presença do nome de alguns objetos. 
-> Órbitas 
-> Anéis planetários: anéis ao redor dos planetas gigantes gasosos (Saturno e Júpiter) e gelados (Urano e Netuno)
-> Música de fundo. Link: https://www.youtube.com/watch?v=bUTU8YEGrYY
-> Tentou-se utilizar o diâmetro real dos planetas na implementação. 
