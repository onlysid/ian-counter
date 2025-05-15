#! /usr/bin/env bash
set -euo pipefail

# -----------------------------------------------------------------------------
#   run.sh - build and run the ian-counter docker image
#
#   Usage:
#       sh run.sh <path-to-csv-folder> [--rebuild]
#   
#   If --rebuild is passed, the image will be rebuilt even if it exists already
# -----------------------------------------------------------------------------

IMAGE_NAME="ian-counter:latest"
CSV_DIR="${1:-}"

if [[ -z "CSV_DIR" ]]; then
    echo "❌ Error: no CSV folder provided."
    echo "Usage: $0 <path-to-csv-folder> [--rebuild]"
    exit 1
fi

# Check that Docker is installed
if ! command -v docker &> /dev/null; then
    echo "❌ Docker not found. Please install Docker to proceed."
    exit 2
fi

# Absolute path to mount
CSV_DIR="$(cd "$CSV_DIR" && pwd)"

REBUILD=false
if [[ "${2-}" == "--rebuild" ]]; then
    REBUILD=true
fi

# Build if requested or if image doesn't exist
if $REBUILD || [[ -z "$(docker images -q $IMAGE_NAME)" ]]; then
    echo "🔨 Building Docker image ${IMAGE_NAME}..."
    docker build --pull -t "$IMAGE_NAME" .
else
    echo "ℹ️ Docker image ${IMAGE_NAME} already exists. Skipping build."
fi

echo "▶️ Running ian-counter on ${CSV_DIR}..."
docker run --rm -v "${CSV_DIR}:/data:ro" "$IMAGE_NAME" /data