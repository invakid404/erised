FROM alpine as build

RUN apk update && \
	apk upgrade && \
	apk add \
		cmake \
		git \
		ninja \
		g++ \
		qt5-qtbase-dev \
		qt5-qtwebsockets-dev && \
	rm -rf /var/cache/apk/*

WORKDIR /build
RUN git clone https://github.com/invakid404/erised .

RUN cmake . -DCMAKE_BUILD_TYPE=Release -GNinja && \
	cmake --build . --config Release && \
	ctest -C Release

FROM alpine as app

RUN apk update && \
	apk upgrade && \
	apk add \
		qt5-qtbase \
		qt5-qtwebsockets && \
	rm -rf /var/cache/apk/*

WORKDIR /app
COPY --from=build /build/erised .

ENTRYPOINT ["/app/erised"]
