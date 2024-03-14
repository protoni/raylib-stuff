# Use an emscripten-sdk base image
FROM emscripten/emsdk:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    git \
    cmake \
    build-essential

# Clone the raylib repository and build it
RUN git clone --recurse-submodules https://github.com/raysan5/raylib.git raylib && \
    cd raylib/src && \
    emmake make PLATFORM=PLATFORM_WEB

# Set the WORKDIR to a directory where we'll put our program
WORKDIR /usr/src/app

# Copy example raylib program into the Docker image
COPY example.c ./

# Copy custom shell ( web page that displays the raylib window ) into the Docker image
COPY shell.html ./
COPY style.css ./

# Compile the program using Emscripten
RUN emcc example.c -o example.html \
    -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 \
    -I/src/raylib/src -L/src/raylib/src \
    -lraylib -DPLATFORM_WEB \
    --use-preload-plugins \
    --shell-file /usr/src/app/shell.html -O3

# Expose the port the HTTP server will use
EXPOSE 8080

# Use python3 HTTP server to serve the compiled WebAssembly application
CMD ["emrun", "--no_browser", "--port", "8080", "example.html"]
