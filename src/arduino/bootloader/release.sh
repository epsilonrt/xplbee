#!/bin/bash
#
# Use like: "release.sh <versionno>"
#
# Build a "release" .zip file for xPLBee bootloader
# Run from the build directory

# Uncomment if you want a clean builds of specific files
# make rebuild

rm -Rf /tmp/xplbee-release

#
# Create the 3rd-party hardware extension directory structure
# Note that the structure under "packages" (handed by boards manager)
# is different than the structure under "sketchbook/hardware" would be.

TOP=/tmp/xplbee-release/xplbee/
#
# Bootloaders directory
mkdir -p $TOP/bootloaders/xplbee
# cores, variants, libraries
# mkdir -p $TOP/variants/
mkdir -p $TOP/libraries/
# Less common: firmware, system.
# mkdir -p $TOP/firmwares/
# mkdir -p $TOP/system/

#
# Copy files from whereever into the release directory
cp boards-1.6.txt $TOP/boards.txt
#cp -R ../../examples $TOP/libraries/
#cp -R ../../variants $TOP/
#cp -R ../../system $TOP/

#
# Create platform.txt, because it contains the "group" name for the boards menu
echo name=xPLBee $1 > $TOP/platform.txt
echo version=$1 >> $TOP/platform.txt

#
# Create a README file.
echo This is an xPLBee version $1 \"Binary\" Release. > $TOP/README.TXT
echo >> $TOP/README.TXT
echo For Source code see https://github.com/epsilonrt/xplbee>> $TOP/README.TXT

#
# Copy over our "binaries."
cp *.hex $TOP/bootloaders/xplbee

#
# Copy examples ?  (examples for a boards.txt don't seem possible?)


# files we'd specifical exclude, if we weren't doing only .hex files.
#rm /tmp/xplbee-release/xplbee/avr/bootloaders/xplbee/*.lst
#rm /tmp/xplbee-release/xplbee/avr/bootloaders/xplbee/*~
#rm /tmp/xplbee-release/xplbee/avr/bootloaders/xplbee/#*

#
# zip everything up.
pushd /tmp/xplbee-release
zip -r xplbee.zip xplbee
HASH=`openssl dgst -sha256 xplbee.zip | sed -e 's/.* //'`
SIZE=`stat -c %s xplbee.zip`
popd
sed -e "s/#.*//" -e "s/%HASH%/$HASH/" -e "s/%VERSION%/$1/" -e "s/%SIZE%/$SIZE/" package_xplbee_xplbee-additional_index.json.TEMPLATE > /tmp/xplbee-release/package_xplbee_xplbee-additional_index.json

#
echo This leaves the .zip and the .json file in /tmp/xplbee-release
echo where it can be copied to a suitable network location.

