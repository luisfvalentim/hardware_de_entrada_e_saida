# Parte 1

## Dispositivos escolhidos:
1. **Entrada**: Teclado 
2. **Saída**: Impressora

## Configuração do Teclado

1. **Verificar se o teclado está reconhecido pelo sistema**:
   
   ```bash
   xinput list
   ```
   
2. **Configurar o layout do teclado**:

   Use o seguinte comando para abrir o arquivo de configuração:
   
   ```bash
   sudo nano /etc/default/keyboard
   ```
   
   Mudando layout de us para "us" para "br-abnt2" para o layout brasileiro

   ```bash
   XKBLAYOUT="br"
   ```

3. **Salve as alterações**:

   Pressione `CTRL + O` para salvar o arquivo e `CTRL + X` para sair do editor.

4. **Aplique as alterações**:

   Depois de editar o arquivo, execute os seguintes comandos para aplicar as mudanças:

   ```bash
   sudo dpkg-reconfigure keyboard-configuration
   sudo service keyboard-setup restart
   ```

## Configuração da Impressora
  
1. **Instalar o CUPS**:

   Se o CUPS ainda não estiver instalado, execute os comandos para instalar e iniciar o serviço:

   ```bash
   sudo apt update
   sudo apt install cups
   sudo systemctl start cups
   sudo systemctl enable cups
   ```

2. **Adicione o usuário ao grupo `lpadmin`**:

   Para configurar e gerenciar impressoras, o usuário precisa estar no grupo lpadmin. Adicione o usuário com o seguinte comando:

   ```bash
   sudo usermod -aG lpadmin $USER
   ```

3. **Acesse a interface do CUPS**:

   O CUPS tem uma interface web onde você pode adicionar e gerenciar impressoras. Acesse-a no navegador, digitando:

   ```bash
   http://localhost:631
   ```

4. **Adicione uma impressora**:

   No navegador, vá para Administration e clique em Add Printer. Você será solicitado a fazer login com seu usuário e senha do sistema.   A partir daí, selecione a impressora conectada ou forneça o endereço IP 
   se for uma impressora de rede.

5. **Instale drivers**:

   Dependendo da impressora, o CUPS pode solicitar drivers específicos. O sistema tentará detectar o driver automaticamente, mas, se      necessário, você pode fornecer o PPD (PostScript Printer Description) da 
   impressora.

6. **Configurar permissões de impressão**:

   Depois de adicionar a impressora, configure as permissões de impressão. Por padrão, o CUPS permite que todos imprimam. Para            restringir o acesso, você pode ajustar essas permissões nas configurações 
   de administração do CUPS.

7. **Verifique o status da impressora**:

   Após configurar a impressora, verifique se está funcionando corretamente com o comando:

   ```bash
   lpstat -p
   ```

8. **Imprima uma página de teste**:

   Finalmente, imprima uma página de teste para garantir que a configuração está correta: 

   ```bash
   sudo lp -d nome_impressora /usr/share/cups/data/testprint
   ```

# Parte 2

## Compilar e Executar

1. **Compilar o programa: Abra o terminal e execute o seguinte comando para compilar o programa**:

   ```bash
   gcc -o entrada_saida entrada_saida.c
   ```
  
2. **Executar o programa: Para executar o programa, digite**:
   
   ```bash
   ./entrada_saida
   ```

# Parte 3

## Passo 1: Executando o Programa e Preparando a Ferramenta de Monitoramento

1. **Compilar o programa**
2. Abra um terminal para monitorar o uso de recursos enquanto o programa estiver sendo executado.

## Passo 2: Monitorar com `top`

1. **Abra o top em um terminal**:

   ```bash
   top
   ```

2. **Procure o processo do programa**:

   Enquanto o programa está rodando, procure o nome do executável (`entrada_saida`). Ele será exibido na lista de processos do `top`.

## Passo 3: Monitorar com htop

1. **Instalar o `htop`**:

   ```bash
   sudo apt install htop
   ```

2. **Abra o `htop` em um terminal**:

   ```bash
   htop
   ```

3. **Monitorar o uso de CPU e memória**:

   No `htop`, você pode ver uma lista visualmente mais clara de todos os processos. Procure o processo `entrada_saida` (ou o nome que você deu ao executável) e observe o uso de recursos enquanto o programa está     em execução.

4. **Filtrar o processo específico**:

   Você pode pressionar `F3` para buscar diretamente o processo pelo nome e monitorar o uso de CPU e memória de forma mais focada.

## Passo 4: Monitorar E/S com iotop

1. **Instalar o `iotop`**:

   ```bash
   sudo apt install iotop
   ```

2. **Executar o `iotop`**:

   ```bash
   sudo iotop
   ```

