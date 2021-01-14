#!/bin/bash
# Create auto-generated text files used on the host board. These include:
#   - i2c_addrs.sh
#

usage()
{
    exit_code=$1

    echo "$(basename $0) <build top> <header path>"
    echo "  - build top     : Top of build tree"
    echo "  - header path   : Path to header file we parse"
    echo ""
    exit $exit_code 
}

# Validate input
if test ! -d "$1"; then
    echo "Build top directory does not exist: '$1'"
    usage 255
fi
if test ! -f "$2"; then
    echo "Header path not found: '$1'"
    usage 255
fi

# Input looks good
build_top=$1
header_file=$2
fs_dir=${build_top}/fs

# Make sure the destination directory is there, it should already be there from the build
test -d $fs_dir || (echo "Destination 'fs' directory does not exist: '$fs_dir'" && exit 1)
set -e

# Read the 'bcmolt_i2c_devs_addr.h' file for the given platform and create the 'i2c_addrs.sh' file for use
# on the host board.
cp i2c_addrs.sh ${fs_dir}
chmod u+w ${fs_dir}/i2c_addrs.sh
grep -w "BCM_I2C_DEV_ADDR" ${header_file} | \
    sed -s "s/BCM_I2C_DEV_ADDR(\(.*\), \(.*\), 0x\(.*\))/\1=\3/" >> ${fs_dir}/i2c_addrs.sh

exit 0
