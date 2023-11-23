FROM alpine
RUN apk add build-base
RUN apk add meson
WORKDIR /task-cad-1
COPY . .
RUN meson setup build && cd build && meson compile && ./task-cad-1
