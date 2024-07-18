include recipes-core/images/core-image-base.bb


IMAGE_FEATURES += "ssh-server-dropbear"
IMAGE_INSTALL += "bluez5 i2c-tools dhcpcd iptables wpa-supplicant car-detection v4l-utils python3 libcamera picamera-libs overtakemanager"
IMAGE_INSTALL:append = " packagegroup-rpi-test"

