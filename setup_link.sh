#!/bin/bash
set -e

PARENT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$PARENT_DIR/build"

mkdir -p "$BUILD_DIR"

declare -A targets=(
    ["$BUILD_DIR/Parser.ih"]="$PARENT_DIR/src/frontend/parser/Parser.ih"
    ["$BUILD_DIR/Scanner.ih"]="$PARENT_DIR/src/frontend/lexer/Scanner.ih"
    ["$PARENT_DIR/include/frontend/parser/Parser.h"]="$BUILD_DIR/Parser.h"
    ["$PARENT_DIR/include/frontend/lexer/Scanner.h"]="$BUILD_DIR/Scanner.h"
)

for link in "${!targets[@]}"; do
    source="${targets[$link]}"
    mkdir -p "$(dirname "$source")"

    if [ -L "$source" ]; then
        resolved_source="$(readlink -f "$source")"
        if [ -f "$resolved_source" ]; then
            temporary_source="$(mktemp)"
            cp -p "$resolved_source" "$temporary_source"
            rm -f "$source"
            mv "$temporary_source" "$source"
        else
            rm -f "$source"
        fi
    fi

    relative_target="$(realpath --relative-to="$(dirname "$link")" "$source")"
    if [ -L "$link" ] && [ "$(readlink "$link")" = "$relative_target" ]; then
        echo "✓ $link → $relative_target"
    else
        rm -f "$link"
        ln -s "$relative_target" "$link"
        echo "✓ $link → $relative_target"
    fi
done

echo "Relative symlinks successfully created in build tree → source tree"

echo "Copying parser grammar files to $BUILD_DIR"

cp "$PARENT_DIR/src/frontend/parser/parser.yy" "$BUILD_DIR/"
cp "$PARENT_DIR/src/frontend/parser/"*.ly "$BUILD_DIR/"