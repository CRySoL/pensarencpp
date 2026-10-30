# Imagen para compilar los libros (HTML y PDF): arco-authors aporta make,
# inkscape y TeX Live; aquí se instala el resto de DEPENDS que usa
# «make products». Se listan todos aunque la imagen base traiga alguno, porque
# su contenido cambia entre versiones.
#
#   docker build -t pensarencpp docker
#   docker run --rm -u $(id -u):$(id -g) -e HOME=/tmp -v $PWD:/host -w /host \
#       pensarencpp make products

FROM ghcr.io/uclm-arco/arco-authors/arco-authors:latest

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        bzip2 dblatex docbook-xml docbook-xsl highlight inkscape make \
        python3 xsltproc && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
