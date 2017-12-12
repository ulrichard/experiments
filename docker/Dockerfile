FROM ubuntu:xenial
MAINTAINER Richard Ulrich   "richi@ulrichard.ch"

# Tell debconf to run in non-interactive mode
ENV DEBIAN_FRONTEND noninteractive

# Make sure the repository information is up to date
RUN apt-get update && apt-get -y dist-upgrade

# We need ssh to access the docker container, wget
RUN apt-get update && apt-get install -y openssh-server wget \
    bash gawk gnulib sudo

# manually install some dependencies
RUN apt-get update && apt-get install -y libgtk2.0-0 libnotify4 \
    libgconf-2-4 libnss3 libasound2

# download and extract the jaxx archive
RUN wget https://jaxx.io/files/1.1.7/Jaxx-v1.1.7-linux-x64.tar.gz
    && tar -xf Jaxx-v1.1.7-linux-x64.tar.gz
    && rm Jaxx-v1.1.7-linux-x64.tar.gz

# determine dependencies
RUN ldd Jaxx-v1.1.7_linux-x64/Jaxx \
    | awk '/=>/{print $(NF-1)}' \
    | while read n; do dpkg-query -S $n; done \
    | sed 's/^\([^:]\+\):.*$/\1/' \
    | sort | uniq \
    > jaxxdependencies.txt

# install the dependencies
RUN apt-get update && \
    apt-get install -y $(cat jaxxdependencies.txt | paste -s)

# Create user "docker" and set the password to "docker"
RUN useradd -m -d /home/docker docker
RUN echo "docker:docker" | chpasswd

# Set locale (fix locale warnings)
RUN localedef -v -c -i en_US -f UTF-8 en_US.UTF-8 || true
RUN echo "Europe/Zurich" > /etc/timezone

# Replace 1000 with your user / group id
RUN export uid=1000 gid=1000 && \
    echo "docker ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/docker && \
    chmod 0440 /etc/sudoers.d/docker
USER docker
ENV HOME /home/docker
ENV PATH /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/Jaxx-v1.1.7_linux-x64

# Start Jaxx
CMD Jaxx
