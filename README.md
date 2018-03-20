<!-- ![Logo](https://raw.githubusercontent.com/Heisenberk/StegX/dev-cmake/doc/rsc/readme-logo.png)  -->
<p align="center">
<img src="https://raw.githubusercontent.com/Heisenberk/StegX/dev/doc/rsc/logo-readme.png">
</p>

---

Introduction
================================================================================

**StegX** est une application de stéganographie. Elle permet de dissimuler des
données dans divers formats de fichier, de type image, son ou vidéo. Les
données cachées peuvent ainsi être transmises par un canal non sécurisé sans
être découverte, puis le receveur pourra les extraire. L'application se compose
d'une interface graphique et d'une interface en ligne de commande, ainsi que
d'une bibliothèque partagée intégrable dans d'autres projets de développement.

Statut
--------------------------------------------------------------------------------

* Interface graphique : développement non commencé.
* Interface en ligne de commande : développement non commencé.
* Bibliothèque : développement non commencé.


---

Installation
================================================================================

Unix (Debian-like)
--------------------------------------------------------------------------------

### - Installateur

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.deb`.
2. Installer le en utilisant une interface à APT (par exemple en double cliquant
dessus), ou en utilisant la commande `sudo apt-get install ./StegX-xxx.deb`
depuis le répertoire de téléchargement.

### - Portable

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.tar.gz` (archive
tar) ou `StegX-xxx.sh` (exécutable auto extractible).
2. Décompresser l'archive avec la commande `tar xzvf StegX-xxx.tar.gz` ou lancer
l'extraction de l'exécutable avec la commande `./StegX-xxx.sh` en fonction de
votre choix de téléchargement.
3. Vous trouverez un dossier contenant l'application. 

Windows
--------------------------------------------------------------------------------

### - Installateur

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.exe`.
2. Installer le en double cliquant dessus.
3. Si vous voulez pouvoir lancer l'interface en ligne de commande depuis le
terminal avec la commande `stegx`, alors sélectionner `Ajouter le répertoire
d'installation au PATH` lorsque cela vous sera demandé lors de l'installation.

### - Portable

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.zip` (archive
compressée).
2. Décompresser l'archive, ainsi vous trouverez un dossier contenant
l'application. 


---

Désinstallation
================================================================================

Unix (Debian-like)
--------------------------------------------------------------------------------

Exécuter la commande `sudo apt remove stegx` pour supprimer le paquet de votre
système.

Windows
--------------------------------------------------------------------------------

Accéder au panneau de configuration, cliquer sur désinstaller un programme,
sélectionner `StegX` et cliquer sur désinstaller.

---

Utilisation
================================================================================

Après une installation avec un installateur
--------------------------------------------------------------------------------

Dans un terminal, utiliser la commande `stegx` pour utiliser l'interface en
ligne de commande. Pour lancer l'interface graphique, taper `stegx-gui` dans
votre terminal, ou utiliser le raccourci créer dans le menu démarrer ou sur le
bureau.

Après décompression de la version portable
--------------------------------------------------------------------------------

Placez vous dans le répertoire dans le répertoire `bin` contenu dans le
répertoire racine de l'application, puis exécutez dans votre terminal `./stegx`
pour l'interface en ligne de commande ou `./stegx-gui` pour l'interface
graphique.

Aide
--------------------------------------------------------------------------------

Pour obtenir de l'aide, consulter le manuel de l'interface graphique sous format
PDF ou taper dans votre terminal `man stegx` pour lire le manuel de l'interface
en ligne de commande sur **Unix** si l'installation à été effectuée par
l'installateur.

---

Développement
================================================================================

Dépendances
--------------------------------------------------------------------------------

### - Requises

#### -- Unix

* *Compilateur* : **GNU Compiler Collection** (GCC) (https://gcc.gnu.org/) 
* *Moteur de production* : **GNU Make** (https://www.gnu.org/software/make/)

#### -- Windows

Au choix :
* *Compilateur et environment Unix* : 
  * **MinGW-w64/GCC** (https://mingw-w64.org/doku.php)
  * **MSYS2** (http://www.msys2.org/)
* *Compilateur et environment de développement* : 
  * **Microsoft Visual Studio** (MSVC) (https://www.visualstudio.com/fr/downloads/)

#### -- Unix & Windows

* *Moteur de production* : **CMake** (https://cmake.org/)
* *Interface graphique* : <b> GTK+ </b> (>= 3.0) (https://www.gtk.org/)

### - Optionnelles (Unix & Windows)

* *Générateur de documentation* : **Doxygen** (https://www.stack.nl/~dimitri/doxygen/index.html)
* *Distribution LaTeX* : **TeX Live** (https://tug.org/texlive/)
* *Test unitaire* : **CMocka** (https://cmocka.org/)

Commandes et cibles
--------------------------------------------------------------------------------

La configuration de la compilation est à faire en première. Toutes les autres
commandes sont à effectuer dans le dossier _build_. Lors d'un ajout d'un fichier
source au projet, ou lors d'une rencontre avec un bug lors de la
configuration/compilation, supprimez le dossier _build_ et recommencez la
configuration. Les commandes entre _[  ]_ sont optionnelles et le _pipe_ ( | )
signifie "OU".

Sur **Windows**, si une erreur survient, faites attention de placer le dossier
dans un chemin qui ne contient pas d'espaces. Certains modules de **CMake** pour
**Windows** gèrent mal les espaces. Les cibles (targets) exécutées par **CMake**
peuvent aussi êtres générées directement par l'interface graphique de **MSVC**
sous forme de solution.

L'option _-DVarName=VarValue_ de **CMake** permet de configurer une variable.
Ci-dessous une liste des variables configurables avec leurs valeurs possibles :
1. *Description* : **VarName** = VarValue1, VarValue2 etc...
2. *Chemin vers un dossier existant pour l'installation* :
**CMAKE_INSTALL_PREFIX** = /usr/local, /opt/stegx
3. *Mode de compilation* : **CMAKE_BUILD_TYPE** = Release, Debug

### - Configuration de la compilation

#### -- Unix

    mkdir build
    cd build
    cmake .. [-G "Unix Makefiles"] [-DVarName=VarValue]

#### -- Windows (MinGW-w64/GCC & MSYS2)

    mkdir build
    cd build
    cmake .. [-G "MinGW Makefiles | MSYS Makefiles"] [-DVarName=VarValue]

#### -- Windows (MSVC)

    mkdir build
    cd build
    cmake .. [-G "Visual Studio 15 2017"] [-DVarName=VarValue]

### - Compilation des modules principaux

#### -- Unix & Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make [all] [stegx-cli stegx-gui stegx-lib]

#### -- Windows (MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target all [stegx-cli stegx-gui stegx-lib]

#### -- Windows (MSVC)

    cmake --build . --target ALL_BUILD [stegx-cli stegx-gui stegx-lib]

### - Génération de la documentation

#### -- Unix & Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make doc

#### -- Windows (MSVC | MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target doc

### - Génération des rapports

#### -- Unix & Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make report

#### -- Windows (MSVC | MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target report

### - Lancement des tests unitaires

#### -- Unix & Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make check

#### -- Windows (MSVC | MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target check

### - Création des binaires de distribution

#### -- Unix

    sudo make dist

#### -- Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make dist // En tant qu'administrateur

#### -- Windows (MSVC | MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target dist // En tant qu'administrateur

### - Installation

#### -- Unix

    sudo make install

#### -- Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make install // En tant qu'administrateur

#### -- Windows (MSVC | MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target INSTALL // En tant qu'administrateur

### -- Désinstallation

#### - Unix

    sudo make uninstall

#### -- Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make uninstall // En tant qu'administrateur

#### -- Windows (MSVC | MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target uninstall // En tant qu'administrateur

### - Nettoyage

#### -- Unix & Windows (MinGW-w64/GCC & MSYS2 avec MinGW Makefiles)

    make clean

#### -- Windows (MSVC | MinGW-w64/GCC & MSYS2 avec MSYS Makefiles)

    cmake --build . --target clean
