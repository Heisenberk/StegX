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

* Interface graphique : Quasi-terminée.
* Interface en ligne de commande : Quasi-terminée.
* Bibliothèque : En cours de commencement.


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

### - Optionnelles

#### -- Unix & Windows

* *Générateur de documentation* : **Doxygen** (https://www.stack.nl/~dimitri/doxygen/index.html)
* *Distribution LaTeX* : **TeX Live** (https://tug.org/texlive/)
* *Test unitaire* : **CMocka** (https://cmocka.org/)

#### -- Unix

* *Générateur de tags* : **Ctags** (http://ctags.sourceforge.net/)
* *Formateur de code source* : **GNU Indent** (https://www.gnu.org/software/indent/)

Commandes et cibles
--------------------------------------------------------------------------------

La configuration de la compilation est à faire en première. Toutes les autres
commandes sont à effectuer dans le dossier _build_. Lors de l'ajout d'un fichier
source au projet ou lors de la rencontre d'un bug lors de la
configuration/compilation, utilisez la commande de réinitialisation de
l'arborescence, sinon, supprimez le dossier _build_ et recommencez la
configuration. Les commandes entre _[  ]_ sont optionnelles.

Sur **Windows**, si une erreur survient, faites attention de placer le dossier
dans un chemin qui ne contient pas d'espaces. Certains modules de **CMake** pour
**Windows** gèrent mal les espaces. Les cibles (targets) exécutées par **CMake**
peuvent aussi êtres générées directement par l'interface graphique de **MSVC**
sous forme de solution.

Pour chaque commande avec **Make**, vous pouvez utiliser *VERBOSE=1* pour
afficher toutes les actions effectuées.

L'option _-DVarName=VarValue_ de **CMake** permet de configurer une variable.
Ci-dessous une liste des variables configurables avec leurs valeurs possibles :
1. *Description* : **VarName** = VarValue1, VarValue2 etc...
2. *Chemin vers un dossier existant pour l'installation* :
**CMAKE_INSTALL_PREFIX** = /usr/local, /opt/stegx
3. *Mode de compilation* : **CMAKE_BUILD_TYPE** = Release, Debug

### - Unix

#### -- Configuration de la compilation

    mkdir build
    cd build
    cmake .. [-G "Unix Makefiles"] [-DVarName=VarValue]
    
#### -- Compilation des modules principaux

    make [all] [stegx-cli stegx-gui stegx-lib] [VERBOSE=1]
    
#### -- Génération de la documentation

    make doc
    
#### -- Génération des rapports

    make report
    
#### -- Lancement des tests unitaires

    make check
 
#### -- Création des binaires de distribution

    sudo make dist
    
#### -- Installation

    sudo make install
    
#### -- Désinstallation

    sudo make uninstall

#### -- Génération des tags

    make tags

#### -- Formatage du code source

    make indent
    
#### -- Nettoyage

    make clean

#### -- Réinitialisation

    make reinit
    
### - Windows

#### -- Configuration de la compilation

    mkdir build
    cd build
    MSYS :
        cmake .. -G "MSYS Makefiles" [-DVarName=VarValue]
    MinGW :
        cmake .. -G "MinGW Makefiles" [-DVarName=VarValue]
    MSVC :
        cmake .. [-G "Visual Studio 15 2017"] [-DVarName=VarValue]
    
#### -- Compilation des modules principaux

    MSYS :
        make [all] [stegx-cli stegx-gui stegx-lib] [VERBOSE=1]
    MinGW :
        cmake --build . --target all [stegx-cli stegx-gui stegx-lib]
    MSVC : Interface graphique (GTK+) non disponible.
        cmake --build . --target ALL_BUILD [stegx-cli stegx-lib]
    
#### -- Génération de la documentation

    MSYS :
        make doc
    MinGW & MSVC:
        cmake --build . --target doc
    
#### -- Génération des rapports

    MSYS :
        make report
    MinGW & MSVC :
        cmake --build . --target report
    
#### -- Lancement des tests unitaires

    MSYS & MinGW :
        Tests unitaires non disponibles.
    MSVC :
        cmake --build . --target check
 
#### -- Création des binaires de distribution

    MSYS :
        make dist
    MinGW & MSVC : à lancer en tant qu'administrateur.
        cmake --build . --target dist
    
#### -- Installation

    MSYS : à lancer en tant qu'administrateur.
        make install
    MinGW & MSVC : à lancer en tant qu'administrateur.
        cmake --build . --target INSTALL
    
#### -- Désinstallation

    MSYS : à lancer en tant qu'administrateur.
        make uninstall
    MinGW & MSVC : à lancer en tant qu'administrateur.
        cmake --build . --target uninstall
    
#### -- Nettoyage

    MSYS :
        make clean
    MinGW & MSVC :
        cmake --build . --target clean

#### -- Réinitialisation

    MSYS :
        make reinit
    MinGW & MSVC :
        cmake --build . --target reinit
