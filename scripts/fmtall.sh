#! /bin/bash

scriptDir=$(dirname "$0")
scriptDir=$(readlink -f "${scriptDir}")
root=$(realpath "${scriptDir}/..")
formatter="${CLANG_FMAT_EXE:-clang-format}"
echo "Formatting from ${dir} using ${formatter}..."

srcDirs=("${root}/source" "${root}/plugins" "${root}/exp/http")
for dir in "${srcDirs[@]}"
do
find "${dir}" -type f \(\
              -iname '*.h' -o \
              -iname '*.hpp' -o \
              -iname '*.hxx' -o \
              -iname '*.c' -o \
              -iname '*.cpp' -o \
              -iname '*.cxx' \
              \) \
              ! -iname '*moc_*' \
                # -exec "${formatter}" -style=file {} \; || exit -1
done
echo "Formatting done..."                