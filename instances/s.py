import os
import re

def limpar_formato_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r') as arquivo:
        linhas = arquivo.readlines()
        # Remover as duas últimas linhas
        conteudo_limpo = ''.join(linhas[:-2])
        # Limpar o padrão ""
        conteudo_limpo = re.sub(r'-{3,}', '', conteudo_limpo)
    with open(nome_arquivo, 'w') as arquivo:
        arquivo.write(conteudo_limpo)

def percorrer_subdiretorios(pasta):
    for raiz, subdiretorios, arquivos in os.walk(pasta):
        for arquivo in arquivos:
            nome_arquivo = os.path.join(raiz, arquivo)
            limpar_formato_arquivo(nome_arquivo)

if __name__ == "__main__":
    pasta_atual = '.'  # Pasta atual, ajuste conforme necessário
