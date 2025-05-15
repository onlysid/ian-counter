# Split into two stages so that the final image is lean (ommitting compilers, headers etc)
# This also means a smaller attack surface and better cache efficiency

# ─── Stage 1: Build ───────────────────────────────────────────────────────────
FROM alpine:3.18 AS build

# Install build tools and CMake
RUN apk update \
 && apk add --no-cache \
     # Pull in gcc,g++,make
      build-base      \
      # Build tool
      cmake>=3.27     \
      # Faster than GNU Make! (tool to compile/link)
      ninja           \
      # Lightweight C standard library used by Alpine
      musl-dev

# Set working directory
WORKDIR /app

# Copy CMake config and source code
COPY CMakeLists.txt .
COPY src/ src/

# Configure & build with Ninja in Release mode
RUN mkdir build \
 # Go into build dir
 && cd build \
 # Build a release executable with cMake and Ninja
 && cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      .. \
 # Run Ninja
 && ninja

# ─── Stage 2: Runtime ─────────────────────────────────────────────────────────
FROM alpine:3.18

# Install the C++ runtime libraries our binary needs
RUN apk add --no-cache \
      libstdc++ \
      libgcc

# Only copy the compiled binary
WORKDIR /app
COPY --from=build /app/build/ian_counter .

ENTRYPOINT ["./ian_counter"]