3. **Monitorar o uso de CPU e memória**:

   O `iotop` mostrará processos que estão executando operações de leitura e gravação de disco. Quando o seu programa criar e enviar o arquivo para a impressora, você verá o processo correspondente com as            operações de E/S sendo feitas.

# Parte 4

## Erro 1: Falta de Papel na Impressora

### Cenário:

Neste cenário, você pode simular a falta de papel removendo fisicamente o papel da impressora ou alterando as configurações para forçar a impressão quando o papel estiver ausente.

### Simulação:

1. **Remova o papel da impressora (ou configure a impressora para pensar que está sem papel)**.

2. **Tente executar o programa para enviar um texto à impressora**.

### Registro de como o sistema lida com o erro:

1. **Comando lpstat: Antes de imprimir, você pode verificar o estado da impressora**:

   ```cash
   lpstat -p nome_impressora
   ```

   Se o papel estiver ausente, você verá uma mensagem como:

   ```cash
   printer nome_impressora is idle. enabled since Tue 05 Oct 2024 08:15:05 AM - "Out of paper"
   ```

2. **Monitoramento de Erro com `dmesg` ou `journalctl`**:

   ```bash
   dmesg | grep printer
   ```

   ou

   ```bash
   journalctl -xe | grep printer
   ```

3. **Corrigindo o erro: Coloque papel na impressora e use o seguinte comando para reiniciar o trabalho de impressão**:

   ```bash
   sudo cupsenable nome_impressora
   sudo cupsaccept nome_impressora
   ```

### Erro 2: Desconexão Temporária do Teclado

### Cenário:

Neste caso, você pode simular a desconexão temporária do teclado ao desconectá-lo fisicamente (se for um teclado USB) ou desabilitando-o temporariamente via software.

### Simulação:

1. **Remova o papel da impressora (ou configure a impressora para pensar que está sem papel)**.

2. **Tente executar o programa para enviar um texto à impressora**.

### Registro de como o sistema lida com o erro:

1. **Desconecte fisicamente o teclado USB ou desative o dispositivo de entrada usando o comando `xinput`:**:

   Primeiro, encontre o ID do teclado:
   
   ```cash
   xinput list
   ```

   Desative o teclado:

   ```cash
   xinput disable ID_TECLADO
   ```

   Se o papel estiver ausente, você verá uma mensagem como:

   ```cash
   printer nome_impressora is idle. enabled since Tue 05 Oct 2024 08:15:05 AM - "Out of paper"
   ```

2. **Tente executar o programa que solicita a entrada de texto.**:

### Registro de como o sistema lida com o erro:

1. **Verifique o status do dispositivo**:
   
   ```bash
   dmesg | grep usb
   ```

3. **Correção do erro:**:

   Para reconectar fisicamente o teclado, basta conectar novamente o cabo USB.

   Para reativar via software:

   ```bash
   xinput enable ID_TECLADO
   ```

## Erro 3: Impressora Desconectada (Impressora Off-line)

### Cenário:

Você pode simular que a impressora está desconectada temporariamente (off-line) ao desligá-la ou desativar a conexão de rede se for uma impressora de rede.

### Simulação:

1. **Desligue a impressora ou desconecte-a da rede.**.

2. **Tente executar o programa para enviar um texto à impressora**.

### Registro de como o sistema lida com o erro:

1. **Status do trabalho de impressão**:

   O trabalho de impressão será enfileirado, mas o lpstat mostrará que a impressora está indisponível:

   ```cash
   lpstat -p nome_impressora
   ```

   O resultado será algo como:

   ```cash
   printer nome_impressora is idle. enabled since Tue 05 Oct 2024 08:15:05 AM - "Out of paper"
   ```

2. **Logs do sistema: Verifique os logs do sistema para mais detalhes**:

   ```bash
   dmesg | grep printer
   journalctl -xe | grep printer
   ```

   ou

   ```bash
   journalctl -xe | grep printer
   ```

4. **Correção do erro**:

   ```bash
   sudo cupsenable nome_impressora
   sudo cupsaccept nome_impressora
   ```

# Parte 5

## Introdução

Esse relatório tem como objetivo explicar o processo de configuração dos dispositivos de entrada e saída, além de descrever os testes práticos e o acompanhamento do uso dos recursos do sistema enquanto um programa roda. Também foi simulada uma situação em que ocorrem erros, para entender como o sistema operacional reage a falhas nos dispositivos de E/S (Entrada/Saída) e como isso pode impactar a experiência do usuário.

## Parte 1: Configuração dos Dispositivos

