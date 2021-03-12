## Estrutura do Repositório

* Abaixo encontra-se a estrutura do repositório com seus respectivos arquivos. Os requisitos obrigatórios e optativos estão inclusos em uma mesmo documento contido na pasta **"01_documento_completo"**. 

* O documento denominado **arquivoCompleto.pdf** contém todo o **Projeto Eletrônico Executivo, orçamento da proposta, lista de fornecedores, simulações do sistema de controle, simulações do sistema de processamento e Implementação de operações matemáticas no sistema de processamento de dados**.

📦**01_documento_completo** \
 ┣ 📜arquivoCompleto.pdf \
📦**02_codigos** \
 ┣ 📜01_microcontrolador.cpp \
 ┣ 📜02_plot_real_time \
 ┣ 📜03_recover_data_patient \
 ┣ 📜04_dataPlayer1 \
 ┣ 📜05_dataPlayer2 \
 ┣ 📜06_dataPlayer3 \
 ┣ 📜07_dataPlayer4 \
 📦**03_esquematicos_circuitos** \
 ┣ 📜01_projetoCompleto.pdf \
 ┣ 📜02_projetoIndividual.pdf \
 📦**04_arquivos_proteus** \
 ┣ 📂01_projetoCompleto \
 ┣ 📂02_projetoPCB 
 
 ## Identificação de partes importantes no documento:
 
 * **MEMORIAL DE CÁLCULOS:**  Durante todo o documento as equações e modelos matemáticos utilizados são explicados individualmente ao decorrer do texto. Um memorial de cálculos foi anexado para melhor análise dos modelos matemáticos no **Apêndice B** da **Página 44**. 
 
 * **PROCESSAMENTO DIGITAL DO SINAL:** Este tópico encontra-se na **Seção 1.3** da **Página 18-21**. Antes disso, é discutido a construção do Biossensor como parte do canal de instrumentação na **Seção 1.1** da **Página 10-17**.
 
* **DETALHAMENTO DO SISTEMA DE CONTROLE:** É discutido ao longo do **Capítulo 3** sobre a plataforma de controle para os carrinhos. O algoritmo de controle de velocidade proposto para os carrinhos é discutido especificamente na **Seção 3.2** da **Página 33-37**.

* **LISTA DE MATERIAIS E EQUIPAMENTOS/ORÇAMENTO:** Tanto a lista de materiais quanto a de Orçamento do projeto se encontram no **Capítulo 4** da **Página 38**. 

* **LISTA DE FORNECEDORES:** Encontra-se no **Capítulo 5** da **Página 39**. 

* **SIMULAÇÕES DO SISTEMA DE CONTROLE E PROCESSAMENTO:** No **Apêndice C** da **Página 45** encontram-se prints de simulações desenvolvidas no Software Proteus sobre o sistema de controle e processamento. Caso não seja suficiente para análise, considerar os 2 vídeos feitos de simulação do sistema de controle e processamento pelos links: 
\
[SIMULAÇÃO DE PROCESSAMENTO E CONTROLE](https://youtu.be/yx-JKuLpTcY) - **Youtube Video 1**.
\
[SIMULAÇÃO DO SISTEMA DE MONITORAMENTO COM OS 4 PACIENTES](https://youtu.be/WNo6eDHGgP4) - **Youtube Video 2**.

* **IMPLEMENTAÇÃO DE OPERAÇÕES MATEMÁTICAS NO SISTEMA DE PROCESSAMENTO DE DADOS:** Na **Seção 1.3.1** da **Página 19-21** é discutido sobre as operações feitas no sinal EMG por meio do filtro média móvel. 

* **PROTOCOLO DE SEGURANÇA PARA O PACIENTE:** Discutido nas **Páginas 12 e 13**.

* **ARMAZENAMENTO DOS DADOS E MOSTRAGEM EM TEMPO REAL:** Discutido nas **Páginas 25 e 26** e demonstrado nos vídeos de simulação.

* **INDICATIVO VISUAL PARA O VENCEDOR:** Discutido na **Página 37**.

* **MODELO DE PLACA PCB PROPOSTA:** Representado no **Apêndice D** nas **Páginas 48, 49, 50**.

Conforme demonstrado acima, todos os requisitos obrigatório e optativos do sistema foram realizados assim como suas especificações de acordo com o documento de orientações. O arquivo **arquivoCompleto.pdf** contém ainda diversas outras informações sobre o sistema em questão. Favor verificar com cautela o que foi exposto no **Sumário** do documento para devida identificação de tópicos relacionados.

Os esquemáticos eletrônicos completos desenvolvidos no Proteus encontra-se na pasta **03_esquematicos_circuitos**. Esses mesmos esquemáticos são apresentados nos 2 vídeos de simulação. A pasta **02_codigos** contém os códigos usados no microcontrolador, o script de coletagem dos dados e plotagem em tempo real e o script de acesso ao datalogger do sistema. Junto a isso, estão contidos os arquivos CSVs de cada paciente com os valores dos sinais EMG. A pasta **04_arquivos_proteus** contém os arquivos do Software Proteus utilizados para a simulação do sistema e confecção da placa PCB proposta.