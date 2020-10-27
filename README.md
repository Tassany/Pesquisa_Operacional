# Pesquisa_Operacional

Este repositório serve apenas como um depósito para as atividades que envolvem a disciplina de Pesquisa Operacional na UFPB. 


O resolvedor pode ser encontrado no seguinte link:
 
(https://www.ibm.com/br-pt/products/ilog-cplex-optimization-studio)

Antes de iniciar o programa é importante verificar se o seguinte trecho de código do Makefile do arquivo está indicando o local correto onde o resolvedor foi instalado no computador.


####diretorios com as libs do cplex
CPLEXDIR  = /home/tassany/Downloads/CPLEX/cplex/
CONCERTDIR =/home/tassany/Downloads/CPLEX/concert/
   
CPLEXLIBDIR   = $(CPLEXDIR)/lib/x86-64_linux/static_pic
CONCERTLIBDIR = $(CONCERTDIR)/lib/x86-64_linux/static_pic


Em seguida, no terminal onde está o programa execute "make rebuild". Após nenhum erro ocorrer, o programa pode ser executado "./maxcover instances/1.txt" (o instances/ é apenas necessário se os números estiverem dentro da pasta instances).
