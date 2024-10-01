FROM ubuntu:24.04

WORKDIR /app

RUN apt update -y && apt upgrade -y && apt install build-essential libhdf5-dev mpi-default-dev git wget -y
RUN mkdir -p ~/miniconda3
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh
RUN bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
RUN rm ~/miniconda3/miniconda.sh
ENV PATH=/root/miniconda3/bin:$PATH
RUN conda create -n test python==3.12 pip -y

COPY . ./versioned_hdf5/
RUN mv ./versioned_hdf5/failure.py ./

RUN conda run -n test pip install ./versioned_hdf5 -v
RUN conda run -n test python failure.py
