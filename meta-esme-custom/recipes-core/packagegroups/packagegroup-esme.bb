DESCRIPTION = "Packagegroup pour les applications ESME"
LICENSE = "MIT"
# On utilise la licence MIT commune fournie par Yocto
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Héritage de la classe packagegroup (Obligatoire)
inherit packagegroup

# Liste des paquets à inclure dans ce groupe
# ${PN} est le nom de la recette (ici packagegroup-esme)
RDEPENDS:${PN} = "\
    esme-gpio-toggle \
    "
