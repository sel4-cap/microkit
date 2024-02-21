#!/bin/bash
FILE_LOCATION="/var/lib/tftpboot/loader-josh.img"
export MICROKIT_DIR="$PWD"
export MICROKIT_SDK="$MICROKIT_DIR/release/microkit-sdk-1.2.6"
export NETBSD_DIR="$MICROKIT_DIR/example/maaxboard/xhci_stub/netbsd/src"
export PATH="$HOME/mk-manifest/compiler/bin:$PATH"
export PYTHONPATH="$MICROKIT_DIR/tool"
export MICROKIT_TOOL="python -m microkit"
rm -r $MICROKIT_DIR/tmp_build
python3.9 dev_build.py --board=maaxboard --example=xhci_stub
echo 
sudo cp $MICROKIT_DIR/tmp_build/loader.img $FILE_LOCATION
if [ $? -gt 0 ]; then
    echo "Error(s) detected, file not copied"
else
    echo Copied image file to "$FILE_LOCATION".
fi