1. **Configuração do Teclado**:
   A primeira etapa foi configurar o teclado como dispositivo de entrada. No Linux, é possível alterar o layout do teclado editando o arquivo `/etc/default/keyboard`. No meu caso, alterei o layout de "us" para      "br-abnt2", que corresponde ao layout brasileiro. Para fazer isso, usei o editor de texto `nano` para modificar o arquivo de configuração, ajustando a linha responsável pelo layout para `XKBLAYOUT="br-           abnt2"`. Após realizar a alteração, apliquei as novas configurações executando os comandos `sudo dpkg-reconfigure keyboard-configuration` e `sudo service keyboard-setup restart`. Isso garantiu que o teclado      utilizasse o layout brasileiro corretamente, permitindo a entrada de texto com todos os caracteres especiais usados em português.





2. **Configuração da Impressora**
   
   A impressora, um dispositivo de saída, foi configurada utilizando o CUPS (Common Unix Printing System), um sistema popular no Linux para gerenciamento de impressoras. A instalação foi feita usando os comandos    adequados, e após a instalação, adicionei a impressora através da interface web do CUPS, acessível no navegador pelo endereço `http://localhost:631`. No painel de administração do CUPS, a impressora foi          detectada e adicionada. Com isso, ela estava pronta para uso, configurada e capaz de aceitar trabalhos de impressão. Para garantir que estava funcionando corretamente, imprime uma página de teste usando o        comando adequado.


## Parte 2: Programa para Demonstrar Funcionamento dos Dispositivos

Para demonstrar o funcionamento dos dispositivos configurados (teclado e impressora), desenvolvi um programa simples em C. Esse programa captura a entrada de texto via teclado e, em seguida, envia o texto para a impressora. O código foi estruturado de forma que o texto digitado pelo usuário seja armazenado em um arquivo temporário, que depois é enviado para a impressora usando o comando lp. Após a impressão, o arquivo é removido do sistema.

## Parte 3: Monitoramento do Uso de Recursos

Durante a execução do programa, usei ferramentas de monitoramento como `htop` e `iotop` para verificar o uso de CPU, memória e operações de entrada/saída. O `htop` foi utilizado para monitorar o uso de CPU e memória, e notei um pequeno aumento no uso da CPU enquanto o programa aguardava a entrada do usuário, manipulava o arquivo temporário e enviava o arquivo para a impressora. Capturas de tela do `htop` mostraram o processo em execução, revelando que o impacto no sistema foi mínimo, já que o programa é simples e leve. Já o `iotop` foi usado para monitorar as operações de leitura e gravação no disco. Durante a criação e o envio do arquivo temporário, houve um aumento temporário no uso de E/S de disco, mas, após o envio para a impressora, a atividade de E/S voltou ao normal. Essas ferramentas demonstraram que o sistema gerencia os recursos de forma eficiente, alocando CPU e disco conforme necessário, sem sobrecarregar o sistema.

## Parte 4: Simulação de Cenários de Erro

Nesta seção, simulei dois cenários de erro para observar como o sistema lida com falhas. No primeiro cenário, simulei a falta de papel na impressora, removendo fisicamente o papel. Ao tentar executar o programa, o trabalho de impressão foi enfileirado, mas não foi impresso. Com o comando `lpstat`, verifiquei o erro registrado, que também apareceu nos logs do sistema, acessíveis pelo comando `dmesg`. Assim que recoloquei o papel na impressora, o trabalho foi processado com sucesso. No segundo cenário, desconectei temporariamente o teclado, desativando o dispositivo com o comando `xinput`. Enquanto o teclado estava desconectado, o programa ficou esperando indefinidamente por entrada do usuário, já que o dispositivo de entrada não estava disponível. Quando reconectei o teclado, o programa continuou a execução normalmente. Esses cenários demonstraram como o sistema lida com falhas de hardware, mantendo os processos em andamento, mas aguardando a resolução dos erros para prosseguir.

## Parte 5: Importância do Gerenciamento de Dispositivos de E/S

O gerenciamento eficiente de dispositivos de entrada e saída é fundamental para o bom funcionamento dos sistemas operacionais. A capacidade do sistema de detectar, gerenciar e notificar falhas, como a falta de papel na impressora ou a desconexão de um teclado, garante que o sistema permaneça funcional e que o usuário seja devidamente informado sobre os problemas. Além disso, ferramentas de monitoramento, como `htop` e `iotop`, permitem acompanhar o uso de recursos e ajustar a alocação de CPU, memória e disco de forma eficiente. Essa habilidade de monitoramento e gerenciamento impacta diretamente a experiência do usuário, assegurando que o sistema continue operando de maneira estável e que os erros possam ser resolvidos sem interrupções significativas.

## Conclusão

O processo de configuração, execução e monitoramento dos dispositivos de entrada e saída demonstrou que o sistema operacional Linux é robusto em sua capacidade de lidar com falhas e gerenciar recursos de forma eficaz. A simulação de cenários de erro, como a falta de papel na impressora ou a desconexão do teclado, mostrou que o sistema pode manter a integridade dos processos e oferecer uma experiência de usuário tranquila, mesmo diante de falhas de dispositivos.

   

   
   
   
