FROM alpine:3.23
LABEL maintainer="xiaobo <peterwillcn@gmail.com>"

ENV GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

RUN apk update && apk add --no-cache \
    argp-standalone asciidoc bash bc binutils bzip2 \
    cdrkit coreutils diffutils e2fsprogs-dev findutils flex g++ \
    gawk gcc gettext git grep gzip intltool libtool libxslt linux-headers make \
    musl-libintl musl-obstack-dev ncurses-dev openssl-dev patch perl \
    python3-dev py3-setuptools quilt rsync swig tar unzip util-linux wget zlib-dev \
    autoconf automake build-base elfutils-dev lzo-dev musl-fts-dev \
    pkgconfig py3-distutils-extra py3-elftools sed vim bsd-compat-headers && \
  addgroup buildbot && \
  adduser -s /bin/bash -G buildbot -D buildbot

USER buildbot
COPY .quiltrc /home/buildbot
WORKDIR /workdir
