# Métadonnées de la recette
SUMMARY = "Application de bascule GPIO pour ESME-3S10"
HOMEPAGE = "https://github.com/asaph-avanet/esme-gpio-toggle-A3S10"
SECTION = "base"

# Version
PV = "1.0"
PR = "r0"

# Licence (Il est préférable d'avoir un fichier LICENSE dans votre dépôt)
# Si vous n'en avez pas, mettez LICENSE = "CLOSED" et commentez LIC_FILES_CHKSUM
LICENSE = "MIT"
# Adaptez le chemin si votre fichier de licence a un autre nom ou hash
LIC_FILES_CHKSUM = "file://COPYING.MIT;md5=3912d958d00bac4a6b550f75d7c806bb"

# --- Dépendances ---
inherit pkgconfig
DEPENDS = "libgpiod (< 2.0)"

# --- Source URI (Mode Git Distant) ---
# URL de votre dépôt GitHub
# protocol=https : Pour utiliser le port 443 (souvent moins bloqué)
# branch=main : La branche par défaut sur GitHub est souvent 'main' maintenant
SRC_URI = "git://github.com/asaph-avanet/esme-gpio-toggle-A3S10.git;protocol=https;branch=main"

# Révision : Utilise le dernier commit de la branche spécifiée
SRCREV = "${AUTOREV}"

# Dossier Source (S)
# BitBake clone le dépôt dans ${WORKDIR}/git
S = "${WORKDIR}/git"

# --- Script d'init ---
inherit update-rc.d
INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME:${PN} = "esme-gpio26-toggle"
INITSCRIPT_PARAMS:${PN} = "defaults"

# --- Tâches Manuelles ---

do_compile() {
    # On force make à s'exécuter dans le dossier cloné
    oe_runmake -C ${S}
}

do_install() {
    # Installation avec surcharge du dossier de destination
    oe_runmake install INSTALL_DIR=${D} -C ${S}
    
    # Installation manuelle du script d'init
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${S}/esme-gpio26-toggle ${D}${sysconfdir}/init.d/esme-gpio26-toggle
}
