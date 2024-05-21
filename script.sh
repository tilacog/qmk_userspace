#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

# To swich to the correct bootloader, via ISP, use the following command
# $ avrdude -C /etc/avrdude.conf -c stk500v1 -P /dev/ttyACM0 -p m32u4 -b19200 -B 125kHz -U flash:w:bootloader_atmega32u4_1.0.0.hex:i -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xF3:m

# Backup existing .hex files by appending a timestamp suffix
backup_hex_files() {
    local backup_suffix
    backup_suffix="$(date +%Y%m%d%H%M%S)"
    for file in *.hex; do
        if [ -f "$file" ]; then
            mv "$file" "${file}_${backup_suffix}" # Rename file with timestamp
        fi
    done
}

# Compile firmware with QMK
compile_firmware() {
    qmk compile --clean -kb handwired/void_ergo -km tilacog
}

# Prepare EEPROM reset file
prepare_eeprom_reset() {
    local eeprom_reset_file
    eeprom_reset_file=$(mktemp)
    cat <<EOF >"$eeprom_reset_file"
:0100000000FF
:00000001FF
EOF
    echo "$eeprom_reset_file"
}

wait_for_reset() {
    echo "Device reset initiated. Continuing with flashing after 5 seconds..."

    for ((i = 5; i > 0; i--)); do
        echo "Waiting for $i seconds..."
        sleep 1
    done
}

# Flash the device with the firmware and EEPROM reset file
flash_firmware() {
    local eeprom_reset_file=$1
    dfu-programmer atmega32u4 erase --force
    dfu-programmer atmega32u4 flash --force --eeprom "$eeprom_reset_file" || true
    dfu-programmer atmega32u4 flash --force handwired_void_ergo_tilacog.hex
    dfu-programmer atmega32u4 reset
}

main() {
    backup_hex_files
    compile_firmware
    eeprom_file=$(prepare_eeprom_reset)
    wait_for_reset
    flash_firmware "$eeprom_file"
}

main
