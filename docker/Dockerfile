# Imagen para compilar los libros (HTML y PDF): arco-authors ya trae make,
# xsltproc, dblatex, inkscape y TeX Live; aquí se añade lo que falta para el
# Makefile (ver DEPENDS).
#
#   docker build -t pensarencpp docker
#   docker run --rm -u $(id -u):$(id -g) -e HOME=/tmp -v $PWD:/host -w /host \
#       pensarencpp make products

FROM ghcr.io/uclm-arco/arco-authors/arco-authors:latest

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        bzip2 docbook-xsl highlight && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
