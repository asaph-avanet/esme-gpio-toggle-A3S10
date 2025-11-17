SUMMARY = "A minimal ESME image"

LICENSE = "MIT"

inherit core-image

# Add rpi-test-image features
require recipes-core/images/rpi-test-image.bb

# Add extra features
IMAGE_FEATURES += "ssh-server-openssh"
