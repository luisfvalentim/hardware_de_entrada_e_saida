# Configuração de Teclado e Impressora no Linux

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
  

   
   
   
