FROM ubuntu:26.04 AS build

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential cmake ninja-build git curl zip unzip tar pkg-config \
        bison flex ca-certificates \
        bison flex python3 ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV VCPKG_ROOT=/opt/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git ${VCPKG_ROOT} \
    && ${VCPKG_ROOT}/bootstrap-vcpkg.sh -disableMetrics

WORKDIR /src/mdp
COPY vcpkg.json ./
RUN ${VCPKG_ROOT}/vcpkg install --x-install-root=build/vcpkg_installed

COPY --from=proto . /src/schemas/proto
COPY . .
RUN cmake -S . -B build && cmake --build build

FROM ubuntu:26.04 AS feedhandler

COPY --from=build /src/mdp/build/feedhandler/feedhandler /usr/local/bin/feedhandler
ENTRYPOINT ["feedhandler"]